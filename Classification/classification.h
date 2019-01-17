#ifndef CLASSIFICATION_H
#define CLASSIFICATION_H

#include <QThread>

#include "opencv2/opencv.hpp"
#include <iostream>

#include <Buffer/buffer.h>

struct ConfigClassification{
};

class Classification : public QThread
{
    Q_OBJECT
public:

    Classification(Buffer* buffer);

    void SetConfig(ConfigClassification config);

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

    ConfigClassification config_;

    bool is_running_;

    float fps_;
};


#endif // CLASSIFICATION_H
