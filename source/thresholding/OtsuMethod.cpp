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
        float Wb, Wf;
        float Ub, Uf;
        float ssb, ssf; // square sigma
        float sswMin = 255;
        int threshold = 0;

        int n = 256;

        for(int t=0; t<n;t++) {
            Wb = 0;
            float UbTop = 0, UbBot = 0;

            /* Compute Weight backround, weight foreground, mean background, mean foreground */
            for(int i=0; i<t;i++) {
                Wb    += histogram.at(i);
                UbTop += i*histogram.at(i);
                UbBot += histogram.at(i);
            }

            Wb /= image.rows*image.cols;
            Ub = UbTop/UbBot;
            Wf = 1-Wb;

            float UfTop = 0, UfBot = 0;

            for(int i=t; i<n; i++) {
                UfTop += i*histogram.at(i);
                UfBot += histogram.at(i);
            }

            Uf = UfTop/UfBot;

            /* Compute square sigmas */
            ssb = 0;

            for(int i=0; i<t; i++) {
                ssb += ((i-Ub)*(i-Ub)) * histogram.at(i);
            }

            ssb /= UbBot;

            ssf = 0;

            for(int i=t; i<n; i++) {
                ssf += ((i-Uf)*(i-Uf)) * histogram.at(i);
            }

            ssf /= UfBot;

            /* Compute sigma square W and check is is minimum */
            float ssw = Wb * ssb + Wf * ssf;

            if(ssw < sswMin) {
                sswMin = ssw;
                threshold = t;
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