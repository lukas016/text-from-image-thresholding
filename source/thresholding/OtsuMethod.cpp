/**
 * @file:   OtsuMethod.cpp
 * @author: Tom Svoboda <xsvobo0l@stud.fit.vutbr.cz>
 * @date:   12. 04. 2017
 */

#include "OtsuMethod.h"

namespace thresholding {

    OtsuMethod::OtsuMethod(const cv::Mat& _image, const Histogram& _histogram) :
        Algorithm(_image, _histogram) {
        name = "Otsu's Method";
    }

    void OtsuMethod::run(cv::Mat& result) {
        result = cv::Mat( image.size(), image.type() );

        // @TODO
    }

}