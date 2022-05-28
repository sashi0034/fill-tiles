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
        return CoroTask(CoroTask::Result::SUCCESS);
    }

    CoroTask CoroTask::RespondFailed()
    {
        return CoroTask(CoroTask::Result::FAILED);
    }

    CoroTask CoroTask::RespondPending()
    {
        return CoroTask(CoroTask::Result::PENDING);
    }
}