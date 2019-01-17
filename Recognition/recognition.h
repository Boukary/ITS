#ifndef RECOGNITION_H
#define RECOGNITION_H

#include <QThread>

#include "opencv2/opencv.hpp"
#include <iostream>

#include <Buffer/buffer.h>

struct ConfigRecognition{
};

class Recognition : public QThread
{
    Q_OBJECT
public:

    Recognition(Buffer* buffer);

    void SetConfig(ConfigRecognition config);

    void Start();

    void Stop();

signals:

public slots:

private:

    void run();

    bool MainFunction();

    Buffer* buffer_;

    cv::Mat image_;

    std::vector<Vehicle> vehicles_;

    ConfigRecognition config_;

    bool is_running_;

    float fps_;
};

#endif // RECOGNITION_H
