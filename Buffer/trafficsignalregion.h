#ifndef TRAFFICSIGNALREGION_H
#define TRAFFICSIGNALREGION_H

#include "opencv2/opencv.hpp"
#include <iostream>

#include <Buffer/region.h>

typedef enum{
    COLOR_NONE,
    COLOR_RED,
    COLOR_ORANGE,
    COLOR_GREEN
} TrafficSignalColor;

class TrafficSignalRegion : public Region
{
public:

    TrafficSignalRegion(cv::Rect r_s, cv::Rect o_s, cv::Rect g_s);

    void SetTrafficSignalRects(cv::Rect r_s, cv::Rect o_s, cv::Rect g_s);

    void SetTrafficSignalColor(TrafficSignalColor traffic_signal_color);

    cv::Rect GetRedLightRegion();

    cv::Rect GetOrangeLightRegion();

    cv::Rect GetGreenLightRegion();

    TrafficSignalColor GetTrafficSignalColor();

private :

    cv::Rect red_light_region_ ;

    cv::Rect orange_light_region_ ;

    cv::Rect green_light_region_ ;

    TrafficSignalColor traffic_signal_color_;

};

#endif // TRAFFICSIGNALREGION_H
