#pragma once
#include "IStorageAlgorithm.h"

class SingleStorage : public IStorageAlgorithm {
public:
    std::vector<std::string> store(
        const std::vector<std::string>& files,
        const std::string& backupDir,
        std::time_t timestamp
    ) const override;
};
