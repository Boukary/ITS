#include "region.h"

using namespace std;
using namespace cv;

Region::Region()
{

}

void Region::SetPoints(Point p1, Point p2, Point p3, Point p4)
{
    p1_ = p1;
    p2_ = p2;
    p3_ = p3;
    p4_ = p4;
}

void Region::SetSpeedLimit(float speed_limit)
{
    speed_limit_ = speed_limit;
}

bool Region::IsInsideRegion(Point centroid)
{

}

bool Region::IsCorrectDirection(Point centroid_start, Point centroid_end)
{

}

Point Region::GetP1()
{
    return p1_;
}

Point Region::GetP2()
{
    return p2_;
}

Point Region::GetP3()
{
    return p3_;
}

Point Region::GetP4()
{
    return p4_;
}

float Region::GetSpeedLimit()
{
    return speed_limit_;
}
