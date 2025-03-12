#pragma once
#include "IStorageAlgorithm.h"
#include <zip.h>
#include <filesystem>
#include <stdexcept>
#include <iostream>

namespace fs = std::filesystem;

class SplitStorage : public IStorageAlgorithm {
public:
    std::vector<std::string> store(const std::vector<std::string>& files,
                                  const std::string& backupDir) const override {
        std::vector<std::string> storedPaths;
        fs::create_directories(backupDir);

        for (const auto& file : files) {
            if (!fs::exists(file)) {
                throw std::runtime_error("File not found: " + file);
            }

            const fs::path filePath(file);
            const std::string fileName = filePath.filename().string();
            const std::string zipPath = backupDir + "/" + fileName + ".zip";

            // Создаем ZIP-архив
            int error = 0;
            zip_t* zip = zip_open(zipPath.c_str(), ZIP_CREATE | ZIP_EXCL, &error);
            if (!zip) {
                throw std::runtime_error("Failed to create ZIP archive: " + zipPath);
            }

            // Добавляем файл в архив
            zip_source_t* source = zip_source_file(zip, file.c_str(), 0, 0);
            if (zip_file_add(zip, fileName.c_str(), source, ZIP_FL_OVERWRITE) < 0) {
                zip_source_free(source);
                zip_close(zip);
                throw std::runtime_error("Failed to add file to ZIP: " + file);
            }

            // Закрываем архив
            zip_close(zip);
            storedPaths.push_back(zipPath);
        }

        return storedPaths;
    }
};
