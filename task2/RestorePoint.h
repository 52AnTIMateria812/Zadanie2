#pragma once
#include <vector>
#include <string>
#include <chrono>

class RestorePoint {
private:
    std::time_t timestamp;
    std::vector<std::string> storedFiles;
    
public:
    RestorePoint(const std::vector<std::string>& files)
        : timestamp(std::chrono::system_clock::to_time_t(
              std::chrono::system_clock::now())),
          storedFiles(files) {}

    std::time_t getTimestamp() const { return timestamp; }
    const std::vector<std::string>& getStoredFiles() const { return storedFiles; }
};
