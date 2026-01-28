#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <locale>
#include <unordered_map>

#include "PackageData.h"
#include "PackageResolver.h"

enum class PackageManager { apt, dnf, pacman };

bool is_available(const Package& package, PackageManager pm) {
    switch (pm) {
        case PackageManager::apt: return !(package.apt.empty());
        case PackageManager::dnf: return !(package.dnf.empty());
        case PackageManager::pacman: return !(package.pacman.empty());
    }
    return false;
}

std::string normalize(std::string str) {
    // Remove all spaces from string
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

    // Convert string to lowercase
    for (char& c : str) {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    return str;
}

namespace PackageResolver {

    std::unordered_map<std::string, const Package*> buildPackageIndex() {
        std::vector<Category> packages = getPackageData();
        std::unordered_map<std::string, const Package*> pkgMap;

        for (const auto& category : packages) { 
            // Categories
            for (const auto& package : category.packages) { 
                // Packages in category
                std::string normalString = normalize(package.name);
                pkgMap[normalString] = &package; // build unordered_map
            }
        }
        return pkgMap;
    }

    std::string getPackageNames(vector<string> packages, std::string pm){
        return pm;
    }
}