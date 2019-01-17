#include "infractiondetection.h"

using namespace std;
using namespace cv;

InfractionDetection::InfractionDetection(Buffer *buffer)
{
    buffer_ = buffer;
    is_running_ = false;
}

void InfractionDetection::SetConfig(ConfigInfractionDetection config)
{
    config_ = config;
}

void InfractionDetection::Start()
{
    is_running_ = true;
    this->start();
}

void InfractionDetection::Stop()
{
    is_running_ = false;
}

bool InfractionDetection::MainFunction()
{
    int index = buffer_->IsInfractionDetectionAvailable();
    unsigned long long index_absolu = buffer_->GetInfractionDetectionDataByIndex(index,image_);
    vehicles_ = buffer_->GetVehicles();

    if (!UpdateTrafficSignalsColor())
        return false;
    for (int i = 0; i < vehicles_.size(); i++)
    {
        if (!DetectRedLightInfraction(&vehicles_[i], index_absolu))
            return false;
        if (!DetectStopSignInfraction(&vehicles_[i], index_absolu))
            return false;
        if (!DetectDirectionInfraction(&vehicles_[i], index_absolu))
            return false;
    }

    buffer_->UpdateVehicleListByInfractionDetection(&vehicles_);
    return buffer_->SetInfractionDetectionDataByIndex(index,index_absolu);
}

bool InfractionDetection::UpdateTrafficSignalsColor(){
    vector<TrafficSignalRegion> list_region_red_light_infraction = buffer_->GetConfigScene()->GetRegionRedLightInfractionList();

    Mat red_light_area, orange_light_area, green_light_area;
    bool is_red_on, is_orange_on, is_green_on;

    for (int i = 0; i < list_region_red_light_infraction.size(); i++)
    {
        red_light_area = image_(list_region_red_light_infraction[i].GetRedLightRegion());
        orange_light_area = image_(list_region_red_light_infraction[i].GetOrangeLightRegion());
        green_light_area = image_(list_region_red_light_infraction[i].GetGreenLightRegion());

        is_red_on = IsLightOn(red_light_area);
        is_orange_on = IsLightOn(orange_light_area);
        is_green_on = IsLightOn(green_light_area);
        if (is_red_on && !is_orange_on && !is_green_on){
            list_region_red_light_infraction[i].SetTrafficSignalColor(COLOR_RED);
            continue;
        }
        if (!is_red_on && is_orange_on && !is_green_on){
            list_region_red_light_infraction[i].SetTrafficSignalColor(COLOR_ORANGE);
            continue;
        }
        if (!is_red_on && !is_orange_on && is_green_on){
            list_region_red_light_infraction[i].SetTrafficSignalColor(COLOR_GREEN);
            continue;
        }
        if (!is_red_on && !is_orange_on && !is_green_on){
            list_region_red_light_infraction[i].SetTrafficSignalColor(COLOR_NONE);
            continue;
        }
    }

    buffer_->GetConfigScene()->SetRegionRedLightInfractionList(list_region_red_light_infraction);

    return true;
}

bool InfractionDetection::IsLightOn(Mat& area){
    Scalar color= mean(area);
    if ((color[0]<config_.color_threshold) && (color[1]<config_.color_threshold) && (color[2]<config_.color_threshold))
        return false;
    return true;
}

bool InfractionDetection::DetectRedLightInfraction(Vehicle* v, unsigned long long index_absolu){

    vector<Infraction> infraction_list = v->GetInfractionList();
    for (int i = 0; i < infraction_list.size(); i++)
        if (infraction_list[i].GetInfractionType() == INFRACTION_REDLIGHT)
            return true;

    vector<TrafficSignalRegion> list_region_red_light_infraction = buffer_->GetConfigScene()->GetRegionRedLightInfractionList();
    VehicleBlob blob = v->GetBlobByIndexAbsolu(index_absolu);

    for (int i = 0; i < list_region_red_light_infraction.size(); i++)
        if (list_region_red_light_infraction[i].GetTrafficSignalColor() == COLOR_RED
                && list_region_red_light_infraction[i].IsInsideRegion(v->GetBlobByIndexAbsolu(index_absolu).GetCentroidImage2D())){

            Infraction infraction(INFRACTION_REDLIGHT);
            infraction.SetIndexAbsolu(index_absolu);
            v->AddInfraction(infraction);
            if (!buffer_->GetProofElementMaker()->MakeInfractionProof(infraction))
                return false;
            break;
        }



    return true;
}

bool InfractionDetection::DetectStopSignInfraction(Vehicle* v, unsigned long long index_absolu){
    vector<Infraction> infraction_list = v->GetInfractionList();
    for (int i = 0; i < infraction_list.size(); i++)
        if (infraction_list[i].GetInfractionType() == INFRACTION_STOPSIGN)
            return true;



    return true;
}

bool InfractionDetection::DetectDirectionInfraction(Vehicle* v, unsigned long long index_absolu){
    vector<Infraction> infraction_list = v->GetInfractionList();
    for (int i = 0; i < infraction_list.size(); i++)
        if (infraction_list[i].GetInfractionType() == INFRACTION_DIRECTION)
            return true;
    return true;
}

void InfractionDetection::run()
{
    double timer;
    while(is_running_){
        timer = (double)getTickCount();

        MainFunction();

        fps_ = getTickFrequency() / ((double)getTickCount() - timer);
    }
}
