//
// Created by sashi0034 on 2022/05/24.
//

#ifndef FILL_TILES_COROTASK_H
#define FILL_TILES_COROTASK_H


namespace gameEngine
{
    class CoroTask
    {
    public:
        enum class Result{
            SUCCESS,
            FAILED,
            PENDING,
        };
        static CoroTask RespondSuccess();
        static CoroTask RespondFailed();
        static CoroTask RespondPending();

        explicit CoroTask(Result result);
        Result GetResult();
    private:
        Result m_Result;
    };

}


#endif //FILL_TILES_COROTASK_H
