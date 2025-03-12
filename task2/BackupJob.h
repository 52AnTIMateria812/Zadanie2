#pragma once
#include "IStorageAlgorithm.h"
#include "RestorePoint.h"
#include <vector>
#include <memory>
#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem;

class BackupJob {
private:
    std::vector<std::string> objects;
    std::vector<RestorePoint> restorePoints;
    std::unique_ptr<IStorageAlgorithm> storageAlgorithm;
    std::string storagePath;

public:
    BackupJob(std::unique_ptr<IStorageAlgorithm> algorithm, 
             const std::string& storageDir)
        : storageAlgorithm(std::move(algorithm)),
          storagePath(storageDir) {
        fs::create_directories(storageDir);
    }

    void addObject(const std::string& filePath) {
        if (!fs::exists(filePath)) {
            throw std::runtime_error("File does not exist: " + filePath);
        }
        objects.push_back(filePath);
    }

    void removeObject(const std::string& filePath) {
        auto it = std::find(objects.begin(), objects.end(), filePath);
        if (it == objects.end()) {
            throw std::runtime_error("File not in job: " + filePath);
        }
        objects.erase(it);
    }

    void createRestorePoint() {
        if (objects.empty()) {
            throw std::runtime_error("No files to backup");
        }
        
        const std::time_t now = std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now());
        const std::string backupDir = storagePath + "/" + std::to_string(now);
        
        auto storedPaths = storageAlgorithm->store(objects, backupDir);
        restorePoints.emplace_back(storedPaths);
    }
};
