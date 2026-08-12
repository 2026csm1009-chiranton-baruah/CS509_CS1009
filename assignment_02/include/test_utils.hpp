#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

inline std::vector<std::string> collectTests(const std::string& dir) {
    std::vector<std::string> files;

    if (!fs::exists(dir))
        return files;

    for (const auto& entry : fs::directory_iterator(dir)) {
        if (entry.is_regular_file())
            files.push_back(entry.path().string());
    }

    std::sort(files.begin(), files.end());
    return files;
}

#endif
