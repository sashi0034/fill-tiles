//
// Created by sashi0034 on 2022/05/24.
//

#ifndef FILL_TILES_COROUTINEMANAGER_H
#define FILL_TILES_COROUTINEMANAGER_H

#include "WeakPtr.h"
#include "ChildrenPool.h"
#include "CoroTask.h"
#include "boost/coroutine2/coroutine.hpp"

namespace gameEngine
{
    class CoroutineElement
    {
        DEF_WEAK_CONTROLLER(CoroutineElement);
    public:
        explicit CoroutineElement(boost::coroutines2::coroutine<CoroTask>::pull_type *mTask);
        [[nodiscard]] boost::coroutines2::coroutine<CoroTask>::pull_type& GetTask() const;
    private:
        std::unique_ptr<boost::coroutines2::coroutine<CoroTask>::pull_type> m_Task;
    };

    class CoroutineManager
    {
    public:
        WeakPtr<CoroutineElement> Start(CoroutineElement *task);
        bool Destroy(CoroutineElement *task);
        void UpdateEach();
        ~CoroutineManager();
    private:
        ChildrenPool<CoroutineElement> m_Pool;
    };
}


#endif //FILL_TILES_COROUTINEMANAGER_H
