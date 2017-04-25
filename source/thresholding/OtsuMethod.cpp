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

    int OtsuMethod::getOtsuThreshold() {
        int pixelsCount = image.rows * image.cols;
        float uT = 0.0;
        float w0 = 0;   /** < Weight background */
        float w1;       /** < Weight foreground */
        float u0 = 0;   /** < Mean background */
        float u1 = 0;   /** < Mean foreground */
        float sum0 = 0; /** < Sum background */
        float sigma;
        float max = 0;
        int threshold = 0;

        for(int i=0; i < histogram.levels(); i++) {
            uT += i * histogram.at(i);
        }

        for(int i=0; i < histogram.levels(); i++) {

            w0 += histogram.at(i);
            w1 = pixelsCount - w0;

            /* Continue to next step if weight background == 0 */
            if(w0 == 0) {
                continue;
            }

            /* We can end now, result will be same to end of cycle */
            if(w1 == 0) {
                break;
            }

            sum0 += i * histogram.at(i);

            /* Get class means */
            u0 = sum0 / w0;
            u1 = (uT-sum0) / w1;

            /* Get sigma */
            sigma = w0 * w1 * (u0 - u1) * (u0 - u1);

            /* Update threshold */
            if(sigma > max) {
                max = sigma;
                threshold = i;
            }
        }

        return threshold;
    }

    void OtsuMethod::run(cv::Mat& result) {
        result = cv::Mat( image.size(), image.type() );

        // Get threshold
        unsigned char threshold = getOtsuThreshold();

        // Thresholding
        performThresholding(threshold, result);
    }

}