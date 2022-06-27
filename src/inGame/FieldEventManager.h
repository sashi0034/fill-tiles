//
// Created by sashi0034 on 2022/06/27.
//

#ifndef FILL_TILES_FIELDEVENTMANAGER_H
#define FILL_TILES_FIELDEVENTMANAGER_H


namespace inGame
{
    class FieldEventManager;

    class IFieldEventManagerCountable
    {
    public:
        virtual void IncreaseEventCount() = 0;
        virtual void DecreaseEventCount() = 0;
    };

    class FieldEventInScope
    {
    public:
        explicit FieldEventInScope(IFieldEventManagerCountable* manager);
        ~FieldEventInScope();
        void StartFromHere();
        IFieldEventManagerCountable* m_Manager;
        bool m_IsStarted = false;
    };

    class FieldEventManager final : private IFieldEventManagerCountable
    {
    public:
        [[nodiscard]] FieldEventInScope UseEvent();
        [[nodiscard]] bool IsRunning() const;
    private:
        void DecreaseEventCount() override;
        void IncreaseEventCount() override;

        int m_RunningEventCount = 0;
    };
}


#endif //FILL_TILES_FIELDEVENTMANAGER_H
