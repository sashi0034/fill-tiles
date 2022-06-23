//
// Created by sashi0034 on 2022/06/17.
//

#ifndef FILL_TILES_CHARACTERVIEWMODEL_H
#define FILL_TILES_CHARACTERVIEWMODEL_H

#include "../gameEngine/gameEngine.h"
#include "ScrollManager.h"
#include "MatPos.h"
#include "FieldManager.h"

namespace inGame
{
    class CharacterViewModel
    {
    public:
        CharacterViewModel() = default;
        CharacterViewModel(ScrollManager* scrollManager, Graph* graph);
        void SetModelPos(const Vec2<double>& pos);
        void SetModelPos(const MatPos& pos);
        void SetCollider(IFieldManager *field, const Rect<int> &collider);
        SpriteTexture& GetModel();
        SpriteTexture& GetView();
        void SetZ();
    private:
        SpriteTexture m_ViewModel= SpriteTexture::Create();
        SpriteTexture m_View = SpriteTexture::Create();
        unique_ptr<TextureCollider> m_Collider;
    };
}


#endif //FILL_TILES_CHARACTERVIEWMODEL_H
