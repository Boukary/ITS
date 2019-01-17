#ifndef BUFFER_H
#define BUFFER_H

#include <QObject>

#include "opencv2/opencv.hpp"
#include <iostream>

#include <Buffer/frame.h>
#include <Buffer/vehicle.h>
#include <Buffer/vehicleblob.h>
#include <Buffer/infractionproofmaker.h>
#include <Buffer/configscene.h>

struct ConfigBuffer{
    int size_frame_list_max;
    ConfigInfractionProofMaker config_infraction_proof_maker;
};


class Buffer : public QObject
{
    Q_OBJECT
public:

    Buffer();

    void SetConfig(ConfigBuffer config);

    int IsPreprocessingAvailable();

    int IsDetectionAvailable();

    int IsTrackingAvailable();

    int IsClassificationAvailable();

    int IsRecognitionAvailable();

    int IsSpeedEstimationAvailable();

    int IsInfractionDetectionAvailable();

    int IsDisplayAvailable();

    std::vector<Vehicle> GetVehicles();

    unsigned long long int GetPreprocessingDataByIndex(int index, cv::Mat& img_input_mono, cv::Mat& img_input_stereo);

    unsigned long long int GetDetectionDataByIndex(int index, cv::Mat& img_preprocessed_mono);

    unsigned long long int GetTrackingDataByIndex(int index, cv::Mat& img_preprocessed_mono, std::vector<VehicleBlob>& blobs);

    unsigned long long int GetClassificationDataByIndex(int index, cv::Mat& img_preprocessed_mono);

    unsigned long long int GetRecognitionDataByIndex(int index, cv::Mat& img_preprocessed_mono);

    unsigned long long int GetSpeedEstimationDataByIndex(int index, cv::Mat& img_preprocessed_mono, cv::Mat& img_preprocessed_stereo);

    unsigned long long int GetInfractionDetectionDataByIndex(int index, cv::Mat& img_preprocessed_mono);

    unsigned long long int GetDisplayDataByIndex(int index, cv::Mat& img_preprocessed_mono);

    bool AddFrameMono(cv::Mat *image);

    bool AddFrameStereo(cv::Mat *image_left, cv::Mat *image_right);

    bool SetPreprocessingDataByIndex(int index, unsigned long long int index_absolu, cv::Mat* img_preprocessed_mono, cv::Mat* img_preprocessed_stereo);

    bool SetDetectionDataByIndex(int index, unsigned long long int index_absolu,  std::vector<VehicleBlob> *blobs);

    bool SetTrackingDataByIndex(int index, unsigned long long int index_absolu);

    bool SetClassificationDataByIndex(int index, unsigned long long int index_absolu);

    bool SetRecognitionDataByIndex(int index, unsigned long long int index_absolu);

    bool SetSpeedEstimationDataByIndex(int index, unsigned long long int index_absolu);

    bool SetInfractionDetectionDataByIndex(int index, unsigned long long int index_absolu);

    bool SetDisplayDataByIndex(int index, unsigned long long int index_absolu, cv::Mat* img_display);

    bool UpdateVehicleListByTracking(std::vector<Vehicle>* new_vehicles);
    
    bool UpdateVehicleListByClassification(std::vector<Vehicle>* new_vehicles);
    
    bool UpdateVehicleListByRecognition(std::vector<Vehicle>* new_vehicles);
    
    bool UpdateVehicleListBySpeedEstimation(std::vector<Vehicle>* new_vehicles, unsigned long long index_absolu);
    
    bool UpdateVehicleListByInfractionDetection(std::vector<Vehicle>* new_vehicles);

    void SkipDetectionInFrame(int index);

    ConfigScene* GetConfigScene();

    void SetConfigScene(ConfigScene cs) ;

    InfractionProofMaker* GetProofElementMaker() ;

    void SetProofElementMaker(InfractionProofMaker  prm) ;


private :

    void LockFrame(int index);

    void UnlockFrame(int index);

    void LockVehicleList();

    void UnlockVehicleList();

signals:

public slots:



private:

    std::vector<Frame> list_frames_ ;

    std::vector<Vehicle> list_vehicles_ ;

    ConfigScene configuration_scene_ ;

    InfractionProofMaker infraction_proof_maker_ ;

    unsigned long long int nbr_acquisition_traitee_ ;

    unsigned long long int nbr_preprocessing_traitee_ ;

    unsigned long long int nbr_detection_traitee_ ;

    unsigned long long int nbr_tracking_traitee_ ;

    unsigned long long int nbr_classification_traitee_ ;

    unsigned long long int nbr_recognition_traitee_ ;

    unsigned long long int nbr_speedestimation_traitee_ ;

    unsigned long long int nbr_infractiondetection_traitee_ ;

    unsigned long long int nbr_display_traitee_ ;

    QMutex* mutex_list_vehicles_ ;

    ConfigBuffer config_;

};

#endif // BUFFER_H


// pourdisplay cvmat2qimage
