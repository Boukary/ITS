#include "infractionproofmaker.h"

using namespace std;
using namespace cv;

InfractionProofMaker::InfractionProofMaker()
{

}

void InfractionProofMaker::SetConfig(ConfigInfractionProofMaker config)
{
    config_ = config;
}

void InfractionProofMaker::AddImageIndexed(Mat *image, unsigned long long index_absolu)
{
    vector<uchar> image_encoded;

    switch (config_.extension_image_proof) {
    case EXTI_JPG:
        imencode(".jpg",*image,image_encoded);
        break;
    case EXTI_PNG:
        imencode(".png",*image,image_encoded);
        break;
    case EXTI_PGM:
        imencode(".pgm",*image,image_encoded);
        break;
    case EXTI_PPM:
        imencode(".ppm",*image,image_encoded);
        break;
    case EXTI_TIF:
        imencode(".tif",*image,image_encoded);
        break;
    }

    ImageIndexed image_indexed;
    image_indexed.SetIndexAbsolu(index_absolu);
    image_indexed.SetImage(image_encoded);

    while (list_imageindexed_.size()>=config_.size_imageindexed_list_max)
        list_imageindexed_.erase(list_imageindexed_.begin());

    list_imageindexed_.push_back(image_indexed);
}

bool InfractionProofMaker::MakeInfractionProof(Infraction inf)
{
    unsigned long long index_absolu_start = 0;
    unsigned long long index_absolu_end = inf.GetIndexAbsolu();
    string video_path = config_.dir_path_proof+"/";
    switch (inf.GetInfractionType()) {
    case INFRACTION_REDLIGHT:
        video_path+="redlight";
        if (index_absolu_end > config_.proof_redlight_violation_duration)
            index_absolu_start = index_absolu_end - config_.proof_redlight_violation_duration;
        break;

    case INFRACTION_STOPSIGN:
        video_path+="stopsign";
        if (index_absolu_end > config_.proof_stopsign_violation_duration)
            index_absolu_start = index_absolu_end - config_.proof_stopsign_violation_duration;
        break;

    case INFRACTION_SPEED:
        video_path+="speed";
        if (index_absolu_end > config_.proof_speed_violation_duration)
            index_absolu_start = index_absolu_end - config_.proof_speed_violation_duration;
        break;

    case INFRACTION_DIRECTION:
        video_path+="direction";
        if (index_absolu_end > config_.proof_direction_violation_duration)
            index_absolu_start = index_absolu_end - config_.proof_direction_violation_duration;
        break;
    }
    video_path+="_"+inf.GetIdInfraction();
    switch (config_.extension_video_proof) {
    case EXTV_MP4:
        video_path+=".mp4";
        break;

    case EXTV_AVI:
        video_path+=".avi";
        break;

    case EXTV_MPG:
        video_path+=".mpg";
        break;
    }

    VideoWriter video_writer(video_path,config_.codec_video_proof,config_.fps_video_proof,config_.size_image_proof,true);
    if (!video_writer.isOpened())
    {
        cout  << "InfractionProofMaker:: Error open video writer"  << endl;
        return false;
    }

    Mat image_decoded(config_.size_image_proof,CV_8UC3);
    for (unsigned long long i=index_absolu_start; i<=index_absolu_end; i++) {
        for (int j=list_imageindexed_.size() - 1; j>=0; j--) {
            if (list_imageindexed_[j].GetIndexAbsolu() == i){
                imdecode(list_imageindexed_[j].GetImage(),IMREAD_COLOR,&image_decoded);
                video_writer << image_decoded;
                break;
            }
        }
    }
    video_writer.release();

    return true;
}
