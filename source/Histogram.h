/**
 * @TODO
 */

#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <opencv2/opencv.hpp>
#include <vector>

/**
 * Histogram class
 */
class Histogram {
public:
    /**
     * Create histogram from grayscale image
     * @param image OpenCV matrix with image (item type: unsigned char)
     */
    Histogram(cv::Mat& image);

    unsigned char getHighest();
    unsigned char getLowest();
    unsigned char at(int index);

    friend std::ostream& operator<<(std::ostream& os, const Histogram& obj);

protected:
    std::vector<unsigned char> histogram;
};

#endif /* HISTOGRAM_H */