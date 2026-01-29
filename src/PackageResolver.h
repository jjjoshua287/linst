#ifndef PACKAGE_RESOLVER_H
#define PACKAGE_RESOLVER_H

#include <string>
#include <vector>
#include "DistroDetector.h"

namespace PackageResolver {
    
    void init(std::vector<std::string> userPackages, DistroConfig distro);
}

#endif