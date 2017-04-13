/**
 * @file:   BalancedHistogramMethod.cpp
 * @author: Tom Svoboda <xsvobo0l@stud.fit.vutbr.cz>
 * @date:   12. 04. 2017
 */

#include "BalancedHistogramMethod.h"

namespace thresholding {

    BalancedHistogramMethod::BalancedHistogramMethod(const cv::Mat& _image, const Histogram& _histogram) :
        Algorithm(_image, _histogram) {
        name = "Balanced Histogram Thresholding Method";
    }

    int BalancedHistogramMethod::getBHThreshold() {
        int lIndex = 0;   // min index
        int rIndex = 255; // max index

        int lWeight = histogram.at(lIndex);
        int rWeight = histogram.at(rIndex);

        while(lIndex < rIndex) {
            if(rWeight > lIndex) {
                // Right side is heavier -> push right index to left
                rIndex--;
                rWeight += histogram.at(rIndex);
            }
            else {
                // Left side is heavier -> push left index into right
                lIndex++;
                lWeight += histogram.at(lIndex);
            }
        }

        return lIndex;
    }

    void BalancedHistogramMethod::run(cv::Mat& result) {
        result = cv::Mat( image.size(), image.type() );

        // Get threshold
        unsigned char threshold = getBHThreshold();

        // Thresholding
        performThresholding(threshold, result);
    }

}