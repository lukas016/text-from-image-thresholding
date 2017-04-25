/**
 * @file:   AdaptiveMeanCMethod.cpp
 * @author: Olga Gavryliuk <xgavry00@stud.fit.vutbr.cz>
 * @date:   25. 04. 2017
 */

#include "AdaptiveMeanCMethod.h"

namespace thresholding {

    AdaptiveMeanCMethod::AdaptiveMeanCMethod(const cv::Mat& _image, const Histogram& _histogram) :
            Algorithm(_image, _histogram) {
        name = "Adaptive Mean C Method";
    }

    void AdaptiveMeanCMethod::run(cv::Mat& result) {
        cv::adaptiveThreshold(image, result, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 7, 5);

        // @TODO
    }

}