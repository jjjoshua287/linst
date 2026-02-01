#include <iostream>
#include <string>
#include <vector>
#include "DistroDetector.h"
#include "PackageResolver.h"

void buildCommand(std::vector<std::string> names, std::string prefix) {
    std::cout << prefix << " ";
    for (const auto& name : names) {
        std::cout << name << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: linst package1 package2 package3 ..." << std::endl;
        return 1;
    }

    DistroInfo info = DistroDetector::getDistroInfo();
    DistroConfig cfg = DistroDetector::getDistroConfig(info);
    if (cfg.id == "unsupported") {
        std::cerr << "Error: Unsupported Linux Distribution." << std::endl;
        return 1;
    }

    std::vector<std::string> userPkgs(argv + 1, argv + argc);
    std::vector<std::string> names = PackageResolver::resolvePackages(userPkgs, cfg);
    buildCommand(names, cfg.cmd);

    return 0;
}