#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <vector>

#ifdef DURATION
    #include <chrono>
#endif

#include "version.h"
#include "Histogram.h"
#include "thresholding/OtsuMethod.h"
#include "thresholding/BalancedHistogramMethod.h"
#include "thresholding/IterativeMethod.h"
#include "thresholding/AdaptiveGaussMethod.h"
#include "thresholding/AdaptiveMeanCMethod.h"


using namespace std;
using namespace thresholding;

struct arguments {
    string inputPath;
    string outputPath;
    int method;
    int value;
    bool halfThresholding;

    arguments() : value(-1)
    {}

    void print() {
        cout << "inputPath:  " << inputPath << endl <<
                "outputPath: " << outputPath << endl <<
                "method:     " << method << endl <<
                "value:      " << value << endl;
    }

    string getOutput(const string &methodName = "") {
        return outputPath + methodName + ".png";
    }
};

enum argsPosition {
    name = 0,
    method,
    inputImage,
    outputImage,
};

enum thresholdingOption {
    otsu = 0,
    adaptiveGauss,
    adaptiveMeanC,
    balanced,
    iterative,
    manual,
    all, //must be last
};

enum errorCode {
    noError = 0,
    invalidArguments,
};

map<string, int> thresholdingArgs({{"--otsu", thresholdingOption::otsu},
        {"--balanced", thresholdingOption::balanced},
        {"--adaptiveGauss", thresholdingOption::adaptiveGauss},
        {"--adaptiveMeanC", thresholdingOption::adaptiveMeanC},
        {"--iterative", thresholdingOption::iterative},
        {"--manual=", thresholdingOption::manual},
        {"--all", thresholdingOption::all}});

void printHelp()
{
    cout << "Help for cleanCppApplication " << endl;
    cout << "Version: " << Version::getVersionLong() << endl;
    cout << "Author:  " << endl;
    cout << "URL:     " << endl;
    /// @todo Do stuff in here also
}

int getMethod(char const* argv[])
{
    auto it = thresholdingArgs.find(argv[argsPosition::method]);

    if (it == thresholdingArgs.end())
        throw invalid_argument("Invalid argument " + string(argv[argsPosition::method]));

    return it->second;
}

void parseArguments(int argc, char const** argv, arguments & output)
{
    const int minArgs = 4;
    const int maxArgs = 5;
    if (argc < minArgs || argc > maxArgs)
        throw invalid_argument("Invalid count of arguments.\nExpected 4 arguments");

    output.method = getMethod(argv);
    output.inputPath = argv[argsPosition::inputImage];
    output.outputPath = argv[argsPosition::outputImage];

    if (argc == maxArgs)
        if (string("--half") == argv[4])
            output.halfThresholding = true;
}

void performThresholding(cv::Mat& inputImage, Histogram& histogram, arguments& args) {
    cv::Mat outputImage;

    cv::namedWindow( "Original", CV_WINDOW_AUTOSIZE );  // Create a window for display.
    cv::imshow( "Original", inputImage );              // Show our image inside it.

    if(args.method == thresholdingOption::otsu || args.method == thresholdingOption::all) {
        thresholding::OtsuMethod otsu(inputImage, histogram);
        otsu.run(outputImage);

        cv::imwrite(args.outputPath + ".otsu.png", outputImage);

        cv::namedWindow( otsu.getName(), CV_WINDOW_AUTOSIZE );  // Create a window for display.
        cv::imshow( otsu.getName(), outputImage );              // Show our image inside it.
    }
    if(args.method == thresholdingOption::balanced || args.method == thresholdingOption::all) {
        thresholding::BalancedHistogramMethod bht(inputImage, histogram);
        bht.run(outputImage);

        cv::imwrite(args.outputPath + ".bht.png", outputImage);

        cv::namedWindow( bht.getName(), CV_WINDOW_AUTOSIZE );  // Create a window for display.
        cv::imshow( bht.getName(), outputImage );              // Show our image inside it.
    }
    if(args.method == thresholdingOption::iterative || args.method == thresholdingOption::all) {
        thresholding::IterativeMethod iterative(inputImage, histogram);
        iterative.run(outputImage);

        cv::imwrite(args.outputPath + ".iterative.png", outputImage);

        cv::namedWindow( iterative.getName(), CV_WINDOW_AUTOSIZE );  // Create a window for display.
        cv::imshow( iterative.getName(), outputImage );              // Show our image inside it.
    }
    if(args.method == thresholdingOption::manual) {
        if(args.value < 0) {
            throw std::invalid_argument("Bad manual threshold argument");
        }

        throw std::runtime_error("Manual thresholding not supported yet");
    }

    cv::waitKey(0);
}

