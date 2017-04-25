#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
#include <vector>

#include "version.h"
#include "Histogram.h"
#include "thresholding/OtsuMethod.h"
#include "thresholding/BalancedHistogramMethod.h"
#include "thresholding/IterativeMethod.h"


using namespace std;

struct arguments {
    string inputPath;
    string outputPath;
    int method;
    int value;

    arguments() : value(-1)
    {}

    void print() {
        cout << "inputPath:  " << inputPath << endl <<
                "outputPath: " << outputPath << endl <<
                "method:     " << method << endl <<
                "value:      " << value << endl;
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
    balanced,
    iterative,
    manual,
    all,
};

enum errorCode {
    noError = 0,
    invalidArguments,
};

map<string, int> thresholdingArgs({{"--otsu", thresholdingOption::otsu},
        {"--balanced", thresholdingOption::balanced},
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
    const int argsCount = 4;
    if (argc != argsCount)
        throw invalid_argument("Invalid count of arguments.\nExpected 4 arguments");

    output.method = getMethod(argv);
    output.inputPath = argv[argsPosition::inputImage];
    output.outputPath = argv[argsPosition::outputImage];
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

int main(int argc, char const* argv[])
{
    int retCode = errorCode::noError;
    cv::Mat inputImage;
    arguments args;
    // Print help if no arguments are given

    try {
        parseArguments(argc, argv, args);
        inputImage = cv::imread(args.inputPath, CV_LOAD_IMAGE_GRAYSCALE);
        Histogram histogram(inputImage);
        cout << histogram << endl;

        performThresholding(inputImage, histogram, args);
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
