#include "buffer.h"

using namespace std;
using namespace cv;

Buffer::Buffer()
{
    nbr_acquisition_traitee_ = 0;
    nbr_preprocessing_traitee_ = 0;
    nbr_detection_traitee_ = 0;
    nbr_tracking_traitee_ = 0;
    nbr_classification_traitee_ = 0;
    nbr_recognition_traitee_ = 0;
    nbr_speedestimation_traitee_ = 0;
    nbr_infractiondetection_traitee_ = 0;
    nbr_display_traitee_ = 0;

    mutex_list_vehicles_ = new QMutex;
}

void Buffer::SetConfig(ConfigBuffer config)
{
    config_ = config;
    infraction_proof_maker_.SetConfig(config_.config_infraction_proof_maker);
}

int Buffer::IsPreprocessingAvailable()
{
    while ( ((nbr_preprocessing_traitee_ % config_.size_frame_list_max) >= list_frames_.size()) || list_frames_[nbr_preprocessing_traitee_ % config_.size_frame_list_max].IsLocked() || (list_frames_[nbr_preprocessing_traitee_ % config_.size_frame_list_max].GetStatus() != FRAME_ACQUIRED) )
        cout.flush();
    return nbr_preprocessing_traitee_ % config_.size_frame_list_max;
}

int Buffer::IsDetectionAvailable()
{
    while (nbr_detection_traitee_ % config_.size_frame_list_max >= list_frames_.size() || list_frames_[nbr_detection_traitee_ % config_.size_frame_list_max].IsLocked() || (list_frames_[nbr_detection_traitee_ % config_.size_frame_list_max].GetStatus() != FRAME_PREPROCESSED) )
        cout.flush();
    return nbr_detection_traitee_ % config_.size_frame_list_max;
}

int Buffer::IsTrackingAvailable()
{
    while (nbr_tracking_traitee_ % config_.size_frame_list_max >= list_frames_.size() || list_frames_[nbr_tracking_traitee_ % config_.size_frame_list_max].IsLocked() || (list_frames_[nbr_tracking_traitee_ % config_.size_frame_list_max].GetStatus() != FRAME_DETECTED) )
        cout.flush();
    return nbr_tracking_traitee_ % config_.size_frame_list_max;
}

int Buffer::IsClassificationAvailable()
{
    while (nbr_classification_traitee_ % config_.size_frame_list_max >= list_frames_.size() || list_frames_[nbr_classification_traitee_ % config_.size_frame_list_max].IsLocked() || (list_frames_[nbr_classification_traitee_ % config_.size_frame_list_max].GetStatus() != FRAME_TRACKED) )
        cout.flush();
    return nbr_classification_traitee_ % config_.size_frame_list_max;
}

int Buffer::IsRecognitionAvailable()
{
    while (nbr_recognition_traitee_ % config_.size_frame_list_max >= list_frames_.size() || list_frames_[nbr_recognition_traitee_ % config_.size_frame_list_max].IsLocked() || (list_frames_[nbr_recognition_traitee_ % config_.size_frame_list_max].GetStatus() != FRAME_TRACKED) )
        cout.flush();
    return nbr_recognition_traitee_ % config_.size_frame_list_max;
}

int Buffer::IsSpeedEstimationAvailable()
{
    while (nbr_speedestimation_traitee_ % config_.size_frame_list_max >= list_frames_.size() || list_frames_[nbr_speedestimation_traitee_ % config_.size_frame_list_max].IsLocked() || (list_frames_[nbr_speedestimation_traitee_ % config_.size_frame_list_max].GetStatus() != FRAME_TRACKED) )
        cout.flush();
    return nbr_speedestimation_traitee_ % config_.size_frame_list_max;
}

int Buffer::IsInfractionDetectionAvailable()
{
    while (nbr_infractiondetection_traitee_ % config_.size_frame_list_max >= list_frames_.size() || list_frames_[nbr_infractiondetection_traitee_ % config_.size_frame_list_max].IsLocked() || (list_frames_[nbr_infractiondetection_traitee_ % config_.size_frame_list_max].GetStatus() != FRAME_TRACKED) )
        cout.flush();
    return nbr_infractiondetection_traitee_ % config_.size_frame_list_max;
}

