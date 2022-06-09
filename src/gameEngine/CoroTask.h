//
// Created by sashi0034 on 2022/05/24.
//

#ifndef FILL_TILES_COROTASK_H
#define FILL_TILES_COROTASK_H

#include "boost/coroutine2/coroutine.hpp"


namespace gameEngine
{
    class CoroTask
    {
    public:
        enum class Result{
            Success,
            Failed,
            Pending,
        };
        static CoroTask RespondSuccess();
        static CoroTask RespondFailed();
        static CoroTask RespondPending();

        explicit CoroTask(Result result);
        Result GetResult();
    private:
        Result m_Result;
    };

    using CoroTaskCall = boost::coroutines2::coroutine<CoroTask>::pull_type;
    using CoroTaskYield = boost::coroutines2::coroutine<CoroTask>::push_type;
}


#endif //FILL_TILES_COROTASK_H
