/**
 * @file:   OtsuMethod.h
 * @author: Tom Svoboda <xsvobo0l@stud.fit.vutbr.cz>
 * @date:   12. 04. 2017
 */

#ifndef OTSUMETHOD_H
#define OTSUMETHOD_H

#include "Algorithm.h"

namespace thresholding {

    class OtsuMethod : public Algorithm {
    public:
        /**
         * Construct Otsu's Method object
         * @param _image Reference to source image
         * @param _histogram Reference to histogram of source image
         */
        OtsuMethod(const cv::Mat& _image, const Histogram& _histogram);

        void run(cv::Mat& result) override;
    };

}

#endif /* OTSUMETHOD_H */