int Buffer::IsDisplayAvailable()
{
    while (nbr_display_traitee_ % config_.size_frame_list_max >= list_frames_.size() || list_frames_[nbr_display_traitee_ % config_.size_frame_list_max].IsLocked() || (list_frames_[nbr_infractiondetection_traitee_ % config_.size_frame_list_max].GetStatus() != FRAME_TRACKED)
           || !list_frames_[nbr_display_traitee_ % config_.size_frame_list_max].IsClassificationDone()
           || !list_frames_[nbr_display_traitee_ % config_.size_frame_list_max].IsRecognitionDone()
           || !list_frames_[nbr_display_traitee_ % config_.size_frame_list_max].IsSpeedEstimationDone()
           || !list_frames_[nbr_display_traitee_ % config_.size_frame_list_max].IsInfractionDetectionDone())
        cout.flush();
    return nbr_display_traitee_ % config_.size_frame_list_max;
}

vector<Vehicle> Buffer::GetVehicles()
{
    LockVehicleList();
    vector<Vehicle> tmp = list_vehicles_;
    UnlockVehicleList();
    return tmp ;
}

unsigned long long Buffer::GetPreprocessingDataByIndex(int index, Mat &img_input_mono, Mat &img_input_stereo)
{
    unsigned long long index_absolu = 0;
    LockFrame(index);
    index_absolu = list_frames_[index].GetIndexAbsolu();
    list_frames_[index].GetImageInputMono()->copyTo(img_input_mono);
    list_frames_[index].GetImageInputStereo()->copyTo(img_input_stereo);
    UnlockFrame(index);
    return index_absolu;
}

unsigned long long Buffer::GetDetectionDataByIndex(int index, Mat &img_preprocessed_mono)
{
    unsigned long long index_absolu = 0;
    LockFrame(index);
    index_absolu = list_frames_[index].GetIndexAbsolu();
    list_frames_[index].GetImagePreprocessedMono()->copyTo(img_preprocessed_mono);
    UnlockFrame(index);
    return index_absolu;
}

unsigned long long Buffer::GetTrackingDataByIndex(int index, Mat &img_preprocessed_mono, vector<VehicleBlob> &blobs)
{
    unsigned long long index_absolu = 0;
    LockFrame(index);
    index_absolu = list_frames_[index].GetIndexAbsolu();
    list_frames_[index].GetImagePreprocessedMono()->copyTo(img_preprocessed_mono);
    blobs = *(list_frames_[index].GetVehiclesDetected());
    UnlockFrame(index);
    return index_absolu;
}

unsigned long long Buffer::GetClassificationDataByIndex(int index, Mat &img_preprocessed_mono)
{
    unsigned long long index_absolu = 0;
    LockFrame(index);
    index_absolu = list_frames_[index].GetIndexAbsolu();
    list_frames_[index].GetImagePreprocessedMono()->copyTo(img_preprocessed_mono);
    UnlockFrame(index);
    return index_absolu;
}

unsigned long long Buffer::GetRecognitionDataByIndex(int index, Mat &img_preprocessed_mono)
{
    unsigned long long index_absolu = 0;
    LockFrame(index);
    index_absolu = list_frames_[index].GetIndexAbsolu();
    list_frames_[index].GetImagePreprocessedMono()->copyTo(img_preprocessed_mono);
    UnlockFrame(index);
    return index_absolu;
}

unsigned long long Buffer::GetSpeedEstimationDataByIndex(int index, Mat &img_preprocessed_mono, Mat &img_preprocessed_stereo)
{
    unsigned long long index_absolu = 0;
    LockFrame(index);
    index_absolu = list_frames_[index].GetIndexAbsolu();
    list_frames_[index].GetImagePreprocessedMono()->copyTo(img_preprocessed_mono);
    list_frames_[index].GetImagePreprocessedStereo()->copyTo(img_preprocessed_stereo);
    UnlockFrame(index);
    return index_absolu;
}

unsigned long long Buffer::GetInfractionDetectionDataByIndex(int index, Mat &img_preprocessed_mono)
{
    unsigned long long index_absolu = 0;
    LockFrame(index);
    index_absolu = list_frames_[index].GetIndexAbsolu();
    list_frames_[index].GetImagePreprocessedMono()->copyTo(img_preprocessed_mono);
    UnlockFrame(index);
    return index_absolu;
}

unsigned long long Buffer::GetDisplayDataByIndex(int index, Mat &img_preprocessed_mono)
{
    unsigned long long index_absolu = 0;
    LockFrame(index);
    index_absolu = list_frames_[index].GetIndexAbsolu();
    list_frames_[index].GetImagePreprocessedMono()->copyTo(img_preprocessed_mono);
    UnlockFrame(index);
    return index_absolu;
}

