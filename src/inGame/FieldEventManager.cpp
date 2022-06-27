//
// Created by sashi0034 on 2022/06/27.
//

#include "FieldEventManager.h"
#include "../gameEngine/gameEngine.h"

namespace inGame{

    void FieldEventManager::DecreaseEventCount()
    {
        --m_RunningEventCount;
    }

    void FieldEventManager::IncreaseEventCount()
    {
        ++m_RunningEventCount;
    }

    bool FieldEventManager::IsRunning() const
    {
        return m_RunningEventCount>0;
    }

    FieldEventInScope FieldEventManager::UseEvent()
    {
        return FieldEventInScope(this);
    }

    FieldEventInScope::FieldEventInScope(IFieldEventManagerCountable *manager)
    : m_Manager(manager)
    {}

    void FieldEventInScope::StartFromHere()
    {
        LOG_ASSERT(!m_IsStarted, "Event has already started.");
        m_IsStarted = true;
        m_Manager->IncreaseEventCount();
    }

    FieldEventInScope::~FieldEventInScope()
    {
        LOG_ASSERT(m_IsStarted, "Event destroyed without starting.");
        m_Manager->DecreaseEventCount();
    }
}
