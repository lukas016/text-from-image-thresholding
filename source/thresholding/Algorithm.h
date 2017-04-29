/**
 * @file:   Base.h
 * @author: Tom Svoboda <xsvobo0l@stud.fit.vutbr.cz>
 * @date:   12. 04. 2017
 */

#ifndef BASE_H
#define BASE_H

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <string>

#include "../Histogram.h"

namespace thresholding {

    /**
     * Common base class for all thresholding algorithm objects
     */
    class Algorithm {
    public:
        Algorithm(const cv::Mat& _image, const Histogram& _histogram, bool _halfThresholding = false) : image(_image), histogram(_histogram), halfThresholding(_halfThresholding) {};
        virtual ~Algorithm() {};

        /**
         * Run algorithm and get result
         * @param result Reference to matrix where result thresholded image will be written
         */
        virtual void run(cv::Mat& result) = 0;

        /**
         * Return name of algorithm
         * @return std::string name
         */
        inline std::string getName() {return name;};

    protected:
        const cv::Mat& image;
        const Histogram& histogram;
        bool halfThresholding;
        std::string name;

        /**
         * Perform standard thresholding with given threshold
         * @param threshold Value of threshold
         * @param result Reference to matrix where thresholding result will be stored
         */
        void performThresholding(unsigned char threshold, cv::Mat& result);
    };

}

#endif /* BASE_H */