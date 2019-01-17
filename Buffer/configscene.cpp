#include "configscene.h"

using namespace std;

ConfigScene::ConfigScene()
{

}

vector<Region> ConfigScene::GetRegionDirectionInfractionList()
{
    return list_region_direction_infraction_;
}

vector<Region> ConfigScene::GetRegionStopSignInfractionList()
{
    return list_region_stop_sign_infraction_;
}

vector<TrafficSignalRegion> ConfigScene::GetRegionRedLightInfractionList()
{
    return list_region_red_light_infraction_;
}

void ConfigScene::SetRegionRedLightInfractionList(vector<TrafficSignalRegion> list_region_red_light_infraction)
{
    list_region_red_light_infraction_ = list_region_red_light_infraction;
}
