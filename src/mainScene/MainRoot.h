//
// Created by sashi0034 on 2022/05/23.
//

#ifndef FILL_TILES_MAINROOT_H
#define FILL_TILES_MAINROOT_H

#include "../gameEngine/gameEngine.h"
#include "../gameEngine/ChildBase.h"
#include "resource/Image.h"

namespace mainScene
{
    class MainRoot : public Singleton<MainRoot>
    {
    public:
        explicit MainRoot(IAppState* appState);
        ~MainRoot() override;
        const unique_ptr<resource::Image> ResImage;
        const IAppState* AppStatePtr;
    private:
        shared_ptr<Sprite> m_Spr{};
        ChildrenPool<ChildBase> m_ChildrenPool{};

        void createSelfSpr();
    };
}


#endif //FILL_TILES_MAINROOT_H
