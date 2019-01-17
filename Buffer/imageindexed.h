#ifndef IMAGEINDEXED_H
#define IMAGEINDEXED_H

#include "opencv2/opencv.hpp"
#include <iostream>

class ImageIndexed
{
public:

    ImageIndexed();

    unsigned long long int GetIndexAbsolu();

    std::vector<uchar>& GetImage();

    void SetIndexAbsolu(unsigned long long int index_absolu);

    void SetImage(std::vector<uchar>& image);


private :

    unsigned long long int index_absolu_ ;

    std::vector<uchar> image_ ;

};

#endif // IMAGEINDEXED_H
