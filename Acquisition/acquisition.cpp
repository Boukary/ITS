#include "acquisition.h"

using namespace std;
using namespace cv;

Acquisition::Acquisition(Buffer *buffer)
{
    buffer_ = buffer;
    is_running_ = false;
}

void Acquisition::SetConfig(ConfigAcquisition config)
{
    config_ = config;
}

bool Acquisition::Init()
{
    if (cap_mono_.isOpened() || cap_stereo_.isOpened())
        return true;
    cap_mono_.open(config_.cap_path_mono);
    if (!cap_mono_.isOpened()){
        cout<<"Acquisition :: Capture Mono Not Opened !!! "<<endl;
        return false;
    }

    if (config_.is_stereo){
        cap_stereo_.open(config_.cap_path_stereo);
        if (!cap_stereo_.isOpened()){
            cout<<"Acquisition :: Capture Stereo Not Opened !!! "<<endl;
            return false;
        }
    }
    return true;
}

void Acquisition::Start()
{
    is_running_ = true;
    this->start();
}

void Acquisition::Stop()
{
    is_running_ = false;
}

bool Acquisition::MainFunction()
{
    if (config_.is_stereo){
        if ((cap_mono_.get(CV_CAP_PROP_POS_FRAMES) == cap_mono_.get(CV_CAP_PROP_FRAME_COUNT) )
                || (cap_stereo_.get(CV_CAP_PROP_POS_FRAMES) == cap_stereo_.get(CV_CAP_PROP_FRAME_COUNT) ))
            return false;
        cap_mono_ >> image_raw_mono_;
        cap_stereo_ >> image_raw_stereo_;
        return buffer_->AddFrameStereo(&image_raw_mono_,&image_raw_stereo_);
    }
    else {
        if (cap_mono_.get(CV_CAP_PROP_POS_FRAMES) == cap_mono_.get(CV_CAP_PROP_FRAME_COUNT))
            return false;
        cap_mono_ >> image_raw_mono_;
        return buffer_->AddFrameMono(&image_raw_mono_);
    }
}

void Acquisition::run()
{
    if (!Init())
        return;
    double timer;
    while(is_running_){
        timer = (double)getTickCount();

        MainFunction();
        QThread::msleep(500) ;
        //waitKey(10000);

        fps_ = getTickFrequency() / ((double)getTickCount() - timer);
    }
}
