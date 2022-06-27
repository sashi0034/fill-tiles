//
// Created by sashi0034 on 2022/06/11.
//

#ifndef FILL_TILES_COROUTILS_H
#define FILL_TILES_COROUTILS_H

#include "CoroTask.h"
#include "WeakPtr.h"
#include "Time.h"

namespace gameEngine::coroUtils
{
    template<typename T>
    CoroTask WaitForExpire(CoroTaskYield &yield, const WeakPtr <T> observer)
    {
        while (!observer.IsNull())
            yield();
    }

    CoroTask WaitForTime(CoroTaskYield& yield, const Time &timeSystem, double waitSecond);

    CoroTask WaitForTrue(CoroTaskYield& yield, const std::function<bool()>& discriminant);
}


#endif //FILL_TILES_COROUTILS_H
