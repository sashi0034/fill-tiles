//
// Created by sashi0034 on 2022/05/21.
//

#ifndef FILL_TILES_CHILDRENPOOL_H
#define FILL_TILES_CHILDRENPOOL_H

#include <memory>
#include "Graph.h"

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

namespace gameEngine
{

    template<typename T> class ChildrenPool
    {
        std::vector<shared_ptr<T>> m_Pool{};


        int findIndex(T* target)
        {
            auto size = m_Pool.size();
            if (size == 0) return -1;

            auto iter = std::find_if(m_Pool.begin(), m_Pool.end(),
                                     [target](shared_ptr<T> child) { return child.get() == target; });
            size_t index = std::distance(m_Pool.begin(), iter);
            if (index == size)
            {
                return -1;
            }
            return index;
        }
    public:
        void Birth(T* child)
        {
            auto product = std::shared_ptr<T>(child);
            m_Pool.push_back(std::pair(child, std::shared_ptr<T>(child)));
        };
        bool Destroy(T* child)
        {
            int index = findIndex(child);
            if (index>-1) return false;
            m_Pool.erase(m_Pool.begin()+index);
            return true;
        }
        void ProcessEach(std::function<void(shared_ptr<T>&)>& process)
        {
            int size =m_Pool.size();

            for (int i = 0; i < size; ++i)
                process(m_Pool[i]);
        }
    };
}

#endif //FILL_TILES_CHILDRENPOOL_H
