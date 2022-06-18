//
// Created by sashi0034 on 2022/05/21.
//

#ifndef FILL_TILES_CHILDRENPOOL_H
#define FILL_TILES_CHILDRENPOOL_H

#include <memory>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

namespace gameEngine
{
    template<typename T> class IChildrenPool
    {
    public:
        virtual weak_ptr<T> Birth(T* child) = 0;
        virtual void Register(shared_ptr<T>& child)=0;
        virtual bool Destroy(T* child) = 0;
    };


    template<typename T> class ChildrenPool : public IChildrenPool<T>
    {
        std::vector<shared_ptr<T>> m_Pool{};
        int currentProcessingIndex = 0;

        typename std::vector<shared_ptr<T>>::iterator findIterator(T* target)
        {
            assert(!m_Pool.empty());
            assert(currentProcessingIndex < int(m_Pool.size()));

            if (target == m_Pool[currentProcessingIndex].get()) return m_Pool.begin() + currentProcessingIndex;

            auto iter = std::find_if(
                    m_Pool.begin(), m_Pool.end(),
                    [target](shared_ptr<T> child) {
                        return child.get() == target;
                    });

            return iter;
        }

        void collectGarbage(std::vector<int> &upwardIndexes)
        {
            for (int i = upwardIndexes.size() - 1; i >= 0; --i)
            {
                int index = upwardIndexes[i];
                m_Pool.erase(m_Pool.begin() + index);
            }
        }
    public:
        weak_ptr<T> Birth(T* child) override
        {
            auto product = std::shared_ptr<T>(child);
            m_Pool.push_back(product);
            return product;
        };
        template<class CastedType> CastedType* BirthAs(T* child)
        {
            Birth(child);
            auto casted = dynamic_cast<CastedType*>(child);
            return casted;
        }
        void Register(shared_ptr<T>& child) override
        {
            m_Pool.template emplace_back(child);
        };
        bool Destroy(T* child) override
        {
            if (m_Pool.empty()) return false;

            auto iter = findIterator(child);

            if (iter==m_Pool.end()) return false;

            *iter = nullptr;

            return true;
        }
        void ProcessEach(std::function<void(shared_ptr<T>&)> process)
        {
            int size =m_Pool.size();
            std::vector<int> garbage{};

            for (int i = 0; i < size; ++i)
            {
                currentProcessingIndex = i;
                if (m_Pool[i] != nullptr)
                    process(m_Pool[i]);
                else
                    garbage.push_back(i);
            }

            currentProcessingIndex = 0;
            collectGarbage(garbage);
        }
        void Release()
        {
            m_Pool = std::vector<shared_ptr<T>>{};
        }
        ~ChildrenPool()
        {
            assert(m_Pool.size()==0);
        }
    };
}

#endif //FILL_TILES_CHILDRENPOOL_H
