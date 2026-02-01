#ifndef DISTRO_DETECTOR_H
#define DISTRO_DETECTOR_H

#include <string>

// -- Struct Definitions --
struct DistroInfo {
    std::string id; // Name of Distribution
    std::string id_like; // Base Distribution is built on top of (empty if already Base Distribution)
};

struct DistroConfig {
    std::string id; // base distribution name (e.g. arch, debian, fedora)
    std::string manager; // respective package manager (e.g. pacman, apt, dnf)
    std::string cmd; // Install command prefix (e.g. `sudo dnf install -y`)
};

namespace DistroDetector {

    // Reads /etc/os-release and fills in the DistroInfo struct
    DistroInfo getDistroInfo();

    // Takes DistroInfo struct and fills in the DistroConfig struct
    DistroConfig getDistroConfig(const DistroInfo& distro);
}

#endif