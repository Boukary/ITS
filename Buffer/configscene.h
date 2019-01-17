#ifndef CONFIGSCENE_H
#define CONFIGSCENE_H

#include <iostream>

#include <Buffer/trafficsignalregion.h>

class ConfigScene
{
public:

    ConfigScene();

    std::vector<Region> GetRegionDirectionInfractionList();

    std::vector<Region> GetRegionStopSignInfractionList();

    std::vector<TrafficSignalRegion> GetRegionRedLightInfractionList();

    void SetRegionRedLightInfractionList(std::vector<TrafficSignalRegion> list_region_red_light_infraction);


private :

    std::vector<Region> list_region_direction_infraction_ ;

    std::vector<Region> list_region_stop_sign_infraction_ ;

    std::vector<TrafficSignalRegion> list_region_red_light_infraction_ ;

};

#endif // CONFIGSCENE_H
