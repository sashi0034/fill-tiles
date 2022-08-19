//
// Created by sashi0034 on 2022/08/19.
//

#include "WarpTile.h"
#include "../ZIndex.h"

namespace inGame::character
{
    // TODO: 時間があったらキノコくんがぐるぐるするアニメーションを作りたいかも

    WarpTile::WarpTile(IMainScene *mainScene, const MatPos &matPos)
            : CharacterBase(mainScene->GetFieldManager())
            , m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->RscImage->warp_tile_16x16.get())
    {
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, cellMatSize * FieldManager::PixelPerMat});

        m_View.SetModelPos(matPos);

        ZIndexBackGround(&m_View.GetView()).GoFront(1).ApplyZ();
    }
} // inGame