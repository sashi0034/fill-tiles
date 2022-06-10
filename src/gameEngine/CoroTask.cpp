//
// Created by sashi0034 on 2022/05/24.
//

#include "CoroTask.h"
namespace gameEngine{

    CoroTask::CoroTask(CoroTask::Result result)
    {
        m_Result=result;
    }

    CoroTask::Result CoroTask::GetResult()
    {
        return m_Result;
    }

    CoroTask CoroTask::RespondSuccess()
    {
        return CoroTask(CoroTask::Result::Success);
    }

    CoroTask CoroTask::RespondFailed()
    {
        return CoroTask(CoroTask::Result::Failed);
    }

    CoroTask CoroTask::RespondPending()
    {
        return CoroTask(CoroTask::Result::Pending);
    }

    CoroTask CoroTask::RespondPending(boost::coroutines2::coroutine<CoroTask>::push_type &yield)
    {
        yield(CoroTask(CoroTask::Result::Pending));
        return CoroTask(CoroTask::Result::Pending);
    }
}