bool Buffer::AddFrameMono(Mat *image)
{
    if(image->empty()){
        cout<<"Buffer :: Image Mono Empty !!! "<<endl;
        return false;
    }

    if (list_frames_.size() < config_.size_frame_list_max){
        Frame frame(false);
        frame.SetIndexAbsolu(nbr_acquisition_traitee_);
        frame.SetImageInputMono(image);
        list_frames_.push_back(frame);
    }
    else {
        LockFrame(nbr_acquisition_traitee_ % config_.size_frame_list_max);
        list_frames_[nbr_acquisition_traitee_ % config_.size_frame_list_max].ResetFrame();
        list_frames_[nbr_acquisition_traitee_ % config_.size_frame_list_max].SetIndexAbsolu(nbr_acquisition_traitee_);
        list_frames_[nbr_acquisition_traitee_ % config_.size_frame_list_max].SetImageInputMono(image);
        UnlockFrame(nbr_acquisition_traitee_ % config_.size_frame_list_max);
    }

    cout<<"Acquisition --> Frame "<<nbr_acquisition_traitee_<<endl;
    nbr_acquisition_traitee_++;
    return true;
}

bool Buffer::AddFrameStereo(Mat *image_left, Mat *image_right)
{
    if(image_left->empty()){
        cout<<"Buffer :: Image Stereo Left Empty !!! "<<endl;
        return false;
    }

    if(image_right->empty()){
        cout<<"Buffer :: Image Stereo Right Empty !!! "<<endl;
        return false;
    }

    if (list_frames_.size() < config_.size_frame_list_max){
        Frame frame(true);
        frame.SetIndexAbsolu(nbr_acquisition_traitee_);
        frame.SetImageInputStereo(image_left,image_right);
        list_frames_.push_back(frame);
    }
    else {
        LockFrame(nbr_acquisition_traitee_ % config_.size_frame_list_max);
        list_frames_[nbr_acquisition_traitee_ % config_.size_frame_list_max].ResetFrame();
        list_frames_[nbr_acquisition_traitee_ % config_.size_frame_list_max].SetIndexAbsolu(nbr_acquisition_traitee_);
        list_frames_[nbr_acquisition_traitee_ % config_.size_frame_list_max].SetImageInputStereo(image_left,image_right);
        UnlockFrame(nbr_acquisition_traitee_ % config_.size_frame_list_max);
    }

    cout<<"Acquisition --> Frame "<<nbr_acquisition_traitee_<<endl;
    nbr_acquisition_traitee_++;
    return true;
}

bool Buffer::SetPreprocessingDataByIndex(int index, unsigned long long index_absolu, Mat *img_preprocessed_mono, Mat *img_preprocessed_stereo)
{
    LockFrame(index);
    if (list_frames_[index].GetIndexAbsolu() != index_absolu){
        UnlockFrame(index);
        return false;
    }

    if (!list_frames_[index].IsStereo())
        list_frames_[index].SetImagePreprocessedMono(img_preprocessed_mono);
    else
        list_frames_[index].SetImagePreprocessedStereo(img_preprocessed_mono,img_preprocessed_stereo);
    infraction_proof_maker_.AddImageIndexed(img_preprocessed_mono,index_absolu);
    UnlockFrame(index);

    cout<<"###### Preprocessing --> Frame "<<nbr_preprocessing_traitee_<<endl;
    nbr_preprocessing_traitee_++;
    return true;
}

bool Buffer::SetDetectionDataByIndex(int index, unsigned long long index_absolu, std::vector<VehicleBlob> *blobs)
{
    LockFrame(index);
    if (list_frames_[index].GetIndexAbsolu() != index_absolu){
        UnlockFrame(index);
        return false;
    }
    list_frames_[index].SetVehiclesDetected(blobs);
    UnlockFrame(index);

    cout<<"############ Detection --> Frame "<<nbr_detection_traitee_<<endl;
    nbr_detection_traitee_++;
    return true;
}

bool Buffer::SetTrackingDataByIndex(int index, unsigned long long index_absolu)
{
    LockFrame(index);
    if (list_frames_[index].GetIndexAbsolu() != index_absolu){
        UnlockFrame(index);
        return false;
    }
    list_frames_[index].SetFrameTracked();
    UnlockFrame(index);

    cout<<"################## Tracking --> Frame "<<nbr_tracking_traitee_<<endl;
    nbr_tracking_traitee_++;
    return true;
}

