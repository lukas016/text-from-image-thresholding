/**
 * @TODO
 */
#include <limits>

#include "Histogram.h"

using namespace std;

static uint16_t colorRange = 256;

Histogram::Histogram(cv::Mat& image) : histogram(vector<uint32_t>(colorRange, 0))
{
    // Initialize vector
    for (int64_t row = 0; row < image.rows; ++row)
        for (int64_t col = 0; col < image.cols; ++col)
            histogram[image.at<color>(row, col)]++;
}

color Histogram::getHighest()
{
    color result = 0;
    uint32_t counter = 0;
    for (uint32_t i = 0; i < histogram.size(); ++i) {
        if (histogram[i] > counter) {
            result = (color) i;
            counter = histogram[i];
        }
    }

    return result;
}

color Histogram::getLowest()
{
    color result = 0;
    uint32_t counter = numeric_limits<uint32_t>::max();
    for (color i = 0; i < histogram.size(); ++i) {
        if (histogram[i] < counter) {
            result = i;
            counter = histogram[i];
        }
    }

    return result;
}

uint32_t Histogram::at(color index) const
{
    return histogram[index];
}

ostream& operator<<(std::ostream& os, const Histogram& obj)
{
    os << "HISTOGRAM:" << endl;

    for (uint16_t i = 0; i < colorRange; ++i)
        os << i << ": " << obj.at(i) << endl;

    return os;
}
