//
// Created by sashi0034 on 2022/06/17.
//

#include "CharacterViewModel.h"
#include "ZIndex.h"

namespace inGame
{
    CharacterViewModel::CharacterViewModel(ScrollManager *scrollManager, Graph *graph)
    {
        scrollManager->RegisterSprite(m_ViewModel);

        m_View.SetGraph(graph);
        m_View.SetPositionParent(m_ViewModel);
    }

    void CharacterViewModel::SetModelPos(const Vec2<double> &pos)
    {
        m_ViewModel.SetPosition(pos);
    }

    void CharacterViewModel::SetModelPos(const MatPos &pos)
    {
        SetModelPos(pos.ToPixelPos());
    }

    SpriteTexture& CharacterViewModel::GetModel()
    {
        return m_ViewModel;
    }

    SpriteTexture& CharacterViewModel::GetView()
    {
        return m_View;
    }

    void CharacterViewModel::SetZ()
    {

    }

    void CharacterViewModel::SetCollider(IFieldManager *field, const Rect<int> &collider)
    {
        m_Collider = TextureCollider::Create(collider, m_ViewModel.GetWeakPtr());
        field->GetCharacterCollider()->AddCollider(m_Collider->GetWeakPtr());
    }
}