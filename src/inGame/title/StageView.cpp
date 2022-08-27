//
// Created by sashi0034 on 2022/08/27.
//

#include "StageView.h"
#include "../GameRoot.h"
#include "zIndex.h"

namespace inGame::title
{
    IAppState *StageViewArgs::GetApp() const
    {
        return SceneRef->RootRef->GetAppState();
    }

    StageView::StageView(const StageViewArgs &args) :
            _screenshot(createScreenshot(args))
    {
        initIndexSprites(args);
    }

    unique_ptr<ScreenshotView> StageView::createScreenshot(const StageViewArgs &args)
    {
        auto screenShot = std::make_unique<ScreenshotView>(
                args.SceneRef,
                args.CenterPos,
                args.ScreenshotPath,
                args.ParentSpr
        );
        return screenShot;
    }

    void StageView::initIndexSprites(const StageViewArgs &args)
    {
        initIndexSpr(args, _tenthsIndexSpr, args.NumStageIndex/10, -1);
        initIndexSpr(args, _onesIndexSpr, args.NumStageIndex%10, 1);
    }

    void StageView::initIndexSpr(const StageViewArgs &args, SpriteTexture &spr, int index, double modifierX) const
    {
        constexpr double space = 16;
        constexpr double centerY = -88;
        constexpr int cellSize = 32;

        spr.SetGraph(args.SceneRef->RootRef->RscImage->numbers_32x32.get());
        spr.SetSrcRect(Rect<int>{Vec2{cellSize * index, 0}, Vec2{cellSize, cellSize}});
        util::SetTextureByCenter(spr, args.CenterPos + Vec2<double>{modifierX * space, centerY});
        spr.SetPositionParent(args.ParentSpr);
    }

} // inGame