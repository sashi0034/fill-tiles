//
// Created by sashi0034 on 2022/08/25.
//

#include "StageContainer.h"
#include "../GameRoot.h"

namespace inGame::title
{
    StageContainer::StageContainer(MenuScene *sceneRef) :
            ActorBase(sceneRef->GetChildren()),
            _sceneRef(sceneRef)
    {
        const std::string imageDir = "./assets/images/screenshots/";

        _emptySpr.SetPositionParent(sceneRef->RootRef->GetAnchor()->GetOf(ENineAnchorX::Center, ENineAnchorY::Middle));

        for (int i=1; i<=5; ++i)
        {
            createNewView(i, sceneRef, imageDir);
        }
    }

    void StageContainer::createNewView(int index, MenuScene *const sceneRef, const std::string &imageDir)
    {
        std::stringstream screenshotPath{};
        std::stringstream stageIndexText{};
        stageIndexText << index / 10 << index % 10;
        screenshotPath << imageDir << "field_" << stageIndexText.str() << ".png";

        _viewList.emplace_back(std::make_unique<StageView>(StageViewArgs{
                index,
                sceneRef,
                _emptySpr,
                Vec2<double>((index - 1) * viewOffsetX, 0),
                screenshotPath.str()
        }));
    }

} // inGame