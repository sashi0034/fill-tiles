//
// Created by sashi0034 on 2022/07/02.
//

#ifndef FILL_TILES_FONT_H
#define FILL_TILES_FONT_H

#include "../../gameEngine/gameEngine.h"

namespace inGame::resource
{

    class Font
    {
    private:
        IAppState* m_AppStatePtr = nullptr;
    public:
        explicit Font(IAppState* appState);

        const unique_ptr<FontResource> PixelMPlus24Px =
                std::make_unique<FontResource>(
                        m_AppStatePtr, "assets/fonts/PixelMplus-20130602/PixelMplus12-Regular.ttf", 24, 2);


    };

} // inGame::resource

#endif //FILL_TILES_FONT_H
