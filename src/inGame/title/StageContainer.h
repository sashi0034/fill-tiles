//
// Created by sashi0034 on 2022/08/25.
//

#ifndef FILL_TILES_STAGECONTAINER_H
#define FILL_TILES_STAGECONTAINER_H

#include "./ScreenshotView.h"
#include "../pixel.h"


namespace inGame::title
{
    struct StageView
    {
        const int NumStage;
        const unique_ptr<ScreenshotView> Screenshot;
        StageView(int numStage, unique_ptr<ScreenshotView> &screenshot);
    };

    class StageContainer : public ActorBase
    {
    public:
        explicit StageContainer(MenuScene *sceneRef);
    private:
        MenuScene* const _sceneRef;
        std::vector<unique_ptr<StageView>> _viewList;
        SpriteTexture _emptySpr = SpriteTexture::Create();
        static constexpr int viewOffsetX = 880 / pixel::PixelPerUnit;

        void createNewView(int index, MenuScene *const sceneRef, const std::string &imageDir);
    };

} // inGame

#endif //FILL_TILES_STAGECONTAINER_H
