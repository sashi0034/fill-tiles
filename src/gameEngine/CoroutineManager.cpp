//
// Created by sashi0034 on 2022/05/24.
//

#include "CoroutineManager.h"

using namespace boost::coroutines2;
namespace gameEngine{

    weak_ptr<boost::coroutines2::coroutine<CoroTask>::pull_type> CoroutineManager::Start(boost::coroutines2::coroutine<CoroTask>::pull_type *task)
    {
        auto childPtr = m_Pool.Birth(task);
        return childPtr;
    }

    bool CoroutineManager::Destroy(boost::coroutines2::coroutine<CoroTask>::pull_type *task)
    {
        return m_Pool.Destroy(task);
    }

    void CoroutineManager::UpdateEach()
    {
        std::vector<coroutine<CoroTask>::pull_type*> garbageList{};

        m_Pool.ProcessEach([&](shared_ptr<coroutine<CoroTask>::pull_type>& task){{
            (*task)();
            if (*task)
                {}
            else
                garbageList.push_back(task.get());
        }});

        for (auto garbage : garbageList)
            Destroy(garbage);
    }

    CoroutineManager::~CoroutineManager()
    {
        m_Pool.Release();
    }
}