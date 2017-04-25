/**
 * @file:   IterativeMethod.h
 * @author: Tom Svoboda <xsvobo0l@stud.fit.vutbr.cz>
 * @date:   12. 04. 2017
 */

#ifndef ITERATIVEMETHOD_H
#define ITERATIVEMETHOD_H

#include "Algorithm.h"

namespace thresholding {

    /**
     * Simple iterative algorithm for thresholding image
     */
    class IterativeMethod : public Algorithm {
    public:
        /**
         * Construct IterativeMethod object
         * @param _image Reference to source image
         * @param _histogram Reference to histogram of source image
         */
        IterativeMethod(const cv::Mat& _image, const Histogram& _histogram);

        void run(cv::Mat& result) override;

    protected:
        /**
         * Compute threshold with iterative method
         * @return Value of threshold
         */
        int getIterativeThreshold();
    };

}

#endif /* ITERATIVEMETHOD_H */