//
// Created by sashi0034 on 2022/06/17.
//

#include "CharacterViewModel.h"
#include "ZIndex.h"

namespace inGame
{
    CharacterViewModel::CharacterViewModel(ScrollManager *scrollManager, Graph *graph)
    {
        m_ViewModel = SpriteTexture::Create(nullptr);
        scrollManager->RegisterSprite(m_ViewModel);

        m_View = SpriteTexture::Create(graph);
        m_View->SetPositionParent(m_ViewModel);
    }

    void CharacterViewModel::SetModelPos(const Vec2<double> &pos)
    {
        m_ViewModel->SetPosition(pos);
    }

    void CharacterViewModel::SetModelPos(const MatPos &pos)
    {
        SetModelPos(pos.ToPixelPos());
    }

    SpriteTexture * CharacterViewModel::GetModel()
    {
        return m_ViewModel.get();
    }

    SpriteTexture* CharacterViewModel::GetView()
    {
        return m_View.get();
    }

    void CharacterViewModel::SetZ()
    {

    }

    shared_ptr<SpriteTexture> &CharacterViewModel::GetModelShared()
    {
        return m_ViewModel;
    }

    shared_ptr<SpriteTexture> &CharacterViewModel::GetViewShared()
    {
        return m_View;
    }

    void CharacterViewModel::SetCollider(IFieldManager *field, const Rect<int> &collider)
    {
        m_Collider = TextureCollider::Create(collider, m_ViewModel.get());
        field->GetCharacterCollider()->AddCollider(m_Collider);
    }
}