#include "mainwindow.h"
#include <QApplication>

#include "Buffer/buffer.h"
#include "Acquisition/acquisition.h"
#include "Preprocessing/preprocessing.h"
#include "Detection/detection.h"
#include "Tracking/tracking.h"
#include "Classification/classification.h"
#include "Recognition/recognition.h"
#include "SpeedEstimation/speedestimation.h"
#include "InfractionDetection/infractiondetection.h"
#include "Display/display.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Buffer buffer;
    Acquisition acquisition(&buffer);
    Preprocessing preprocessing(&buffer);
    Detection detection(&buffer);
    Tracking tracking(&buffer);
    Classification classification(&buffer);
    Recognition recognition(&buffer);
    SpeedEstimation speed_estimation(&buffer);
    InfractionDetection infraction_detection(&buffer);
    Display display(&buffer);

    // /media/boukary/BOOTCAMP/mascir-waycount/64/EMI-Bayer.avi
    // /media/boukary/BOOTCAMP/mascir-waycount/64/MAScIR-EGE-Bayer/image%05d.bmp
    // /media/boukary/BOOTCAMP/mascir-waycount/64/UM5-Bayer/img%05d.bmp
    // /media/boukary/BOOTCAMP/mascir-waycount/64/CNRST-Bayer/img%05d.bmp
    // /media/boukary/BOOTCAMP/mascir-waycount/64/CNRST-RGB1.mp4
    // /media/boukary/BOOTCAMP/mascir-waycount/64/CNRST-RGB2.mp4

    ConfigBuffer config_buffer;
    config_buffer.size_frame_list_max = 100;
    config_buffer.config_infraction_proof_maker.size_imageindexed_list_max = 1800;
    config_buffer.config_infraction_proof_maker.dir_path_proof = "/home/boukary/Qt-Projects/ITS/InfractionProofVideos";
    config_buffer.config_infraction_proof_maker.size_image_proof = Size(800,600);
    config_buffer.config_infraction_proof_maker.fps_video_proof = 10;
    config_buffer.config_infraction_proof_maker.extension_image_proof = EXTI_JPG;
    config_buffer.config_infraction_proof_maker.extension_video_proof = EXTV_MP4;
    config_buffer.config_infraction_proof_maker.codec_video_proof = 0x00000021; //VideoWriter::fourcc('M','J','P','G');
    config_buffer.config_infraction_proof_maker.proof_redlight_violation_duration = 20;
    config_buffer.config_infraction_proof_maker.proof_stopsign_violation_duration = 20;
    config_buffer.config_infraction_proof_maker.proof_speed_violation_duration = 20;
    config_buffer.config_infraction_proof_maker.proof_direction_violation_duration = 20;


    ConfigAcquisition config_acquisition;
    config_acquisition.cap_path_mono = "/media/boukary/BOOTCAMP/mascir-waycount/64/CNRST-Bayer/img%05d.bmp";
    config_acquisition.cap_path_stereo = "/media/boukary/BOOTCAMP/mascir-waycount/64/CNRST-Bayer/img%05d.bmp";
    config_acquisition.is_stereo = true;

    ConfigPreprocessing config_preprocessing;
    config_preprocessing.input_color_space = CS_BAYER;

    ConfigDetection config_detection;
    config_detection.detection_method = DM_YOLO;
    config_detection.nbr_skip_detection = 0;
    config_detection.min_car_w = 50;
    config_detection.min_car_h = 50;
    config_detection.max_car_w = 1200;
    config_detection.max_car_h = 1200;
    // Yolo
    config_detection.model_path = "/home/boukary/Qt-Projects/ITS/Detection/yolo/yolov3.weights";
    config_detection.config_path = "/home/boukary/Qt-Projects/ITS/Detection/yolo/yolov3.cfg";
    config_detection.model_input_size = Size(416,416);
    config_detection.model_input_scale = 0.00392;
    config_detection.confidence_threshold = 0.5;
    config_detection.nms_threshold = 0.4;
    // Viola and Jones
    config_detection.cascade_path = "/home/boukary/Qt-Projects/ITS/Detection/viola_jones/cascade_bouknadel.xml";
    config_detection.scale_factor = 1.04;
    config_detection.min_neighbors = 3;
    // Background Subtraction
    config_detection.algo_bgs = BGS_FrameDifference;
    config_detection.threshold = 5;
    config_detection.erode_size = 1;
    config_detection.dilate_size = 10;

    ConfigTracking config_tracking;
    config_tracking.m_useLocalTracking = true;
    config_tracking.m_distType = CentersDist;
    config_tracking.m_kalmanType = FilterCenter;
    config_tracking.dt = 1.0f;
    config_tracking.accelNoiseMag = 0.1f;
    config_tracking.dist_thres = 2456 /*1920*/ / 10.0f;
    config_tracking.maximum_allowed_skipped_frames = 10;
    config_tracking.max_trace_length = 50;
    config_tracking.NextTrackID = 0;

    ConfigClassification config_classification;

    ConfigRecognition config_recognition;

    ConfigSpeedEstimation config_speed_estimation;

    ConfigInfractionDetection config_infraction_detection;
    config_infraction_detection.color_threshold = 20;

    ConfigDisplay config_display;
    config_display.trajectory_history_display = 10;

    buffer.SetConfig(config_buffer);
    acquisition.SetConfig(config_acquisition);
    preprocessing.SetConfig(config_preprocessing);
    detection.SetConfig(config_detection);
    tracking.SetConfig(config_tracking);
    classification.SetConfig(config_classification);
    recognition.SetConfig(config_recognition);
    speed_estimation.SetConfig(config_speed_estimation);
    infraction_detection.SetConfig(config_infraction_detection);
    display.SetConfig(config_display);

    acquisition.Start();
    preprocessing.Start();
    detection.Start();
    tracking.Start();
    classification.Start();
    recognition.Start();
    speed_estimation.Start();
    infraction_detection.Start();
    display.Start();

    return a.exec();
}

// config params optimal
// , all blocs return false avec error message
// problem boucle infini pour les bloc parallele CNRST
