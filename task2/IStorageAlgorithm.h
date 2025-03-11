#pragma once
#include <vector>
#include <string>
#include <unique_ptr>

class IStorageAlgorithm {
public:
    virtual ~IStorageAlgorithm() = default;
    virtual std::vector<std::string> store(const std::vector<std::string>& files, 
                                          const std::string& backupDir) const = 0;
};

class BackupJob {
private:
    std::vector<std::string> objects;  // Файлы для резервного копирования
    std::vector<RestorePoint> restorePoints;  // Созданные точки восстановления
    std::unique_ptr<IStorageAlgorithm> storageAlgorithm;  // Алгоритм хранения
    std::string storagePath;  // Путь для хранения резервных копий

public:
    // Конструктор, методы для добавления/удаления файлов и создания точек восстановления
};

class RestorePoint {
private:
    std::time_t timestamp;  // Временная метка создания
    std::vector<std::string> storedFiles;  // Пути к сохраненным файлам
    
public:
    // Конструктор и методы доступа
};