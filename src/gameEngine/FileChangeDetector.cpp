//
// Created by sashi0034 on 2022/06/20.
//

#include "FileChangeDetector.h"

#include <utility>

namespace fs = std::filesystem;

namespace inGame
{
    FileChangeDetector::FileChangeDetector(std::string dirPath)
            : m_DirPath(std::move(dirPath))
    {
        update();
    }

    bool FileChangeDetector::CheckChanged()
    {
        return update();
    }

    bool FileChangeDetector::update()
    {
        bool result = false;

        const int numOldFiles = m_FileInfo.size();
        int numCurrFiles = 0;

        for (const fs::directory_entry& file : fs::recursive_directory_iterator(m_DirPath)) {
            ++numCurrFiles;

            const auto filePath = file.path();
            const auto lastWriteTime = fs::last_write_time(filePath);

            if (m_FileInfo.count(filePath)==0) {
                m_FileInfo[filePath] = lastWriteTime;
            }
            else if (m_FileInfo[filePath] != lastWriteTime)
            {
                m_FileInfo[filePath] = lastWriteTime;
                result = true;
            }
        }

        if (numCurrFiles!=numOldFiles) result = true;

        return result;
    }
}