bool Buffer::SetClassificationDataByIndex(int index, unsigned long long index_absolu)
{
    LockFrame(index);
    if (list_frames_[index].GetIndexAbsolu() != index_absolu){
        UnlockFrame(index);
        return false;
    }
    list_frames_[index].ClassificationDone();
    UnlockFrame(index);

    cout<<"######################## Classification --> Frame "<<nbr_classification_traitee_<<endl;
    nbr_classification_traitee_++;
    return true;
}

bool Buffer::SetRecognitionDataByIndex(int index, unsigned long long index_absolu)
{
    LockFrame(index);
    if (list_frames_[index].GetIndexAbsolu() != index_absolu){
        UnlockFrame(index);
        return false;
    }
    list_frames_[index].RecognitionDone();
    UnlockFrame(index);

    cout<<"######################## Recognition --> Frame "<<nbr_recognition_traitee_<<endl;
    nbr_recognition_traitee_++;
    return true;
}

bool Buffer::SetSpeedEstimationDataByIndex(int index, unsigned long long index_absolu)
{
    LockFrame(index);
    if (list_frames_[index].GetIndexAbsolu() != index_absolu){
        UnlockFrame(index);
        return false;
    }
    list_frames_[index].SpeedEstimationDone();
    UnlockFrame(index);

    cout<<"######################## SpeedEstimation --> Frame "<<nbr_speedestimation_traitee_<<endl;
    nbr_speedestimation_traitee_++;
    return true;
}

bool Buffer::SetInfractionDetectionDataByIndex(int index, unsigned long long index_absolu)
{
    LockFrame(index);
    if (list_frames_[index].GetIndexAbsolu() != index_absolu){
        UnlockFrame(index);
        return false;
    }
    list_frames_[index].InfractionDetectionDone();
    UnlockFrame(index);

    cout<<"######################## InfractionDetection --> Frame "<<nbr_infractiondetection_traitee_<<endl;
    nbr_infractiondetection_traitee_++;
    return true;
}

bool Buffer::SetDisplayDataByIndex(int index, unsigned long long index_absolu, Mat *img_display)
{
    LockFrame(index);
    if (list_frames_[index].GetIndexAbsolu() != index_absolu){
        UnlockFrame(index);
        return false;
    }
    list_frames_[index].SetImageDisplay(img_display);
    UnlockFrame(index);

    cout<<"############################## Display --> Frame "<<nbr_display_traitee_<<endl;
    nbr_display_traitee_++;
    return true;
}

bool Buffer::UpdateVehicleListByTracking(std::vector<Vehicle> *new_vehicles)
{
    LockVehicleList();
    for (int i=0;i<new_vehicles->size(); i++)
        for (int j=0;j<list_vehicles_.size(); j++)
            if (new_vehicles->at(i).GetIdVehicle() == list_vehicles_.at(j).GetIdVehicle()){
                new_vehicles->at(i).SetClassList(list_vehicles_.at(j).GetClassList());
                new_vehicles->at(i).SetColorList(list_vehicles_.at(j).GetColorList());
                new_vehicles->at(i).SetMakeList(list_vehicles_.at(j).GetMakeList());
                new_vehicles->at(i).SetModelList(list_vehicles_.at(j).GetModelList());
                new_vehicles->at(i).SetSpeedList(list_vehicles_.at(j).GetSpeedList());
                new_vehicles->at(i).SetInfractionList(list_vehicles_.at(j).GetInfractionList());
                new_vehicles->at(i).SetLP(list_vehicles_.at(j).GetLP());

                if (list_vehicles_.at(j).IsClassified())
                    new_vehicles->at(i).VehicleClassified();
                if (list_vehicles_.at(j).IsRecognizedColor())
                    new_vehicles->at(i).VehicleRecognizedColor();
                if (list_vehicles_.at(j).IsRecognizedMake())
                    new_vehicles->at(i).VehicleRecognizedMake();
                if (list_vehicles_.at(j).IsRecognizedModel())
                    new_vehicles->at(i).VehicleRecognizedModel();
                if (list_vehicles_.at(j).IsRecognizedLP())
                    new_vehicles->at(i).VehicleRecognizedLP();

            }
    list_vehicles_ = *new_vehicles;
    UnlockVehicleList();

    return true;
}