void saveImageWithTransparentBg(const string& outputFile, const cv::Mat &in) {
    uint8_t white = 255;
    cv::Mat outputMat;
    cv::cvtColor(in, outputMat, CV_GRAY2BGRA);
    for (int64_t x = 0; x < in.rows; ++x)
        for (int64_t y = 0; y < in.cols; ++y) {
            cv::Vec4b & pixel = outputMat.at<cv::Vec4b>(x,y);
            if (pixel[0] == white && pixel[1] == white && pixel[2] == white)
                pixel[3] = 0;
        }

    imwrite(outputFile, outputMat);
}

int main(int argc, char const* argv[])
{
    int retCode = errorCode::noError;
    cv::Mat inputImage;
    cv::Mat outputImage;
    arguments args;
    unique_ptr<Algorithm> algorithm = nullptr;
    bool allSet = false;
#ifdef DURATION
    chrono::time_point<chrono::system_clock> start, end;
#endif
    // Print help if no arguments are given
    try {
        parseArguments(argc, argv, args);
        inputImage = cv::imread(args.inputPath, CV_LOAD_IMAGE_GRAYSCALE);
        Histogram histogram(inputImage);

        //performThresholding(inputImage, histogram, args);
        // TODO: nevsimla jsem si metody all, tak asi predelat
        if (args.method == all) {
            allSet = true;
            args.method = 0;
        }

        while (args.method < all) {
            if (allSet && args.method == manual) {
                args.method++;
                continue;
            }

            switch (args.method) {
                case thresholdingOption::otsu:
                    algorithm = make_unique<OtsuMethod>(inputImage, histogram, args.halfThresholding);
                    break;
                case thresholdingOption::balanced:
                    algorithm = make_unique<BalancedHistogramMethod>(inputImage, histogram, args.halfThresholding);
                    break;
                case thresholdingOption::iterative:
                    algorithm = make_unique<IterativeMethod>(inputImage, histogram, args.halfThresholding);
                    break;
                case thresholdingOption::adaptiveMeanC:
                    algorithm = make_unique<AdaptiveMeanCMethod>(inputImage, histogram);
                    break;
                case thresholdingOption::adaptiveGauss:
                    algorithm = make_unique<AdaptiveGaussMethod>(inputImage, histogram);
                    break;
                default:
                    runtime_error("Invalid method option");
                    break;
            }

            // Run the algorithm
#ifdef DURATION
            start = chrono::system_clock::now();
#endif
            algorithm->run(outputImage);
#ifdef DURATION
            end = chrono::system_clock::now();
            chrono::duration<double> elapsedSeconds = end - start;
            chrono::microseconds micro = chrono::duration_cast<chrono::microseconds>(elapsedSeconds);
            cout << micro.count() << endl;
#endif
            if (allSet) {
                // Write image to the output file
                saveImageWithTransparentBg(args.getOutput(algorithm->getName()), outputImage);
                args.method++;
            }
            else {
                saveImageWithTransparentBg(args.getOutput(), outputImage);
                break;
            }
        }


    }
    catch (invalid_argument &e) {
        cerr << e.what() << endl;
        printHelp();
        retCode = errorCode::invalidArguments;
    }
    catch (exception &e) {
        cerr << e.what() << endl;
        retCode = errorCode::invalidArguments;
    }

    return retCode;
}
