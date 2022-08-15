//
// Created by sashi0034 on 2022/08/15.
//

#include "SwitchAcornManager.h"

namespace inGame
{
    SwitchAcornManager::SwitchAcornManager(IMainScene *mainScene)
    : mainScene(mainScene)
    {}

    rx::observable<SwitchAcornEventArgs *> SwitchAcornManager::OnSwitch()
    {
        return m_OnSwitch.get_observable();
    }

    rx::subscriber<SwitchAcornEventArgs *> SwitchAcornManager::SubscribeSwitch()
    {
        return m_OnSwitch.get_subscriber();
    }
} // inGame