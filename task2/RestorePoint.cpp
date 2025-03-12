#include "RestorePoint.h"

RestorePoint::RestorePoint(const std::vector<std::string>& files, std::time_t timestamp)
    : timestamp(timestamp), storedFiles(files) {}

std::time_t RestorePoint::getTimestamp() const {
    return timestamp;
}

const std::vector<std::string>& RestorePoint::getStoredFiles() const {
    return storedFiles;
}
