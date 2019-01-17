#ifndef INFRACTIONDETECTION_H
#define INFRACTIONDETECTION_H

#include <QThread>

#include "opencv2/opencv.hpp"
#include <iostream>

#include <Buffer/buffer.h>

struct ConfigInfractionDetection{
    int color_threshold;
};

class InfractionDetection : public QThread
{
    Q_OBJECT
public:

    InfractionDetection(Buffer* buffer);

    void SetConfig(ConfigInfractionDetection config);

    void Start();

    void Stop();

signals:

public slots:

private:

    void run();

    bool MainFunction();

    bool UpdateTrafficSignalsColor();

    bool IsLightOn(cv::Mat& area);

    bool DetectRedLightInfraction(Vehicle* v, unsigned long long index_absolu);

    bool DetectStopSignInfraction(Vehicle* v, unsigned long long index_absolu);

    bool DetectDirectionInfraction(Vehicle* v, unsigned long long index_absolu);

    Buffer* buffer_;

    cv::Mat image_;

    std::vector<Vehicle> vehicles_;

    ConfigInfractionDetection config_;

    bool is_running_;

    float fps_;
};


#endif // INFRACTIONDETECTION_H
