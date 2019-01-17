#include "display.h"

using namespace std;
using namespace cv;

Display::Display(Buffer *buffer)
{
    buffer_ = buffer;
    is_running_ = false;

    RNG rng( 0xFFFFFFFF );
    for(int i=0;i<100;i++)
        predefined_colors_.push_back(Scalar(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255)));
}

void Display::SetConfig(ConfigDisplay config)
{
    config_ = config;
}

void Display::Start()
{
    is_running_ = true;
    this->start();
}

void Display::Stop()
{
    is_running_ = false;
}

bool Display::MainFunction()
{
    int index = buffer_->IsDisplayAvailable();
    unsigned long long index_absolu = buffer_->GetDisplayDataByIndex(index,image_);
    vehicles_ = buffer_->GetVehicles();

    Rect vehicle_rect,label_rect;
    Point label_org;
    Size label_text_size;
    vector<VehicleBlob> blobs;

    for (int i = 0; i < vehicles_.size(); i++)
    {
        label_text_size = getTextSize(format("ID %d",vehicles_.at(i).GetIdVehicle()), FONT_HERSHEY_PLAIN, 2, 2, NULL);

        vehicle_rect = vehicles_.at(i).GetBlobByIndexAbsolu(index_absolu).GetScope();
        label_rect = Rect(vehicle_rect.x - 2,vehicle_rect.y - label_text_size.height, label_text_size.width, label_text_size.height);
        label_org = Point(label_rect.x,label_rect.y + label_rect.height + 2);

        rectangle(image_, vehicle_rect, predefined_colors_[vehicles_.at(i).GetIdVehicle() % predefined_colors_.size()], 3, CV_AA);
        rectangle(image_, label_rect, predefined_colors_[(vehicles_.at(i).GetIdVehicle()) % predefined_colors_.size()], CV_FILLED);
        putText(image_, format("ID %d",vehicles_.at(i).GetIdVehicle()), label_org, FONT_HERSHEY_PLAIN, 2, CV_RGB(0,0,0), 2);

        blobs = vehicles_.at(i).GetBlobList();
        int idx;
        for (idx = blobs.size() - 1; idx >=0; idx--)
            if (blobs[idx].GetIndexAbsolu() <= index_absolu)
                break;

        for (int j=max(0,idx-config_.trajectory_history_display); j < idx; j++)
            line(image_, blobs[j].GetCentroidImage2D(), blobs[j+1].GetCentroidImage2D(), predefined_colors_[vehicles_.at(i).GetIdVehicle() % predefined_colors_.size()], 2, LINE_AA);

    }

    return buffer_->SetDisplayDataByIndex(index,index_absolu,&image_);
}

void Display::run()
{
    double timer;
    while(is_running_){
        timer = (double)getTickCount();

        MainFunction();

        fps_ = getTickFrequency() / ((double)getTickCount() - timer);
    }
}

// config scene yze
// draw feu rouge
