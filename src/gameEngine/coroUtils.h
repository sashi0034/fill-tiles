//
// Created by sashi0034 on 2022/06/11.
//

#ifndef FILL_TILES_COROUTILS_H
#define FILL_TILES_COROUTILS_H

#include "CoroTask.h"
#include "WeakPtr.h"

namespace gameEngine::coroUtils
    {
        template<typename T>
        static CoroTask WaitForExpire(
                boost::coroutines2::coroutine<CoroTask>::push_type &yield,
                const WeakPtr <T> observer)
        {
            while (!observer.IsNull())
                yield();
        }
    }


#endif //FILL_TILES_COROUTILS_H
