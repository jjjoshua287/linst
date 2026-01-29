#include <iostream>
#include <string>
#include <vector>
#include "DistroDetector.h"
#include "PackageResolver.h"

void test(DistroInfo info, DistroConfig cfg) {
    // Print Results --- Testing Purposes
    std::cout << "-----    DistroDetector Test    -----" << std::endl;
    std::cout << "Raw ID:          " << info.id << std::endl;
    std::cout << "Like:            " << info.id_like << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Package Manager: " << cfg.manager << std::endl;
    std::cout << "Command Prefix:  " << cfg.cmd << std::endl;
}

int main(int argc, char* argv[]) {
    DistroInfo info = DistroDetector::getDistroInfo();
    DistroConfig cfg = DistroDetector::getDistroConfig(info);

    if (cfg.id == "unsupported") {
        std::cerr << "Error: Unsupported Linux Distribution." << std::endl;
        return 1;
    }
    std::vector<std::string> usrPkg; // temp testing vector
    usrPkg[0] = "firefox";
    PackageResolver::init(usrPkg, cfg);

    return 0;
}