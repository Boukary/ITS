#include "detection.h"

using namespace std;
using namespace cv;
using namespace dnn;

Detection::Detection(Buffer *buffer)
{
    buffer_ = buffer;
    is_running_ = false;
    index_skip_detection_ = 0;
}

void Detection::SetConfig(ConfigDetection config)
{
    config_ = config;
}

bool Detection::Init()
{
    switch (config_.detection_method) {
    case DM_YOLO:
        return LoadModelYolo();
    case DM_VIOLA_JONES:
        return LoadModelViolasJones();
    case DM_BGS:
        return LoadBGS();
    }
}

void Detection::Start()
{
    is_running_ = true;
    this->start();
}

void Detection::Stop()
{
    is_running_ = false;
}

bool Detection::MainFunction()
{
    int index = buffer_->IsDetectionAvailable();

    if (config_.nbr_skip_detection != index_skip_detection_){
        index_skip_detection_++;
        buffer_->SkipDetectionInFrame(index);
        return true;
    }

    index_skip_detection_ = 0;

    unsigned long long index_absolu = buffer_->GetDetectionDataByIndex(index,image_);

    if (image_.empty())
        return false;

    blobs_.clear();
    switch (config_.detection_method) {
    case DM_YOLO:
        if (!DetectYolo())
            return false;
        break;
    case DM_VIOLA_JONES:
        if (!DetectViolaJones())
            return false;
        break;
    case DM_BGS:
        if (!DetectBG())
            return false;
        break;
    }
    for(int i=0; i<blobs_.size(); i++)
        blobs_[i].SetIndexAbsolu(index_absolu);

    // Draw blobs
    cout<<"Blobs : "<<blobs_.size()<<endl;
    for(int i=0; i<blobs_.size(); i++){
        Rect bbox = blobs_[i].GetScope();
        rectangle(image_, Point(bbox.x, bbox.y), Point((bbox.x + bbox.width),(bbox.y + bbox.height)), Scalar(0, 255, 0), 2, 8, 0);
    }
    imshow("Blobs",image_);
    waitKey(1);

    return buffer_->SetDetectionDataByIndex(index,index_absolu,&blobs_);
}

bool Detection::DetectYolo()
{
    if (out_layers_names_.empty())
        return false;

    out_confidences_.clear();
    out_boxes_.clear();
    out_nms_indices_.clear();

    Mat scores;
    Point classIdPoint;
    double confidence;
    int left, top, width, height;

    // Create a 4D blob from a frame.
    blobFromImage(image_, blob_4d_, config_.model_input_scale, config_.model_input_size, Scalar(), true, false);

    // Run a model.
    net_.setInput(blob_4d_);
    net_.forward(net_outs_, out_layers_names_);

    for (size_t i = 0; i < net_outs_.size(); ++i)
    {
        // Network produces output blob with a shape NxC where N is a number of
        // detected objects and C is a number of classes + 4 where the first 4
        // numbers are [center_x, center_y, width, height]
        float* data = (float*)net_outs_[i].data;
        for (int j = 0; j < net_outs_[i].rows; ++j, data += net_outs_[i].cols)
        {
            scores = net_outs_[i].row(j).colRange(5, net_outs_[i].cols);
            minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);

            /* type : classIdPoint.x
                bicycle : 1
                car : 2
                motorcycle : 3
                bus : 5
                train : 6
                truck : 7
            */
            if ((classIdPoint.x == 1 || classIdPoint.x == 2 || classIdPoint.x == 3 || classIdPoint.x == 5 || classIdPoint.x == 6 || classIdPoint.x == 7) && confidence > config_.confidence_threshold)
            {
                width = (int)(data[2] * image_.cols);
                height = (int)(data[3] * image_.rows);
                left = (int)(data[0] * image_.cols) - width / 2;
                top = (int)(data[1] * image_.rows) - height / 2;

                out_confidences_.push_back((float)confidence);
                out_boxes_.push_back(Rect(left, top, width, height));
            }
        }
    }

    NMSBoxes(out_boxes_, out_confidences_, config_.confidence_threshold, config_.nms_threshold, out_nms_indices_);
    for (size_t i = 0; i < out_nms_indices_.size(); ++i)
    {
        Rect bbox = out_boxes_[out_nms_indices_[i]];

        if ((bbox.width < config_.min_car_w) || (config_.max_car_w < bbox.width))
            continue;

        if ((bbox.height < config_.min_car_h) || (config_.max_car_h < bbox.height))
            continue;

        VehicleBlob blob;
        blob.SetScope(bbox);
        blob.SetCentroidImage2D(Point(bbox.x+bbox.width/2,bbox.y+bbox.height/2));
        blobs_.push_back(blob);
    }

    return true;
}

