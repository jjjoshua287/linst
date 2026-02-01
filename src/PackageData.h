#ifndef PACKAGEDATA_H
#define PACKAGEDATA_H

#include <string>
#include <vector>
#include <map>

struct Package {
    std::string name;
    std::string description;
    std::string dnf;
    std::string apt;
    std::string pacman;
};

struct Category {
    std::string name;
    std::vector<Package> packages;
};

// Repo-only catalog:
// Convention: empty string = not available in default repos for that distro family.
// Your installer should skip and print the description.
inline std::vector<Category> getPackageData() {
    return {
        {
            "Browsers",
            {
                {"firefox", "Mozilla's web browser", "firefox", "firefox", "firefox"},
                {"chromium", "Open-source Chromium browser", "chromium", "chromium", "chromium"},

                // Repo-only: skip (Chrome needs Google's repo; Arch is AUR)
                {"google chrome", "Requires third-party repo/AUR (repo-only mode skips)", "", "", ""},

                // Repo-only: typically third-party on apt/dnf; often AUR on Arch
                {"brave", "Requires third-party repo/AUR (repo-only mode skips)", "", "", ""}
            }
        },
        {
            "Development",
            {
                // Repo-only: VS Code usually requires Microsoft's repo; Arch is typically AUR
                {"vs code", "Requires third-party repo/AUR (repo-only mode skips)", "", "", ""},

                {"git", "Version control", "git", "git", "git"},

                // Repo-only (these exist in repos)
                {"docker", "Container platform", "docker", "docker.io", "docker"},
                {"podman", "Daemonless container engine", "podman", "podman", "podman"},
                {"neovim", "Modern Vim-based editor", "neovim", "neovim", "neovim"},
                {"cmake", "Build system generator", "cmake", "cmake", "cmake"},
                {"make", "Build tool", "make", "make", "make"}
            }
        },
        {
            "Communication",
            {
                {"discord", "Voice and text chat (availability varies by distro)", "", "", "discord"},
                {"telegram", "Telegram Desktop client", "", "", "telegram-desktop"}
            }
        },
        {
            "Media",
            {
                {"vlc", "Media player", "vlc", "vlc", "vlc"},
                {"mpv", "Minimal media player", "mpv", "mpv", "mpv"},
                {"obs studio", "Screen recording & streaming", "obs-studio", "obs-studio", "obs-studio"}
            }
        },
        {
            "Utilities",
            {
                {"curl", "Command-line HTTP client", "curl", "curl", "curl"},
                {"wget", "Command-line downloader", "wget", "wget", "wget"},
                {"htop", "Interactive process viewer", "htop", "htop", "htop"},
                {"tmux", "Terminal multiplexer", "tmux", "tmux", "tmux"},
                {"unzip", "Extract .zip archives", "unzip", "unzip", "unzip"},
                {"zip", "Create .zip archives", "zip", "zip", "zip"}
            }
        }
    };
}


#endif