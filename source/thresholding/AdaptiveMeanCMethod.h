/**
 * @file:   AdaptiveMeanCMethod.cpp
 * @author: Olga Gavryliuk <xgavry00@stud.fit.vutbr.cz>
 * @date:   25. 04. 2017
 */

#ifndef ADAPTIVEMETHOD_MeanC_H
#define ADAPTIVEMETHOD_MeanC_H

#include "Algorithm.h"

namespace thresholding {

    class AdaptiveMeanCMethod : public Algorithm {
    public:
        AdaptiveMeanCMethod(const cv::Mat& _image, const Histogram& _histogram);

        void run(cv::Mat& result) override;
    };

}

#endif /* ADAPTIVEMETHOD_MeanC_H */

