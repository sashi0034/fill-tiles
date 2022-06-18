//
// Created by sashi0034 on 2022/06/17.
//

#ifndef FILL_TILES_CHARACTERVIEWMODEL_H
#define FILL_TILES_CHARACTERVIEWMODEL_H

#include "../gameEngine/gameEngine.h"
#include "ScrollManager.h"
#include "MatPos.h"

namespace inGame
{
    class CharacterViewModel
    {
    public:
        CharacterViewModel() = default;
        CharacterViewModel(ScrollManager* scrollManager, Graph* graph);
        void SetModelPos(const Vec2<double>& pos);
        void SetModelPos(const MatPos& pos);
        SpriteTexture * GetModel();
        SpriteTexture * GetView();
        shared_ptr<SpriteTexture>& GetModelShared();
        shared_ptr<SpriteTexture>& GetViewShared();
        void SetZ();
    private:
        shared_ptr<SpriteTexture> m_ViewModel{};
        shared_ptr<SpriteTexture> m_View{};
    };
}


#endif //FILL_TILES_CHARACTERVIEWMODEL_H
