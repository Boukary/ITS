#include "recognition.h"

using namespace std;
using namespace cv;

Recognition::Recognition(Buffer *buffer)
{
    buffer_ = buffer;
    is_running_ = false;
}

void Recognition::SetConfig(ConfigRecognition config)
{
    config_ = config;
}

void Recognition::Start()
{
    is_running_ = true;
    this->start();
}

void Recognition::Stop()
{
    is_running_ = false;
}

bool Recognition::MainFunction()
{
    int index = buffer_->IsRecognitionAvailable();
    unsigned long long index_absolu = buffer_->GetRecognitionDataByIndex(index,image_);
    vehicles_ = buffer_->GetVehicles();


    buffer_->UpdateVehicleListByRecognition(&vehicles_);
    return buffer_->SetRecognitionDataByIndex(index,index_absolu);
}

void Recognition::run()
{
    double timer;
    while(is_running_){
        timer = (double)getTickCount();

        MainFunction();

        fps_ = getTickFrequency() / ((double)getTickCount() - timer);
    }
}
