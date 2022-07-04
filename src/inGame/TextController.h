//
// Created by sashi0034 on 2022/07/04.
//

#ifndef FILL_TILES_TEXTCONTROLLER_H
#define FILL_TILES_TEXTCONTROLLER_H

#include "../gameEngine/gameEngine.h"

namespace inGame
{
    class TextController
    {
    public:
        explicit TextController(IAppState *app, const std::string &text, const Vec2<double> &pos, FontResource *font);
        void SetZIndex(int index);
        void ChangeText(const std::string &text);
    private:
        Vec2<double> m_Pos;
        std::vector<unique_ptr<TextureText>> m_TextList{};
        IAppState* m_App;
        FontResource* m_Font;

        int m_LineHeight = 4;

        static std::vector<std::string> splitText(const std::string &text, const std::string &separator) ;
    };
}


#endif //FILL_TILES_TEXTCONTROLLER_H
