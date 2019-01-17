#ifndef ACQUISITION_H
#define ACQUISITION_H

#include <QThread>

#include "opencv2/opencv.hpp"
#include <iostream>

#include <Buffer/buffer.h>

struct ConfigAcquisition{
    std::string cap_path_mono;
    std::string cap_path_stereo;
    bool is_stereo;
};

class Acquisition : public QThread
{
    Q_OBJECT
public:

    Acquisition(Buffer* buffer);

    void SetConfig(ConfigAcquisition config);

    void Start();

    void Stop();

signals:

public slots:

private:

    void run();

    bool Init();

    bool MainFunction();

    Buffer* buffer_;

    cv::VideoCapture cap_mono_;

    cv::VideoCapture cap_stereo_;

    cv::Mat image_raw_mono_;

    cv::Mat image_raw_stereo_;

    ConfigAcquisition config_;

    bool is_running_;

    float fps_;
};

#endif // ACQUISITION_H