bool Detection::DetectViolaJones(){

    vector<Rect> cars;

    car_cascade_.detectMultiScale( image_, cars, config_.scale_factor, config_.min_neighbors, 0|CV_HAAR_SCALE_IMAGE, Size(config_.min_car_w, config_.min_car_h),Size(config_.max_car_w, config_.max_car_h) );

    for (int i = 0; i < cars.size(); i++) {
        VehicleBlob blob;
        blob.SetScope(cars[i]);
        blob.SetCentroidImage2D(Point(cars[i].x+cars[i].width/2,cars[i].y+cars[i].height/2));
        blobs_.push_back(blob);
    }

    return true;
}

bool Detection::DetectBG()
{
    Mat img_mask;
    Mat img_bkgmodel;
    vector< vector< Point> > contours;
    vector<Vec4i> hierarchy;

    bgs_->process(image_, img_mask, img_bkgmodel); // by default, it shows automatically the foreground mask image

    imshow("img_mask",img_mask);
    waitKey(1);

    // Morphological operations
    cv::Mat element_dilate = getStructuringElement( MORPH_RECT,
                                                    Size( 2*config_.dilate_size + 1, 2*config_.dilate_size+1 ),
                                                    Point( config_.dilate_size, config_.dilate_size ) );

    cv::Mat element_erode = getStructuringElement( MORPH_ELLIPSE,
                                                   Size( 2*config_.erode_size + 1, 2*config_.erode_size+1 ),
                                                   Point( config_.erode_size, config_.erode_size ) );

    cv::erode(img_mask,img_mask,element_erode);
    cv::dilate(img_mask,img_mask,element_dilate);
    imshow("img_mask-1",img_mask);
    waitKey(1);

    findContours(img_mask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    for(int i=0; i<contours.size(); i++){
        Rect bbox = boundingRect(Mat(contours[i]));

        if ((bbox.width < config_.min_car_w) || (config_.max_car_w < bbox.width))
            continue;

        if ((bbox.height < config_.min_car_h) || (config_.max_car_h < bbox.height))
            continue;

        VehicleBlob blob;
        blob.SetScope(bbox);
        blob.SetCentroidImage2D(Point(bbox.x+bbox.width/2,bbox.y+bbox.height/2));
        blobs_.push_back(blob);
    }

    return true;
}

bool Detection::LoadModelYolo()
{
    net_ = readNet(config_.model_path, config_.config_path);

    vector<int> outLayers = net_.getUnconnectedOutLayers();
    if (outLayers.empty())
        return false;

    vector<String> layersNames = net_.getLayerNames();
    if (layersNames.empty())
        return false;

    out_layers_names_.resize(outLayers.size());
    for (size_t i = 0; i < outLayers.size(); ++i)
        out_layers_names_[i] = layersNames[outLayers[i] - 1];

    return true;
}

bool Detection::LoadModelViolasJones()
{
    if (!car_cascade_.load( config_.cascade_path ))
    {
        printf("Detection:: Error loading cascade \n");
        return false;
    }
    else
        return true;
}

bool Detection::LoadBGS(){
    /* Background Subtraction Methods */

    switch (config_.algo_bgs){
    case BGS_AdaptiveBackgroundLearning:
        bgs_ = new AdaptiveBackgroundLearning;
        break;

    case BGS_AdaptiveSelectiveBackgroundLearning:
        bgs_ = new AdaptiveSelectiveBackgroundLearning;
        break;

    case BGS_CodeBook:
        bgs_ = new CodeBook;
        break;

    case BGS_DPAdaptiveMedian:
        bgs_ = new DPAdaptiveMedian;
        break;

    case BGS_DPEigenbackground:
        bgs_ = new DPEigenbackground;
        break;

    case BGS_DPGrimsonGMM:
        bgs_ = new DPGrimsonGMM;
        break;

    case BGS_DPMean:
        bgs_ = new DPMean;
        break;

    case BGS_DPPratiMediod:
        bgs_ = new DPPratiMediod;
        break;

    case BGS_DPTexture:
        bgs_ = new DPTexture;
        break;

    case BGS_DPWrenGA:
        bgs_ = new DPWrenGA;
        break;

    case BGS_DPZivkovicAGMM:
        bgs_ = new DPZivkovicAGMM;
        break;

    case BGS_FrameDifference:
        bgs_ = new FrameDifference;
        break;

    case BGS_FuzzyChoquetIntegral:
        bgs_ = new FuzzyChoquetIntegral;
        break;

    case BGS_FuzzySugenoIntegral:
        bgs_ = new FuzzySugenoIntegral;
        break;

#if CV_MAJOR_VERSION == 2 && CV_MINOR_VERSION >= 4 && CV_SUBMINOR_VERSION >= 3
    case BGS_GMG:
        bgs_ = new GMG;
        break;
#endif

    case BGS_IndependentMultimodal:
        bgs_ = new IndependentMultimodal;
        break;

    case BGS_KDE:
        bgs_ = new KDE;
        break;

    case BGS_KNN:
        bgs_ = new KNN;
        break;

    case BGS_LBAdaptiveSOM:
        bgs_ = new LBAdaptiveSOM;
        break;

    case BGS_LBFuzzyAdaptiveSOM:
        bgs_ = new LBFuzzyAdaptiveSOM;
        break;

    case BGS_LBFuzzyGaussian:
        bgs_ = new LBFuzzyGaussian;
        break;

    case BGS_LBMixtureOfGaussians:
        bgs_ = new LBMixtureOfGaussians;
        break;

    case BGS_LBP_MRF:
        bgs_ = new LBP_MRF;
        break;

    case BGS_LBSimpleGaussian:
        bgs_ = new LBSimpleGaussian;
        break;

    case BGS_LOBSTER:
        bgs_ = new LOBSTER;
        break;

#if CV_MAJOR_VERSION == 2
    case BGS_MixtureOfGaussianV1:
        bgs_ = new MixtureOfGaussianV1;
        break;
#endif

    case BGS_MixtureOfGaussianV2:
        bgs_ = new MixtureOfGaussianV2;
        break;

    case BGS_MultiCue:
        bgs_ = new MultiCue;
        break;

    case BGS_MultiLayer:
        bgs_ = new MultiLayer;
        break;

    case BGS_PAWCS:
        bgs_ = new PAWCS;
        break;

    case BGS_PixelBasedAdaptiveSegmenter:
        bgs_ = new PixelBasedAdaptiveSegmenter;
        break;

    case BGS_SigmaDelta:
        bgs_ = new SigmaDelta;
        break;

    case BGS_StaticFrameDifference:
        bgs_ = new StaticFrameDifference;
        break;

    case BGS_SuBSENSE:
        bgs_ = new SuBSENSE;
        break;

    case BGS_T2FGMM_UM:
        bgs_ = new T2FGMM_UM;
        break;

    case BGS_T2FGMM_UV:
        bgs_ = new T2FGMM_UV;
        break;

    case BGS_T2FMRF_UM:
        bgs_ = new T2FMRF_UM;
        break;

    case BGS_T2FMRF_UV:
        bgs_ = new T2FMRF_UV;
        break;

    case BGS_TwoPoints:
        bgs_ = new TwoPoints;
        break;

    case BGS_ViBe:
        bgs_ = new ViBe;
        break;

    case BGS_VuMeter:
        bgs_ = new VuMeter;
        break;

    case BGS_WeightedMovingMean:
        bgs_ = new WeightedMovingMean;
        break;

    case BGS_WeightedMovingVariance:
        bgs_ = new WeightedMovingVariance;
        break;
    }
    return true;
}

void Detection::run()
{
    if (!Init())
        return;
    double timer;
    while(is_running_){
        timer = (double)getTickCount();

        MainFunction();

        fps_ = getTickFrequency() / ((double)getTickCount() - timer);
    }
}


//init restart, yolo swaprb, yolo scalefactor
