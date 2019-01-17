#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>

#include <Buffer/vehicleblob.h>
#include <Buffer/infraction.h>


typedef enum{
    VEHICLE_UNCLASSED,
    VEHICLE_LIGHT,
    VEHICLE_HEAVY1,
    VEHICLE_HEAVY2
} VehicleClass;


class Vehicle
{
public:
    Vehicle();

    void AddBlob(VehicleBlob blob);

    void AddSpeed(float speed);

    void AddClass(VehicleClass classe);

    void AddColor(std::string color);

    void AddMake(std::string make);

    void AddModel(std::string model);

    void AddRegionId(int r_id);

    void AddInfraction(Infraction inf);


    void SetBlobList(std::vector<VehicleBlob> blob_list);

    void SetSpeedList(std::vector<float> speed_list);

    void SetClassList(std::vector<VehicleClass> class_list);

    void SetColorList(std::vector<std::string> color_list);

    void SetMakeList(std::vector<std::string> make_list);

    void SetModelList(std::vector<std::string> model_list);

    void SetRegionIdList(std::vector<int> region_id_list);

    void SetInfractionList(std::vector<Infraction> infraction_list);

    void SetLP(std::string license_plate);

    void SetBlobByIndexAbsolu(VehicleBlob blob, unsigned long long int index_absolu);

    std::vector<VehicleBlob> GetBlobList();

    std::vector<float> GetSpeedList();

    std::vector<VehicleClass> GetClassList();

    std::vector<std::string> GetColorList();

    std::vector<std::string> GetMakeList();

    std::vector<std::string> GetModelList();

    std::vector<int> GetRegionIdList();

    std::vector<Infraction> GetInfractionList();


    unsigned long long int GetIdVehicle();

    VehicleBlob GetBlobByIndexAbsolu(unsigned long long int index_absolu);

    float GetCurrentSpeed();

    VehicleClass GetBestClass();

    std::string GetBestColor();

    std::string GetBestMake();

    std::string GetBestModel();

    std::string GetLP();


    bool IsClassified();

    bool IsRecognizedColor();

    bool IsRecognizedMake();

    bool IsRecognizedModel();

    bool IsRecognizedLP();

    void VehicleClassified();

    void VehicleRecognizedColor();

    void VehicleRecognizedMake();

    void VehicleRecognizedModel();

    void VehicleRecognizedLP();



private :

    static unsigned long long int nbr_tot_vehicle_ ;

    unsigned long long int id_vehicle_ ;

    std::vector<VehicleBlob> blob_list_ ;

    std::vector<float> speed_list_ ;

    std::vector<VehicleClass> class_list_ ;

    std::vector<std::string> color_list_ ;

    std::vector<std::string> make_list_ ;

    std::vector<std::string> model_list_ ;

    std::string license_plate_ ;

    std::vector<int> region_id_list_ ;

    std::vector<Infraction> infraction_list_ ;

    bool is_classified_ ;

    bool is_color_recognized_ ;

    bool is_make_recognized_ ;

    bool is_model_recognized_ ;

    bool is_lp_recognized_ ;
};

#endif // VEHICLE_H
