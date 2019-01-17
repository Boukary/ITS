#include "speedestimation.h"

using namespace std;
using namespace cv;

SpeedEstimation::SpeedEstimation(Buffer *buffer)
{
    buffer_ = buffer;
    is_running_ = false;
}

void SpeedEstimation::SetConfig(ConfigSpeedEstimation config)
{
    config_ = config;
}

void SpeedEstimation::Start()
{
    is_running_ = true;
    this->start();
}

void SpeedEstimation::Stop()
{
    is_running_ = false;
}

bool SpeedEstimation::MainFunction()
{
    int index = buffer_->IsSpeedEstimationAvailable();
    unsigned long long index_absolu = buffer_->GetSpeedEstimationDataByIndex(index,image_mono_, image_stereo_);
    vehicles_ = buffer_->GetVehicles();


    buffer_->UpdateVehicleListBySpeedEstimation(&vehicles_,index_absolu);
    return buffer_->SetSpeedEstimationDataByIndex(index,index_absolu);
}

void SpeedEstimation::run()
{
    double timer;
    while(is_running_){
        timer = (double)getTickCount();

        MainFunction();

        fps_ = getTickFrequency() / ((double)getTickCount() - timer);
    }
}
