/**
 * @file:   AdaptiveGaussMethod.cpp
 * @author: Olga Gavryliuk <xgavry00@stud.fit.vutbr.cz>
 * @date:   25. 04. 2017
 */

#include "AdaptiveGaussMethod.h"

namespace thresholding {

    AdaptiveGaussMethod::AdaptiveGaussMethod(const cv::Mat& _image, const Histogram& _histogram) :
            Algorithm(_image, _histogram) {
        name = "Adaptive Gauss Method";
    }

    void AdaptiveGaussMethod::run(cv::Mat& result) {
        cv::adaptiveThreshold(image, result, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 7, 5);

        // @TODO
    }

}