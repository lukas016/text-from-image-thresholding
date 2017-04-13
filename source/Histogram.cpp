/**
 * @TODO
 */

#include "Histogram.h"

Histogram::Histogram(cv::Mat& image) {
    // Initialize vector
    for(int i=0; i<256; i++) {
        histogram[i] = 0;
    }

    // @TODO
}

unsigned char Histogram::at(int index) const {
    return histogram.at(index);
}
