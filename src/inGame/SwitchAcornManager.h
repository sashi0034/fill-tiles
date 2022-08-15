//
// Created by sashi0034 on 2022/08/15.
//

#ifndef FILL_TILES_SWITCHACORNMANAGER_H
#define FILL_TILES_SWITCHACORNMANAGER_H

#include "rx.h"

namespace inGame
{
    namespace character{
        class SwitchButton;
        enum class ESwitchAcornKind;
    }

    class IMainScene;

    struct SwitchAcornEventArgs{
        character::SwitchButton* PushedButton;
        character::ESwitchAcornKind NextActiveKind;
    };

    class SwitchAcornManager
    {
    public:
        explicit SwitchAcornManager(IMainScene* mainScene);
        rx::observable<SwitchAcornEventArgs*> OnSwitch();
        rx::subscriber<SwitchAcornEventArgs*> SubscribeSwitch();
    private:
        IMainScene* const mainScene;
        rx::subject<SwitchAcornEventArgs*> m_OnSwitch{};
    };

} // inGame

#endif //FILL_TILES_SWITCHACORNMANAGER_H
