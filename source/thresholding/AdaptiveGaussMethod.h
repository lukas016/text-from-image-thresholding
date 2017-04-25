/**
 * @file:   AdaptiveGaussMethod.cpp
 * @author: Olga Gavryliuk <xgavry00@stud.fit.vutbr.cz>
 * @date:   25. 04. 2017
 */

#ifndef ADAPTIVEMETHOD_Gauss_H
#define ADAPTIVEMETHOD_Gauss_H

#include "Algorithm.h"

namespace thresholding {

    class AdaptiveGaussMethod : public Algorithm {
    public:
        AdaptiveGaussMethod(const cv::Mat& _image, const Histogram& _histogram);

        void run(cv::Mat& result) override;
    };

}

#endif /* ADAPTIVEMETHOD_Gauss_H */

