/**
 * @TODO
 */

#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <opencv2/opencv.hpp>
#include <vector>

using color = uint8_t;

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

    color getHighest();
    color getLowest();
    uint64_t at(color index) const;

    /**
     * Return number of intensity levels
     * @return
     */
    int levels() const;

    friend std::ostream& operator<<(std::ostream& os, const Histogram& obj);

protected:
    std::vector<uint64_t> histogram;
};

#endif /* HISTOGRAM_H */
