#ifndef PACKAGE_RESOLVER_H
#define PACKAGE_RESOLVER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <PackageData.h>

namespace PackageResolver {
    void buildPackageIndex();
    std::string getPackageNames(std::vector<std::string> packages, std::string pm);
    void init();
}

#endif