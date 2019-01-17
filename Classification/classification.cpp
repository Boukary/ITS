#include "classification.h"

using namespace std;
using namespace cv;

Classification::Classification(Buffer *buffer)
{
    buffer_ = buffer;
    is_running_ = false;
}

void Classification::SetConfig(ConfigClassification config)
{
    config_ = config;
}

void Classification::Start()
{
    is_running_ = true;
    this->start();
}

void Classification::Stop()
{
    is_running_ = false;
}

bool Classification::MainFunction()
{
    int index = buffer_->IsClassificationAvailable();
    unsigned long long index_absolu = buffer_->GetClassificationDataByIndex(index,image_);
    vehicles_ = buffer_->GetVehicles();


    buffer_->UpdateVehicleListByClassification(&vehicles_);
    return buffer_->SetClassificationDataByIndex(index,index_absolu);
}

void Classification::run()
{
    double timer;
    while(is_running_){
        timer = (double)getTickCount();

        MainFunction();

        fps_ = getTickFrequency() / ((double)getTickCount() - timer);
    }
}
