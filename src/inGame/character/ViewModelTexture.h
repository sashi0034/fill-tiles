//
// Created by sashi0034 on 2022/06/17.
//

#ifndef FILL_TILES_VIEWMODELTEXTURE_H
#define FILL_TILES_VIEWMODELTEXTURE_H

#include "../../gameEngine/gameEngine.h"
#include "../ScrollManager.h"
#include "../MatPos.h"

namespace inGame::character
{
    class ViewModelTexture
    {
    public:
        ViewModelTexture(ScrollManager* scrollManager, Graph* graph);
        void SetViewModelPos(const Vec2<double>& pos);
        void SetViewModelPos(const MatPos& pos);
        SpriteTexture * GetViewModel();
        SpriteTexture * GetView();
    private:
        shared_ptr<SpriteTexture> m_ViewModel{};
        shared_ptr<SpriteTexture> m_View{};
    };
}


#endif //FILL_TILES_VIEWMODELTEXTURE_H
