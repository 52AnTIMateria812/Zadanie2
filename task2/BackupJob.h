#pragma once
#include <vector>
#include <string>
#include <memory>
#include "IStorageAlgorithm.h"
#include "RestorePoint.h"

class BackupJob {
public:
    BackupJob(std::unique_ptr<IStorageAlgorithm> algorithm, const std::string& storageDir);
    void addObject(const std::string& filePath);
    void removeObject(const std::string& filePath);
    void createRestorePoint();

private:
    std::vector<std::string> objects;
    std::vector<RestorePoint> restorePoints;
    std::unique_ptr<IStorageAlgorithm> storageAlgorithm;
    std::string storagePath;
};
