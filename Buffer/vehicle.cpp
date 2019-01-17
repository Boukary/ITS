#include "vehicle.h"

using namespace std;

unsigned long long int Vehicle::nbr_tot_vehicle_ = 0;

Vehicle::Vehicle()
{
    id_vehicle_ = nbr_tot_vehicle_++;
    is_classified_ = is_color_recognized_ = is_make_recognized_ = is_model_recognized_ = is_lp_recognized_ = false;
    license_plate_ = "";
}

void Vehicle::AddBlob(VehicleBlob blob)
{
    blob_list_.push_back(blob);
}

void Vehicle::AddSpeed(float speed)
{
    speed_list_.push_back(speed);
}

void Vehicle::AddClass(VehicleClass classe)
{
    class_list_.push_back(classe);
}

void Vehicle::AddColor(string color)
{
    color_list_.push_back(color);
}

void Vehicle::AddMake(string make)
{
    make_list_.push_back(make);
}

void Vehicle::AddModel(string model)
{
    model_list_.push_back(model);
}

void Vehicle::AddRegionId(int r_id)
{
    region_id_list_.push_back(r_id);
}

void Vehicle::AddInfraction(Infraction inf)
{
    infraction_list_.push_back(inf);
}

void Vehicle::SetBlobList(std::vector<VehicleBlob> blob_list)
{
    blob_list_ = blob_list;
}

void Vehicle::SetSpeedList(std::vector<float> speed_list)
{
    speed_list_ = speed_list;
}

void Vehicle::SetClassList(std::vector<VehicleClass> class_list)
{
    class_list_ = class_list;
}

void Vehicle::SetColorList(std::vector<string> color_list)
{
    color_list_ = color_list;
}

void Vehicle::SetMakeList(std::vector<string> make_list)
{
    make_list_ = make_list;
}

void Vehicle::SetModelList(std::vector<string> model_list)
{
    model_list_ = model_list;
}

void Vehicle::SetRegionIdList(std::vector<int> region_id_list)
{
    region_id_list_ = region_id_list;
}

void Vehicle::SetInfractionList(std::vector<Infraction> infraction_list)
{
    infraction_list_ = infraction_list;
}

void Vehicle::SetLP(string license_plate)
{
    license_plate_ = license_plate;
}

void Vehicle::SetBlobByIndexAbsolu(VehicleBlob blob, unsigned long long index_absolu)
{
    for(int i=0; i<blob_list_.size(); i++)
        if (blob_list_.at(i).GetIndexAbsolu() == index_absolu)
            blob_list_.at(i) = blob;
}

vector<VehicleBlob> Vehicle::GetBlobList()
{
    return blob_list_;
}

vector<float> Vehicle::GetSpeedList()
{
    return speed_list_;
}

std::vector<VehicleClass> Vehicle::GetClassList()
{
    return class_list_;
}

std::vector<string> Vehicle::GetColorList()
{
    return color_list_;
}

std::vector<string> Vehicle::GetMakeList()
{
    return make_list_;
}

std::vector<string> Vehicle::GetModelList()
{
    return model_list_;
}

vector<int> Vehicle::GetRegionIdList()
{
    return region_id_list_;
}

vector<Infraction> Vehicle::GetInfractionList()
{
    return infraction_list_;
}

unsigned long long Vehicle::GetIdVehicle()
{
    return id_vehicle_;
}

VehicleBlob Vehicle::GetBlobByIndexAbsolu(unsigned long long index_absolu)
{
    for(int i=0; i<blob_list_.size(); i++)
        if (blob_list_.at(i).GetIndexAbsolu() == index_absolu)
            return blob_list_.at(i);
    return VehicleBlob();
}

float Vehicle::GetCurrentSpeed()
{
    return speed_list_.back();
}

VehicleClass Vehicle::GetBestClass()
{
    return class_list_.back();
}

string Vehicle::GetBestColor()
{
    return color_list_.back();
}

string Vehicle::GetBestMake()
{
    return make_list_.back();
}

string Vehicle::GetBestModel()
{
    return model_list_.back();
}

string Vehicle::GetLP()
{
    return license_plate_;
}

bool Vehicle::IsClassified()
{
    return is_classified_;
}

bool Vehicle::IsRecognizedColor()
{
    return is_color_recognized_;
}

bool Vehicle::IsRecognizedMake()
{
    return is_make_recognized_;
}

bool Vehicle::IsRecognizedModel()
{
    return is_model_recognized_;
}

bool Vehicle::IsRecognizedLP()
{
    return is_lp_recognized_;
}

void Vehicle::VehicleClassified()
{
    is_classified_ = true ;
}

void Vehicle::VehicleRecognizedColor()
{
    is_color_recognized_ = true ;
}

void Vehicle::VehicleRecognizedMake()
{
    is_make_recognized_ = true ;
}

void Vehicle::VehicleRecognizedModel()
{
    is_model_recognized_ = true ;
}

void Vehicle::VehicleRecognizedLP()
{
    is_lp_recognized_ = true ;
}
