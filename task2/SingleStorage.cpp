#include "SingleStorage.h"
#include <zip.h>
#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem;

std::vector<std::string> SingleStorage::store(
    const std::vector<std::string>& files,
    const std::string& backupDir,
    std::time_t timestamp
) const {
    std::vector<std::string> storedPaths;
    fs::create_directories(backupDir);

    const std::string zipPath = backupDir + "/backup.zip";

    int error = 0;
    zip_t* zip = zip_open(zipPath.c_str(), ZIP_CREATE | ZIP_EXCL, &error);
    if (!zip) {
        throw std::runtime_error("Failed to create ZIP archive: " + zipPath);
    }

    for (const auto& file : files) {
        if (!fs::exists(file)) {
            zip_close(zip);
            throw std::runtime_error("File not found: " + file);
        }

        const fs::path filePath(file);
        const std::string fileName = filePath.filename().string();

        zip_source_t* source = zip_source_file(zip, file.c_str(), 0, 0);
        if (zip_file_add(zip, fileName.c_str(), source, ZIP_FL_OVERWRITE) < 0) {
            zip_source_free(source);
            zip_close(zip);
            throw std::runtime_error("Failed to add file to ZIP: " + file);
        }
    }

    zip_close(zip);
    storedPaths.push_back(zipPath);
    return storedPaths;
}
