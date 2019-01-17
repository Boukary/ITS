#ifndef INFRACTIONPROOFMAKER_H
#define INFRACTIONPROOFMAKER_H

#include "opencv2/opencv.hpp"
#include <iostream>

#include <Buffer/infraction.h>
#include <Buffer/imageindexed.h>

typedef enum{
    EXTI_JPG,
    EXTI_PNG,
    EXTI_PGM,
    EXTI_PPM,
    EXTI_TIF
} ExtensionImage;

typedef enum{
    EXTV_MP4,
    EXTV_AVI,
    EXTV_MPG
} ExtensionVideo;

struct ConfigInfractionProofMaker{
    int size_imageindexed_list_max;
    std::string dir_path_proof;
    cv::Size size_image_proof;
    int fps_video_proof;
    ExtensionImage extension_image_proof;
    ExtensionVideo extension_video_proof;
    int codec_video_proof;
    int proof_redlight_violation_duration;
    int proof_stopsign_violation_duration;
    int proof_speed_violation_duration;
    int proof_direction_violation_duration;
};

class InfractionProofMaker
{
public:

    InfractionProofMaker();

    void SetConfig(ConfigInfractionProofMaker config);

    void AddImageIndexed(cv::Mat* image, unsigned long long index_absolu);

    bool MakeInfractionProof(Infraction inf);


private :

    std::vector<ImageIndexed> list_imageindexed_ ;

    ConfigInfractionProofMaker config_;

};

#endif // INFRACTIONPROOFMAKER_H
