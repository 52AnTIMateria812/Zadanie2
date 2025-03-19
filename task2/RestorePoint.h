#pragma once
#include <vector>
#include <string>
#include <ctime>

class RestorePoint {
public:
    RestorePoint(const std::vector<std::string>& files, std::time_t timestamp);
    std::time_t getTimestamp() const;
    const std::vector<std::string>& getStoredFiles() const;

private:
    std::time_t timestamp;
    std::vector<std::string> storedFiles;
};