bool Buffer::UpdateVehicleListByClassification(std::vector<Vehicle> *new_vehicles)
{
    LockVehicleList();
    for (int i=0;i<new_vehicles->size(); i++)
        for (int j=0;j<list_vehicles_.size(); j++)
            if (new_vehicles->at(i).GetIdVehicle() == list_vehicles_.at(j).GetIdVehicle()){
                list_vehicles_.at(j).SetClassList(new_vehicles->at(i).GetClassList());
                if (new_vehicles->at(i).IsClassified())
                    list_vehicles_.at(j).VehicleClassified();
                break;
            }
    UnlockVehicleList();

    return true;
}

bool Buffer::UpdateVehicleListByRecognition(std::vector<Vehicle> *new_vehicles)
{
    LockVehicleList();
    for (int i=0;i<new_vehicles->size(); i++)
        for (int j=0;j<list_vehicles_.size(); j++)
            if (new_vehicles->at(i).GetIdVehicle() == list_vehicles_.at(j).GetIdVehicle()){

                list_vehicles_.at(j).SetColorList(new_vehicles->at(i).GetColorList());
                list_vehicles_.at(j).SetMakeList(new_vehicles->at(i).GetMakeList());
                list_vehicles_.at(j).SetModelList(new_vehicles->at(i).GetModelList());
                list_vehicles_.at(j).SetLP(new_vehicles->at(i).GetLP());

                if (new_vehicles->at(i).IsRecognizedColor())
                    list_vehicles_.at(j).VehicleRecognizedColor();
                if (new_vehicles->at(i).IsRecognizedMake())
                    list_vehicles_.at(j).VehicleRecognizedMake();
                if (new_vehicles->at(i).IsRecognizedModel())
                    list_vehicles_.at(j).VehicleRecognizedModel();
                if (new_vehicles->at(i).IsRecognizedLP())
                    list_vehicles_.at(j).VehicleRecognizedLP();
                break;
            }
    UnlockVehicleList();

    return true;
}

bool Buffer::UpdateVehicleListBySpeedEstimation(std::vector<Vehicle> *new_vehicles, unsigned long long index_absolu)
{
    LockVehicleList();
    for (int i=0;i<new_vehicles->size(); i++)
        for (int j=0;j<list_vehicles_.size(); j++)
            if (new_vehicles->at(i).GetIdVehicle() == list_vehicles_.at(j).GetIdVehicle()){
                list_vehicles_.at(j).SetSpeedList(new_vehicles->at(i).GetSpeedList());
                list_vehicles_.at(j).SetBlobByIndexAbsolu(new_vehicles->at(i).GetBlobByIndexAbsolu(index_absolu), index_absolu);
                break;
            }
    UnlockVehicleList();

    return true;
}

bool Buffer::UpdateVehicleListByInfractionDetection(std::vector<Vehicle> *new_vehicles)
{
    LockVehicleList();
    for (int i=0;i<new_vehicles->size(); i++)
        for (int j=0;j<list_vehicles_.size(); j++)
            if (new_vehicles->at(i).GetIdVehicle() == list_vehicles_.at(j).GetIdVehicle()){
                list_vehicles_.at(j).SetInfractionList(new_vehicles->at(i).GetInfractionList());
                break;
            }
    UnlockVehicleList();

    return true;
}

void Buffer::SkipDetectionInFrame(int index)
{
    LockFrame(index);
    list_frames_[index].SkipDetection();
    UnlockFrame(index);

    cout<<"############ Detection --> Frame(Skiped) "<<nbr_detection_traitee_<<endl;
    nbr_detection_traitee_++;
}

ConfigScene *Buffer::GetConfigScene()
{
    return &configuration_scene_ ;
}

void Buffer::SetConfigScene(ConfigScene cs)
{
    configuration_scene_ = cs ;
}

InfractionProofMaker *Buffer::GetProofElementMaker()
{
    return &infraction_proof_maker_ ;
}

void Buffer::SetProofElementMaker(InfractionProofMaker prm)
{
    infraction_proof_maker_ = prm ;
}

void Buffer::LockFrame(int index)
{
    list_frames_[index].Lock();
}

void Buffer::UnlockFrame(int index)
{
    list_frames_[index].Unlock();
}

void Buffer::LockVehicleList()
{
    while(!mutex_list_vehicles_->tryLock());
}

void Buffer::UnlockVehicleList()
{
    mutex_list_vehicles_->unlock();
}
