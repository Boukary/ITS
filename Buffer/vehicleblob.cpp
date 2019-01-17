#include "vehicleblob.h"

using namespace std;
using namespace cv;

VehicleBlob::VehicleBlob()
{

}

unsigned long long VehicleBlob::GetIndexAbsolu()
{
    return index_absolu_ ;
}

void VehicleBlob::SetIndexAbsolu(unsigned long long index_absolu)
{
    index_absolu_ = index_absolu ;
}

void VehicleBlob::SetScope(Rect bbox)
{
    bbox_ = bbox ;
}

void VehicleBlob::SetCentroidImage2D(Point centroid_image_2d)
{
    centroid_image_2d_ = centroid_image_2d;
}

void VehicleBlob::SetCentroidWorld3D(Point3f centroid_world_3d)
{
    centroid_world_3d_ = centroid_world_3d;
}

Rect VehicleBlob::GetScope()
{
    return bbox_;
}

Point VehicleBlob::GetCentroidImage2D()
{
    return centroid_image_2d_ ;
}

Point3f VehicleBlob::GetCentroidWorld3D()
{
    return centroid_world_3d_ ;
}


