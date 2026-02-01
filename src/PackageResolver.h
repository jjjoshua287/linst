#ifndef PACKAGE_RESOLVER_H
#define PACKAGE_RESOLVER_H

#include <string>
#include <vector>
#include "DistroDetector.h"

namespace PackageResolver {
    
    std::vector<std::string> resolvePackages(std::vector<std::string> userPackages, DistroConfig distro);
}

#endif