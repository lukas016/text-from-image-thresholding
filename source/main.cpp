#include <iostream>
#include <string>
#include <vector>

#include "version.h"

using namespace std;

void printHelp()
{
    cout << "Help for cleanCppApplication " << endl;
    cout << "Version: " << Version::getVersionLong() << endl;
    cout << "Author:  " << endl;
    cout << "URL:     " << endl;
    /// @todo Do stuff in here also
}


int main(int argc, char const* argv[])
{
    // Print help if no arguments are given
    if (argc == 1)
        printHelp();

    return 0;
}
