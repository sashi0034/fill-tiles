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
    private:
        shared_ptr<Sprite> m_Sprite{};
        ChildrenPool<ChildBase> m_Children{};
    };
}


#endif //FILL_TILES_MAINROOT_H
