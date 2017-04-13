/**
 * @file:   Base.h
 * @author: Tom Svoboda <xsvobo0l@stud.fit.vutbr.cz>
 * @date:   13. 04. 2017
 */

#include "Algorithm.h"

namespace thresholding {

    void Algorithm::performThresholding(unsigned char threshold, cv::Mat& result) {
        for(int row=0; row<image.rows; row++) {
            for(int col=0; col<image.cols; col++) {
                if(image.at<unsigned char>(row, col) > threshold) {
                    result.at<unsigned char>(row, col) = 255;
                }
                else {
                    result.at<unsigned char>(row, col) = 0;
                }
            }
        }
    }

}