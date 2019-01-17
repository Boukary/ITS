#ifndef DETECTION_H
#define DETECTION_H

#include <QThread>

#include "opencv2/opencv.hpp"
#include "opencv2/dnn.hpp"
#include <iostream>

#include <Buffer/buffer.h>
#include <Detection/bgslibrary/package_bgs/bgslibrary.h>

enum DetectionMethod
{
    DM_YOLO,
    DM_VIOLA_JONES,
    DM_BGS
};

enum AlgoBGS
{
    BGS_AdaptiveBackgroundLearning,
    BGS_AdaptiveSelectiveBackgroundLearning,
    BGS_CodeBook,
    BGS_DPAdaptiveMedian,
    BGS_DPEigenbackground,
    BGS_DPGrimsonGMM,
    BGS_DPMean,
    BGS_DPPratiMediod,
    BGS_DPTexture,
    BGS_DPWrenGA,
    BGS_DPZivkovicAGMM,
    BGS_FrameDifference,
    BGS_FuzzyChoquetIntegral,
    BGS_FuzzySugenoIntegral,
    BGS_GMG,
    BGS_IndependentMultimodal,
    BGS_KDE,
    BGS_KNN,
    BGS_LBAdaptiveSOM,
    BGS_LBFuzzyAdaptiveSOM,
    BGS_LBFuzzyGaussian,
    BGS_LBMixtureOfGaussians,
    BGS_LBP_MRF,
    BGS_LBSimpleGaussian,
    BGS_LOBSTER,
    BGS_MixtureOfGaussianV1,
    BGS_MixtureOfGaussianV2,
    BGS_MultiCue,
    BGS_MultiLayer,
    BGS_PAWCS,
    BGS_PixelBasedAdaptiveSegmenter,
    BGS_SigmaDelta,
    BGS_StaticFrameDifference,
    BGS_SuBSENSE,
    BGS_T2FGMM_UM,
    BGS_T2FGMM_UV,
    BGS_T2FMRF_UM,
    BGS_T2FMRF_UV,
    BGS_TwoPoints,
    BGS_ViBe,
    BGS_VuMeter,
    BGS_WeightedMovingMean,
    BGS_WeightedMovingVariance
};

struct ConfigDetection{
    DetectionMethod detection_method;
    int nbr_skip_detection;
    int min_car_w;
    int min_car_h;
    int max_car_w;
    int max_car_h;

    // Yolo
    std::string model_path;
    std::string config_path;
    cv::Size model_input_size;
    float model_input_scale;
    float confidence_threshold;
    float nms_threshold;

    // Viola and Jones
    std::string cascade_path;
    double scale_factor;
    int min_neighbors;

    // Background Subtraction
    AlgoBGS algo_bgs;
    int threshold;
    int erode_size;
    int dilate_size;
};

class Detection : public QThread
{
    Q_OBJECT
public:

    Detection(Buffer* buffer);

    void SetConfig(ConfigDetection config);

    void Start();

    void Stop();

signals:

public slots:

private:

    void run();

    bool Init();

    bool MainFunction();

    bool DetectYolo();

    bool DetectViolaJones();

    bool DetectBG();

    bool LoadModelYolo();

    bool LoadModelViolasJones();

    bool LoadBGS();

    Buffer* buffer_;

    cv::dnn::Net net_;

    cv::Mat blob_4d_;

    std::vector<cv::Mat> net_outs_;

    std::vector<cv::String> out_layers_names_;

    std::vector<float> out_confidences_;

    std::vector<cv::Rect> out_boxes_;

    std::vector<int> out_nms_indices_;

    CascadeClassifier car_cascade_;

    IBGS *bgs_;

    int index_skip_detection_ ;

    ConfigDetection config_;

    cv::Mat image_;

    std::vector<VehicleBlob> blobs_;

    bool is_running_;

    float fps_;
};

#endif // DETECTION_H
