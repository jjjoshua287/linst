#include "PackageResolver.h"

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <format>

#include "DistroDetector.h"
#include "PackageData.h"
#include "StringUtils.h"

namespace {

    std::vector<Category> packages;
    std::unordered_map<std::string, const Package*> pkgMap;
    std::vector<const Package*> packagePtrs;

    // Determines if package can be installed with package manager    
    bool is_available(const Package& package, std::string pm) {
        // Optimize Later ...
        if (pm == "apt") {return !(package.apt.empty());}
        else if (pm == "dnf") {return !(package.dnf.empty());}
        else if (pm == "pacman") {return !(package.pacman.empty());}
        return false;
    }

    // Finds the desired package and returns a ptr to it, else a nullptr if it doesn't exist.
    const Package* findByName(std::string name) { 
        std::string key = StringUtils::normalize(name); // Normalized name
        auto it = pkgMap.find(key);
        if (it == pkgMap.end()) {
            return nullptr;
        }
        return it->second;
    }
    
    // fills in unordered map of package data from PackageData.h, turning into ptrs to individual packages.
    void buildPackageIndex() {
        for (const auto& category : packages) { 
            // Categories
            for (const auto& package : category.packages) { 
                // Packages in category
                std::string normalString = StringUtils::normalize(package.name);
                pkgMap[normalString] = &package;
            }
        }
    }

    // Fills vector pkgMap with ptrs to user selected packages.
    void buildPackageList(std::vector<std::string> userPackages, std::string pm) {
        int i = 0;
        for (const auto& u : userPackages) {
            const Package* ptr = findByName(u);
            if (ptr == nullptr) {
                std::string s = std::format("Package '{}' not found, skipping...", u);
                std::cerr << s << std::endl;
                continue;
            }
            if (!is_available(*ptr, pm)) {
                std::string s = std::format("Package '{}' cannot be installed with your system's package manager.", u);
                std::cerr << s << std::endl;
                continue;
            }
                packagePtrs.push_back(ptr);
                i++;
        }
    }
}

namespace PackageResolver {
    
    // returns list of resolved package names to system's package manager
    std::vector<std::string> resolvePackages(std::vector<std::string> userPackages, DistroConfig distro) {
        std::vector<std::string> resolvedNames;

        // Initialize data
        packages = getPackageData();
        buildPackageIndex();
        buildPackageList(userPackages, distro.manager);
        
        // map mapping package manager to correct field in Package Struct
        static const std::unordered_map<std::string, std::string Package::*> mgrMap = {
            {"apt", &Package::apt},
            {"dnf", &Package::dnf},
            {"pacman", &Package::pacman}
        };

        auto it = mgrMap.find(distro.manager);
        if (it == mgrMap.end()) {
            std::cerr << "Unknown package manager: " << distro.manager << std::endl;
            return {};
        }

        std::string Package::* pkgName = it->second;
        for (const auto& pkg : packagePtrs) {
            resolvedNames.push_back(pkg->*pkgName);
        }
        return resolvedNames;
    }
}