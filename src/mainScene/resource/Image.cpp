//
// Created by sashi0034 on 2022/05/27.
//

#include "Image.h"

#include <memory>
#include "SDL_image.h"

namespace mainScene::resource
{
    Image::Image(IAppState *appState)
    : m_AppStatePtr(appState)
    {
        LOG_COUT << "Loaded Image Resources.";
    }

    unique_ptr<Graph> Image::loadPng(const std::string& fileName)
    {
        assert(m_AppStatePtr);

        std::string path = R"(./assets/images/)" + fileName + ".png";

        auto renderer = m_AppStatePtr->GetRenderer();
        auto surface = IMG_Load(path.c_str());

        assert(surface);

        unique_ptr<Graph> ret(new Graph(renderer, surface));
        return ret;
    }
}