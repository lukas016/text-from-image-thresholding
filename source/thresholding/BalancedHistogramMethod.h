/**
 * @file:   BalancedHistogramMethod.h
 * @author: Tom Svoboda <xsvobo0l@stud.fit.vutbr.cz>
 * @date:   12. 04. 2017
 */

#ifndef BALANCEDHISTOGRAMMETHOD_H
#define BALANCEDHISTOGRAMMETHOD_H

#include "Algorithm.h"

namespace thresholding {

    class BalancedHistogramMethod : public Algorithm {
    public:
        /**
         * Construct Balanced histogram method object
         * @param _image Reference to source image
         * @param _histogram Reference to histogram of source image
         */
        BalancedHistogramMethod(const cv::Mat& _image, const Histogram& _histogram);

        void run(cv::Mat& result) override;

    };

}

#endif /* BALANCEDHISTOGRAMMETHOD_H */