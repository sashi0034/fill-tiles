//
// Created by sashi0034 on 2022/05/24.
//

#ifndef FILL_TILES_COROTASK_H
#define FILL_TILES_COROTASK_H

#include <memory>
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
        static CoroTask RespondPending(boost::coroutines2::coroutine<CoroTask>::push_type& yield);

        explicit CoroTask(Result result);
        Result GetResult();
    private:
        Result m_Result;
    public:

        template <typename T> static CoroTask
        WaitForExpire(boost::coroutines2::coroutine<CoroTask>::push_type& yield, std::weak_ptr<T> observer)
        {
            while (!observer.expired()){
                yield(CoroTask::RespondPending());
            }

            return CoroTask(CoroTask::Result::Success);
        }

    };

    using CoroTaskCall = boost::coroutines2::coroutine<CoroTask>::pull_type;
    using CoroTaskYield = boost::coroutines2::coroutine<CoroTask>::push_type;
}


#endif //FILL_TILES_COROTASK_H
