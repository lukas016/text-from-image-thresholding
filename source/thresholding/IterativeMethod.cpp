/**
 * @file:   IterativeMethod.cpp
 * @author: Tom Svoboda <xsvobo0l@stud.fit.vutbr.cz>
 * @date:   12. 04. 2017
 */

#include "IterativeMethod.h"

namespace thresholding {

    IterativeMethod::IterativeMethod(const cv::Mat& _image, const Histogram& _histogram) :
        Algorithm(_image, _histogram) {
        name = "IterativeMethod";
    }

    void IterativeMethod::run(cv::Mat& result) {
        result = cv::Mat( image.size(), image.type() );

        // @TODO
    }

}