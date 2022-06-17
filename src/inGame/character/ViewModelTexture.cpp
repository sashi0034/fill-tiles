//
// Created by sashi0034 on 2022/06/17.
//

#include "ViewModelTexture.h"
namespace inGame::character
{
    ViewModelTexture::ViewModelTexture(ScrollManager *scrollManager, Graph *graph)
    {
        m_ViewModel = SpriteTexture::Create(nullptr);
        scrollManager->RegisterSprite(m_ViewModel);

        m_View = SpriteTexture::Create(graph);
        m_View->SetPositionParent(m_ViewModel);
    }

    void ViewModelTexture::SetViewModelPos(const Vec2<double> &pos)
    {
        m_ViewModel->SetPosition(pos);
    }

    void ViewModelTexture::SetViewModelPos(const MatPos &pos)
    {
        SetViewModelPos(pos.ToPixelPos());
    }

    SpriteTexture * ViewModelTexture::GetViewModel()
    {
        return m_ViewModel.get();
    }

    SpriteTexture* ViewModelTexture::GetView()
    {
        return m_View.get();
    }
}