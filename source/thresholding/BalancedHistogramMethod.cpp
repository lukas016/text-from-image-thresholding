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

    void BalancedHistogramMethod::run(cv::Mat& result) {
        result = cv::Mat( image.size(), image.type() );

        // @TODO
    }

}