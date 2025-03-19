#pragma once
#include "IStorageAlgorithm.h"

class SplitStorage : public IStorageAlgorithm {
public:
    std::vector<std::string> store(
        const std::vector<std::string>& files,
        const std::string& backupDir,
        std::time_t timestamp
    ) const override;
};
