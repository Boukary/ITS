#include "preprocessing.h"

using namespace std;
using namespace cv;

Preprocessing::Preprocessing(Buffer *buffer)
{
    buffer_ = buffer;
    is_running_ = false;
}

void Preprocessing::SetConfig(ConfigPreprocessing config)
{
    config_ = config;
}

void Preprocessing::Start()
{
    is_running_ = true;
    this->start();
}

void Preprocessing::Stop()
{
    is_running_ = false;
}

bool Preprocessing::MainFunction()
{
    int index = buffer_->IsPreprocessingAvailable();
    unsigned long long index_absolu = buffer_->GetPreprocessingDataByIndex(index,image_mono_,image_stereo_);

    if (image_mono_.empty())
        return false;

    if (config_.input_color_space == CS_BAYER){
        cvtColor( image_mono_, image_mono_, CV_BGR2GRAY );
        cvtColor( image_mono_, image_mono_, CV_BayerBG2BGR );

        if (!image_stereo_.empty()){
            cvtColor( image_stereo_, image_stereo_, CV_BGR2GRAY );
            cvtColor( image_stereo_, image_stereo_, CV_BayerBG2BGR );
        }
    }

    return buffer_->SetPreprocessingDataByIndex(index,index_absolu,&image_mono_,&image_stereo_);
}

void Preprocessing::run()
{
    double timer;
    while(is_running_){
        timer = (double)getTickCount();

        MainFunction();

        fps_ = getTickFrequency() / ((double)getTickCount() - timer);
    }
}
