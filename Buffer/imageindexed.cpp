#include "imageindexed.h"

using namespace std;
using namespace cv;

ImageIndexed::ImageIndexed()
{

}

unsigned long long ImageIndexed::GetIndexAbsolu()
{
    return index_absolu_;
}

vector<uchar>& ImageIndexed::GetImage()
{
    return image_;
}

void ImageIndexed::SetIndexAbsolu(unsigned long long index_absolu)
{
    index_absolu_ = index_absolu;
}

void ImageIndexed::SetImage(vector<uchar>& image)
{
    image_ = image;
}
