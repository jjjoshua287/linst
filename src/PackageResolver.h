#ifndef PACKAGE_RESOLVER_H
#define PACKAGE_RESOLVER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <PackageData.h>

namespace PackageResolver {
    void buildPackageIndex();
    void buildPackageList(std::vector<std::string> userPackages, std::string pm);
    void init(std::vector<std::string> userPackages, DistroConfig distro);
}

#endif