#include "frame.h"

using namespace std;
using namespace cv;

Frame::Frame(bool is_stereo)
{
    index_absolu_ = 0;

    status_ = FRAME_INVALID ;
    mutex_ = new QMutex;
    is_locked_ = false;
    is_stereo_ = is_stereo;

    classification_ok_ = false;
    recognition_ok_ = false ;
    speed_estimation_ok_ = false;
    infraction_detection_ok_ = false;
}

void Frame::ResetFrame()
{
    index_absolu_ = 0;

    image_input_mono_.release() ;
    image_input_stereo_.release() ;
    image_preprocessed_mono_.release() ;
    image_preprocessed_stereo_.release() ;
    image_display_.release() ;

    vehicles_detected_.clear() ;
    status_ = FRAME_INVALID ;
    mutex_->unlock() ;
    is_locked_ = false;
    is_stereo_ = true;

    classification_ok_ = false;
    recognition_ok_ = false ;
    speed_estimation_ok_ = false;
    infraction_detection_ok_ = false;
}

unsigned long long Frame::GetIndexAbsolu()
{
    return index_absolu_;
}

void Frame::SetIndexAbsolu(unsigned long long index_absolu)
{
    index_absolu_ = index_absolu ;
}

Mat *Frame::GetImageInputMono()
{
    return &image_input_mono_ ;
}

Mat *Frame::GetImagePreprocessedMono()
{
    return &image_preprocessed_mono_ ;
}

Mat *Frame::GetImageInputStereo()
{
    return &image_input_stereo_ ;
}

Mat *Frame::GetImagePreprocessedStereo()
{
    return &image_preprocessed_stereo_ ;
}

vector<VehicleBlob> *Frame::GetVehiclesDetected()
{
    return &vehicles_detected_ ;
}

Mat *Frame::GetImageDisplay()
{
    return &image_display_ ;
}

void Frame::SetImageInputMono(Mat *image_input_mono)
{
    if(image_input_mono->empty()){
        cout<<"Frame :: Image Mono Empty !!! "<<endl;
        return;
    }
    image_input_mono->copyTo(image_input_mono_);
    status_ = FRAME_ACQUIRED;

    imshow("Image Input Mono",image_input_mono_);
    waitKey(1);
}

void Frame::SetImagePreprocessedMono(Mat *image_preprocessed_mono)
{
    if(image_preprocessed_mono->empty()){
        cout<<"Frame :: Image Mono Preprocessed Empty !!! "<<endl;
        return;
    }
    image_preprocessed_mono->copyTo(image_preprocessed_mono_);
    image_input_mono_.release();
    status_ = FRAME_PREPROCESSED;

    imshow("Image Preprocessed Mono",image_preprocessed_mono_);
    waitKey(1);
}

void Frame::SetImageInputStereo(Mat *image_input_mono, Mat *image_input_stereo)
{
    if(image_input_mono->empty()){
        cout<<"Frame :: Image Mono Empty !!! "<<endl;
        return;
    }
    if(image_input_stereo->empty()){
        cout<<"Frame :: Image Stereo Empty !!! "<<endl;
        return;
    }
    image_input_mono->copyTo(image_input_mono_);
    image_input_stereo->copyTo(image_input_stereo_);
    status_ = FRAME_ACQUIRED;

//    imshow("Image Input Mono",image_input_mono_);
//    imshow("Image Input Stereo",image_input_stereo_);
//    waitKey(1);
}

void Frame::SetImagePreprocessedStereo(Mat *image_preprocessed_mono, Mat *image_preprocessed_stereo)
{
    if(image_preprocessed_mono->empty()){
        cout<<"Frame :: Image Mono Preprocessed Empty !!! "<<endl;
        return;
    }
    if(image_preprocessed_stereo->empty()){
        cout<<"Frame :: Image Stereo Preprocessed Empty !!! "<<endl;
        return;
    }
    image_preprocessed_mono->copyTo(image_preprocessed_mono_);
    image_preprocessed_stereo->copyTo(image_preprocessed_stereo_);
    image_input_mono_.release();
    image_input_stereo_.release();
    status_ = FRAME_PREPROCESSED;

//    imshow("Image Preprocessed Mono",image_preprocessed_mono_);
//    imshow("Image Preprocessed Stereo",image_preprocessed_stereo_);
//    waitKey(1);
}

void Frame::SetVehiclesDetected(vector<VehicleBlob> *vehicles_detected)
{
    vehicles_detected_ = *vehicles_detected;
    status_ = FRAME_DETECTED;
}

void Frame::SetFrameTracked()
{
    vehicles_detected_.clear();
    status_ = FRAME_TRACKED;
}

void Frame::SetImageDisplay(Mat *image_display)
{
    if(image_display->empty()){
        cout<<"Frame :: Image Display Empty !!! "<<endl;
        return;
    }
    image_display->copyTo(image_display_);
    status_ = FRAME_DISPLAYED;

    imshow("Image Display",image_display_);
    waitKey(1);
}

void Frame::Lock()
{
    while(!mutex_->tryLock());
}

void Frame::Unlock()
{
    mutex_->unlock();
}

bool Frame::IsLocked()
{
    return is_locked_ ;
}

bool Frame::IsStereo()
{
    return is_stereo_ ;
}

void Frame::ClassificationDone()
{
    classification_ok_ = true ;
}

void Frame::RecognitionDone()
{
    recognition_ok_ = true ;
}

void Frame::SpeedEstimationDone()
{
    speed_estimation_ok_ = true ;
}

void Frame::InfractionDetectionDone()
{
    infraction_detection_ok_ = true ;
}

bool Frame::IsClassificationDone()
{
    return classification_ok_ ;
}

bool Frame::IsRecognitionDone()
{
    return recognition_ok_ ;
}

bool Frame::IsSpeedEstimationDone()
{
    return speed_estimation_ok_ ;
}

bool Frame::IsInfractionDetectionDone()
{
    return infraction_detection_ok_ ;
}

void Frame::SkipDetection()
{
    status_ = FRAME_DETECTED;
}

FrameStatus Frame::GetStatus()
{
    return status_ ;
}
