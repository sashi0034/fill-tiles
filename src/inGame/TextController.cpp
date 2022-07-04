//
// Created by sashi0034 on 2022/07/04.
//

#include "TextController.h"
#include "ZIndex.h"

namespace inGame{

    TextController::TextController(IAppState *app, const std::string &text, const Vec2<double> &pos, FontResource *font)
    : m_Pos(pos), m_App(app), m_Font(font)
    {
        ChangeText(text);
    }

    std::vector<std::string> TextController::splitText(const std::string &text, const std::string &separator)
    {
        const auto separatorLength = separator.length();

        auto list = std::vector<std::string>();

        if (separatorLength == 0)
            list.push_back(text);
        else
        {
            auto offset = std::string::size_type(0);
            while (true)
            {
                const auto pos = text.find(separator, offset);
                if (pos == std::string::npos)
                {
                    list.push_back(text.substr(offset));
                    break;
                }
                list.push_back(text.substr(offset, pos - offset));
                offset = pos + separatorLength;
            }
        }
        return list;
    }

    void TextController::SetZIndex(int index)
    {
        for (auto&& line : m_TextList)
            ZIndexUi(&line->GetTexture()).SetIndex(index).ApplyZ();
    }

    void TextController::ChangeText(const std::string &text)
    {
        const auto lines = splitText(text, "<br>");
        const int oldListSize = m_TextList.size();

        for (int surplusRow = oldListSize-1; surplusRow>=int(lines.size()); --surplusRow)
        {
            m_TextList[surplusRow].reset();
            m_TextList.erase(m_TextList.begin() + surplusRow);
        }

        for (int row = 0; row<int(lines.size()); ++row)
        {
            if (row>=oldListSize) m_TextList.emplace_back(std::make_unique<TextureText>(m_Font));

            auto newLine =  &*(m_TextList[row]);
            newLine->ChangeText(lines[row]);

            const double deltaY = row * (newLine->GetSize().Y / double(m_App->GetPixelPerUnit()) + m_LineHeight);
            const Vec2<double> deltaPos = Vec2<double>{0, deltaY};;
            newLine->GetTexture().SetPosition(m_Pos + deltaPos);
        }
    }
}