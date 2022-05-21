//
// Created by sashi0034 on 2022/05/07.
//

#ifndef FILL_TILES_ARRAYUTILS_H
#define FILL_TILES_ARRAYUTILS_H

#include <vector>
#include <algorithm>

namespace gameEngine
{
    namespace arrayUtils
    {
        template<typename T>
        int FindIndex(const std::vector<T> *arr, T target)
        {
            auto size = (*arr).size();
            if (size == 0) return -1;
            auto iter = std::find((*arr).begin(), (*arr).end(), target);
            size_t index = std::distance((*arr).begin(), iter);
            if (index == size)
            {
                return -1;
            }
            return index;
        }

        template<typename T>
        int Remove(std::vector<T> *arr, T target)
        {
            int index = FindIndex<T>(arr, target);
            if (index == -1) return -1;
            (*arr).erase((*arr).begin() + index);
            return 0;
        }
    }
}


#endif //FILL_TILES_ARRAYUTILS_H
