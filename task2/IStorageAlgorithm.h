#pragma once
#include <vector>
#include <string>

class IStorageAlgorithm {
public:
    virtual ~IStorageAlgorithm() = default;
    virtual std::vector<std::string> store(
        const std::vector<std::string>& files,
        const std::string& backupDir,
        std::time_t timestamp
    ) const = 0;
};
