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

void buildCommand(std::vector<std::string> names, std::string prefix) {
    std::cout << prefix << " ";
    for (const auto& name : names) {
        std::cout << name << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    DistroInfo info = DistroDetector::getDistroInfo();
    DistroConfig cfg = DistroDetector::getDistroConfig(info);
    if (cfg.id == "unsupported") {
        std::cerr << "Error: Unsupported Linux Distribution." << std::endl;
        return 1;
    }
    std::vector<std::string> usrPkg; // temp testing vector
    usrPkg.push_back("firefox");
    usrPkg.push_back("git");
    usrPkg.push_back("docker");
    std::vector<std::string> names = PackageResolver::resolvePackages(usrPkg, cfg);
    
    buildCommand(names, cfg.cmd);

    return 0;
}