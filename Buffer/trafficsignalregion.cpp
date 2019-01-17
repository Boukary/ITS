#include "trafficsignalregion.h"

using namespace std;
using namespace cv;

TrafficSignalRegion::TrafficSignalRegion(Rect r_s, Rect o_s, Rect g_s)
{
    red_light_region_ = r_s;
    orange_light_region_ = o_s;
    green_light_region_ = g_s;
    traffic_signal_color_ = COLOR_NONE;
}

void TrafficSignalRegion::SetTrafficSignalRects(Rect r_s, Rect o_s, Rect g_s)
{
    red_light_region_ = r_s;
    orange_light_region_ = o_s;
    green_light_region_ = g_s;
}

void TrafficSignalRegion::SetTrafficSignalColor(TrafficSignalColor traffic_signal_color)
{
    traffic_signal_color_ = traffic_signal_color;
}

Rect TrafficSignalRegion::GetRedLightRegion()
{
    return red_light_region_;
}

Rect TrafficSignalRegion::GetOrangeLightRegion()
{
    return orange_light_region_;
}

Rect TrafficSignalRegion::GetGreenLightRegion()
{
    return green_light_region_;
}

TrafficSignalColor TrafficSignalRegion::GetTrafficSignalColor()
{
    return traffic_signal_color_;
}
