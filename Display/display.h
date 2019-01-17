#ifndef DISPLAY_H
#define DISPLAY_H

#include <QThread>

#include "opencv2/opencv.hpp"
#include <iostream>

#include <Buffer/buffer.h>

struct ConfigDisplay{
    int trajectory_history_display;
};

class Display : public QThread
{
    Q_OBJECT
public:

    Display(Buffer* buffer);

    void SetConfig(ConfigDisplay config);

    void Start();

    void Stop();

signals:

public slots:

private:

    void run();

    bool MainFunction();

    Buffer* buffer_;

    std::vector<cv::Scalar> predefined_colors_;

    cv::Mat image_;

    std::vector<Vehicle> vehicles_;

    ConfigDisplay config_;

    bool is_running_;

    float fps_;
};

#endif // DISPLAY_H
