#include "DistroDetector.h" 
#include <vector>
#include <fstream>
#include <sstream>

static bool containsWord(const std::string& sentence, const std::string& word) {
    // Helper Function for getPackageManager to search for EXACT word matches
    std::stringstream ss(sentence);
    std::string temp;

    while (ss >> temp) {
        if (temp == word) {
            return true;
        }
    }
    return false;
}

namespace DistroDetector {

    DistroInfo getDistroInfo(){
        std::ifstream osRelease("/etc/os-release");
        std::string line;
        DistroInfo distro;

        while (std::getline(osRelease, line)){
            // Extract name of Linux Distribution    
            if (line.find("ID=") == 0) {
                distro.id = line.substr(3);
                // Remove Quotes if present
                if (!distro.id.empty() && distro.id.front() == '"'){
                    distro.id = distro.id.substr(1, distro.id.length() - 2);
                }
            } else if (line.find("ID_LIKE=") == 0) {
                distro.id_like = line.substr(8);
                if (!distro.id_like.empty() && distro.id_like.front() == '"') {
                    distro.id_like = distro.id_like.substr(1, distro.id_like.length() - 2);
                }
            }    
        }
        return distro;
    }

    DistroConfig getDistroConfig(const DistroInfo& distro) {
        const std::vector<DistroConfig> distros = {
        // id, Package Manager, Install Prefix
        {"arch", "pacman", "sudo pacman -S --needed --noconfirm"},
        {"debian", "apt", "sudo apt install -y"},
        {"fedora", "dnf", "sudo dnf install -y"}
    };
        
        for (const auto& d : distros) {
            // Check for exact ID match OR if it is in the 'like' list
            if (distro.id == d.id || containsWord(distro.id_like, d.id)) {
                return d;
            }
        }  
        return {"unsupported", "Unsupported System", ""};
    }
}