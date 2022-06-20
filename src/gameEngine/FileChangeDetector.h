//
// Created by sashi0034 on 2022/06/20.
//

#ifndef FILL_TILES_FILECHANGEDETECTOR_H
#define FILL_TILES_FILECHANGEDETECTOR_H

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <iomanip>
#include <unordered_map>

namespace inGame
{
    class FileChangeDetector
    {
    public:
        explicit FileChangeDetector(std::string dirPath);
        bool CheckChanged();
    private:
        bool update();
        std::string m_DirPath;
        std::unordered_map<std::string, std::filesystem::file_time_type> m_FileInfo{};
    };
}


#endif //FILL_TILES_FILECHANGEDETECTOR_H
