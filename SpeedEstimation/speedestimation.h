#ifndef SPEEDESTIMATION_H
#define SPEEDESTIMATION_H

#include <QThread>

#include "opencv2/opencv.hpp"
#include <iostream>

#include <Buffer/buffer.h>

struct ConfigSpeedEstimation{
};

class SpeedEstimation : public QThread
{
    Q_OBJECT
public:

    SpeedEstimation(Buffer* buffer);

    void SetConfig(ConfigSpeedEstimation config);

    void Start();

    void Stop();

signals:

public slots:

private:

    void run();

    bool MainFunction();

    Buffer* buffer_;

    cv::Mat image_mono_;

    cv::Mat image_stereo_;

    std::vector<Vehicle> vehicles_;

    ConfigSpeedEstimation config_;

    bool is_running_;

    float fps_;
};

#endif // SPEEDESTIMATION_H
