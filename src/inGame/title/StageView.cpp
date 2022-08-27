//
// Created by sashi0034 on 2022/08/27.
//

#include "StageView.h"

namespace inGame::title
{

    StageView::StageView(const StageViewArgs &args) :
        screenshot(createScreenshot(args))
    {}

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

} // inGame