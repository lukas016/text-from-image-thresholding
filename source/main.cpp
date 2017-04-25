#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
#include <vector>

#include "version.h"
#include "Histogram.h"
#include "thresholding/Algorithm.h"
#include "thresholding/AdaptiveGaussMethod.h"
#include "thresholding/AdaptiveMeanCMethod.h"


using namespace std;
using namespace thresholding;

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
    adaptiveGauss,
    adaptiveMeanC,
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
    const int argsCount = 4;
    if (argc != argsCount)
        throw invalid_argument("Invalid count of arguments.\nExpected 4 arguments");

    output.method = getMethod(argv);
    output.inputPath = argv[argsPosition::inputImage];
    output.outputPath = argv[argsPosition::outputImage];
}


int main(int argc, char const* argv[])
{
    int retCode = errorCode::noError;
    cv::Mat inputImage;
    cv::Mat outputImage;
    arguments args;
    Algorithm *algorithm;

    // Print help if no arguments are given
    try {
        parseArguments(argc, argv, args);
        inputImage = cv::imread(args.inputPath, CV_LOAD_IMAGE_GRAYSCALE);
        Histogram histogram(inputImage);

        // TODO: nevsimla jsem si metody all, tak asi predelat
        switch (args.method) {
            case thresholdingOption::adaptiveMeanC:
                algorithm = new AdaptiveMeanCMethod(inputImage, histogram);
                break;
            case thresholdingOption::adaptiveGauss:
                algorithm = new AdaptiveGaussMethod(inputImage, histogram);
                break;
            default:
                algorithm = nullptr;
        }

        if (algorithm == nullptr) {
            return 0;
        }

        // Run the algorithm
        algorithm->run(outputImage);

        // Write image to the output file
        cv::imwrite(args.outputPath, outputImage);
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
