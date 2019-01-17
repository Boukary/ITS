#ifndef REGION_H
#define REGION_H

#include "opencv2/opencv.hpp"
#include <iostream>

class Region
{
public:

    Region();

    void SetPoints(cv::Point p1, cv::Point p2, cv::Point p3, cv::Point p4);

    void SetSpeedLimit(float speed_limit);

    bool IsInsideRegion(cv::Point centroid);

    bool IsCorrectDirection(cv::Point centroid_start, cv::Point centroid_end);

    cv::Point GetP1();

    cv::Point GetP2();

    cv::Point GetP3();

    cv::Point GetP4();

    float GetSpeedLimit();


private:

    int id_region_ ;

    cv::Point p1_ ;

    cv::Point p2_ ;

    cv::Point p3_ ;

    cv::Point p4_ ;

    float speed_limit_ ;

};

#endif // REGION_H
