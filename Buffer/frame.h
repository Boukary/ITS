#ifndef FRAME_H
#define FRAME_H

#include <QMutex>

#include "opencv2/opencv.hpp"
#include <iostream>

#include <Buffer/vehicleblob.h>

typedef enum{
    FRAME_INVALID,
    FRAME_ACQUIRED,
    FRAME_PREPROCESSED,
    FRAME_DETECTED,
    FRAME_TRACKED,
    FRAME_DISPLAYED
} FrameStatus;


class Frame
{
public:

    Frame(bool is_stereo = true);

    void ResetFrame();

    unsigned long long int GetIndexAbsolu();

    void SetIndexAbsolu(unsigned long long int index_absolu);

    cv::Mat* GetImageInputMono();

    cv::Mat* GetImagePreprocessedMono();

    cv::Mat* GetImageInputStereo();

    cv::Mat* GetImagePreprocessedStereo();

    std::vector<VehicleBlob>* GetVehiclesDetected();

    cv::Mat* GetImageDisplay();

    void SetImageInputMono(cv::Mat *image_input_mono);

    void SetImagePreprocessedMono(cv::Mat *image_preprocessed_mono);

    void SetImageInputStereo(cv::Mat *image_input_mono, cv::Mat *image_input_stereo);

    void SetImagePreprocessedStereo(cv::Mat *image_preprocessed_mono, cv::Mat *image_preprocessed_stereo);

    void SetVehiclesDetected(std::vector<VehicleBlob> *vehicles_detected);

    void SetFrameTracked();

    void SetImageDisplay(cv::Mat *image_display);

    void Lock();

    void Unlock();

    bool IsLocked();

    bool IsStereo();

    void ClassificationDone();

    void RecognitionDone();

    void SpeedEstimationDone();

    void InfractionDetectionDone();

    bool IsClassificationDone();

    bool IsRecognitionDone();

    bool IsSpeedEstimationDone();

    bool IsInfractionDetectionDone();

    void SkipDetection();

    FrameStatus GetStatus();



private :

    unsigned long long int index_absolu_ ;

    QMutex* mutex_ ;

    cv::Mat image_input_mono_ ;

    cv::Mat image_input_stereo_ ;

    cv::Mat image_preprocessed_mono_ ;

    cv::Mat image_preprocessed_stereo_ ;

    cv::Mat image_display_ ;

    std::vector<VehicleBlob> vehicles_detected_ ;

    FrameStatus status_ ;

    bool is_locked_ ;

    bool is_stereo_ ;

    bool classification_ok_ ;

    bool recognition_ok_ ;

    bool speed_estimation_ok_ ;

    bool infraction_detection_ok_ ;

};

#endif // FRAME_H
