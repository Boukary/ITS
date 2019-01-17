#ifndef VEHICLEBLOB_H
#define VEHICLEBLOB_H

#include "opencv2/opencv.hpp"
#include <iostream>

class VehicleBlob
{
public:
    VehicleBlob();

    unsigned long long int GetIndexAbsolu();

    void SetIndexAbsolu(unsigned long long int index_absolu);

    void SetScope (cv::Rect bbox);

    void SetCentroidImage2D(cv::Point centroid_image_2d);

    void SetCentroidWorld3D(cv::Point3f centroid_world_3d);

    cv::Rect GetScope();

    cv::Point GetCentroidImage2D();

    cv::Point3f GetCentroidWorld3D();


private :

    unsigned long long int index_absolu_ ;

    cv::Rect bbox_ ;

    cv::Point centroid_image_2d_ ;

    cv::Point3f centroid_world_3d_ ;

};

#endif // VEHICLEBLOB_H
