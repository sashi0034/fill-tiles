//
// Created by sashi0034 on 2022/08/27.
//

#ifndef FILL_TILES_STAGEVIEW_H
#define FILL_TILES_STAGEVIEW_H

#include "ScreenshotView.h"

namespace inGame::title
{
    struct StageViewArgs
    {
        MenuScene* const SceneRef;
        SpriteTexture& ParentSpr;
        const Vec2<double> CenterPos;
        const std::string ScreenshotPath;
    };

    class StageView
    {
    public:
        explicit StageView(const StageViewArgs& args);
    private:
        static unique_ptr<ScreenshotView> createScreenshot(const StageViewArgs &args);

        const unique_ptr<ScreenshotView> screenshot;
    };

} // inGame

#endif //FILL_TILES_STAGEVIEW_H
