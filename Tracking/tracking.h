#ifndef TRACKING_H
#define TRACKING_H

#include <QThread>

#include "opencv2/opencv.hpp"
#include <iostream>

#include <Buffer/buffer.h>
#include <Tracking/defines.h>
#include <Tracking/track.h>
#include <Tracking/HungarianAlg.h>
#include <Tracking/LocalTracker.h>

enum DistType
{
    CentersDist,
    RectsDist
};
enum KalmanType
{
    FilterCenter,
    FilterRect
};

struct ConfigTracking{
    bool m_useLocalTracking;
    DistType m_distType;
    KalmanType m_kalmanType;
    track_t dt;
    track_t accelNoiseMag;
    track_t dist_thres;
    size_t maximum_allowed_skipped_frames;
    size_t max_trace_length;
    size_t NextTrackID;
};

class Tracking : public QThread
{
    Q_OBJECT
public:

    Tracking(Buffer* buffer);

    void SetConfig(ConfigTracking config);

    void Start();

    void Stop();

signals:

public slots:

private:

    void run();

    bool MainFunction();

    bool TrackVehicles(unsigned long long index_absolu);

    Buffer* buffer_;

    LocalTracker local_tracker_;

    tracks_t tracks_;

    cv::Mat image_;

    std::vector<VehicleBlob> blobs_;

    std::vector<Vehicle> vehicles_;

    ConfigTracking config_;

    bool is_running_;

    float fps_;
};

#endif // TRACKING_H
