/**
 * @file:   OtsuMethod.cpp
 * @author: Tom Svoboda <xsvobo0l@stud.fit.vutbr.cz>
 * @date:   12. 04. 2017
 */

#include "OtsuMethod.h"

namespace thresholding {

    OtsuMethod::OtsuMethod(const cv::Mat& _image, const Histogram& _histogram, bool _halfThresholding) :
        Algorithm(_image, _histogram, _halfThresholding) {
        name = "Otsu'sMethod";
    }

    int OtsuMethod::getOtsuThreshold() {
        int pixelsCount = image.rows * image.cols;
        double uT = 0.0;
        double w0 = 0;   /** < Weight background */
        double w1;       /** < Weight foreground */
        double u0 = 0;   /** < Mean background */
        double u1 = 0;   /** < Mean foreground */
        double sum0 = 0; /** < Sum background */
        double sigma;
        double max = 0;
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
