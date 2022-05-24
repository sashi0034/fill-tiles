//
// Created by sashi0034 on 2022/05/24.
//

#ifndef FILL_TILES_COROUTINEMANAGER_H
#define FILL_TILES_COROUTINEMANAGER_H

#include "ChildrenPool.h"
#include "CoroTask.h"
#include "boost/coroutine2/coroutine.hpp"

namespace gameEngine
{
    class CoroutineManager
    {
    public:
        weak_ptr<boost::coroutines2::coroutine<CoroTask>::pull_type> Start(boost::coroutines2::coroutine<CoroTask>::pull_type* task);
        bool Destroy(boost::coroutines2::coroutine<CoroTask>::pull_type* task);
        void UpdateEach();
        ~CoroutineManager();
    private:
        ChildrenPool<boost::coroutines2::coroutine<CoroTask>::pull_type> m_Pool;
    };
}


#endif //FILL_TILES_COROUTINEMANAGER_H
