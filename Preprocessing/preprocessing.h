#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <QThread>

#include "opencv2/opencv.hpp"
#include <iostream>

#include <Buffer/buffer.h>

enum InputColorSpace
{
    CS_BAYER,
    CS_RGB,
    CS_GRAY
};

struct ConfigPreprocessing{
    InputColorSpace input_color_space;
};

class Preprocessing : public QThread
{
    Q_OBJECT
public:

    Preprocessing(Buffer* buffer);

    void SetConfig(ConfigPreprocessing config);

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

    ConfigPreprocessing config_;

    bool is_running_;

    float fps_;
};

#endif // PREPROCESSING_H
