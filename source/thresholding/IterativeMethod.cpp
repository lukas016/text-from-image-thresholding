/**
 * @file:   IterativeMethod.cpp
 * @author: Tom Svoboda <xsvobo0l@stud.fit.vutbr.cz>
 * @date:   12. 04. 2017
 */

#include "IterativeMethod.h"

namespace thresholding {

    IterativeMethod::IterativeMethod(const cv::Mat& _image, const Histogram& _histogram, bool _halfThresholding) :
        Algorithm(_image, _histogram, _halfThresholding) {
        name = "Iterative Method";
    }

    int IterativeMethod::getIterativeThreshold() {
        int threshold = 255/2; // initial threshold
        int newThreshold=0;

        while(true) {
            float uF = 0, uB = 0;
            int countF = 0, countB = 0;

            // Compute mean foreground and mean background
            for(int row=0; row<image.rows; row++) {
                for(int col=0; col<image.cols; col++) {
                    unsigned char pixel = image.at<unsigned char>(row, col);

                    if(pixel > threshold) {
                        uF += pixel;
                        countF++;
                    }
                    else {
                        uB += pixel;
                        countB++;
                    }
                }
            }

            uF /= countF;
            uB /= countB;

            // Compute new threshold
            newThreshold = 0.5*(uF+uB);

            if(threshold == newThreshold) {
                break; // End algorithm
            }
            else {
                threshold = newThreshold;
            }
        }

        return threshold;
    }

    void IterativeMethod::run(cv::Mat& result) {
        result = cv::Mat( image.size(), image.type() );

        // Get threshold
        unsigned char threshold = getIterativeThreshold();

        // Thresholding
        performThresholding(threshold, result);
    }

}