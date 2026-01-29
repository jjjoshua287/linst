#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <locale>
#include <unordered_map>
#include <format>

#include "DistroDetector.h"
#include "PackageData.h"
#include "PackageResolver.h"

// Anonymous Namespace
namespace {

    std::vector<Category> packages;
    std::unordered_map<std::string, const Package*> pkgMap;
    std::vector<const Package*> packagePtrs;

    bool is_available(const Package& package, std::string pm) {
        // Optimize Later ...
        if (pm == "apt") {return !(package.apt.empty());}
        else if (pm == "dnf") {return !(package.dnf.empty());}
        else if (pm == "pacman") {return !(package.pacman.empty());}
        return false;
    }

    std::string normalize(std::string str) {
        // Remove all spaces from string
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
        for (char& c : str) {
            c = std::tolower(static_cast<unsigned char>(c));
        }
        return str;
    }

    const Package* findByName(std::string name) { 
        std::string key = normalize(name); // Normalized name
        auto it = pkgMap.find(key);
        if (it == pkgMap.end()) {
            return nullptr;
        }
        return it->second;
    }
    
    void buildPackageIndex() {
        for (const auto& category : packages) { 
            // Categories
            for (const auto& package : category.packages) { 
                // Packages in category
                std::string normalString = normalize(package.name);
                pkgMap[normalString] = &package;
            }
        }
    }

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
} // End Anonymous Namespace

// Public Namespaces
namespace PackageResolver {
    
    void init(std::vector<std::string> userPackages, DistroConfig distro) {
        packages = getPackageData();
        buildPackageIndex();
        buildPackageList(userPackages, distro.manager);
        for (const auto& pkg :  packagePtrs) {
            std::cout << pkg->name << " ";
        }
        std::cout << std::endl;
    }
}