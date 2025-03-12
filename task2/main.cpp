#include <iostream>
#include "BackupJob.h"
#include "SplitStorage.h"
#include "SingleStorage.h"

int main() {
    try {
        // Пример с раздельным хранением
        BackupJob splitJob(std::make_unique<SplitStorage>(), "backups_split");
        splitJob.addObject("test1.txt");
        splitJob.addObject("test2.jpg");
        splitJob.createRestorePoint();

        // Пример с общим хранилищем
        BackupJob singleJob(std::make_unique<SingleStorage>(), "backups_single");
        singleJob.addObject("test3.doc");
        singleJob.createRestorePoint();

        // Обработка ошибок
        try {
            singleJob.addObject("non_existent.file");
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
