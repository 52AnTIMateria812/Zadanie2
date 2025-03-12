#include "BackupJob.h"
#include <filesystem>
#include <stdexcept>
#include <algorithm>

namespace fs = std::filesystem;

BackupJob::BackupJob(std::unique_ptr<IStorageAlgorithm> algorithm, const std::string& storageDir)
    : storageAlgorithm(std::move(algorithm)), storagePath(storageDir) {
    fs::create_directories(storageDir);
}

void BackupJob::addObject(const std::string& filePath) {
    if (!fs::exists(filePath)) {
        throw std::runtime_error("File does not exist: " + filePath);
    }
    backupObjects.push_back(filePath);
}

void BackupJob::removeObject(const std::string& filePath) {
    auto it = std::find(backupObjects.begin(), backupObjects.end(), filePath);
    if (it == backupObjects.end()) {
        throw std::runtime_error("File not in job: " + filePath);
    }
    backupObjects.erase(it);
}

void BackupJob::createRestorePoint() {
    if (backupObjects.empty()) {
        throw std::runtime_error("No files to backup");
    }

    const std::time_t now = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now());
    const std::string backupDir = storagePath + "/" + std::to_string(now);

    auto storedPaths = storageAlgorithm->store(backupObjects, backupDir, now);
    restorePoints.emplace_back(storedPaths, now);
}
