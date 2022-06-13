//
// Created by sashi0034 on 2022/06/13.
//

#ifndef FILL_TILES_TILEMAPMATELEMENT_H
#define FILL_TILES_TILEMAPMATELEMENT_H

#include "ActorBase.h"

namespace inGame
{
    enum class ETileName{
        none,
        grass,
        normal_plateau,
    };

    struct TilePropertyChip{
        ETileName Name = ETileName::none;
        bool IsWall = false;
        Vec2<int> SrcPoint{};
    };

    class TileMapMatElement{
    public:
        void AddChip(TilePropertyChip *chip);
        void UpdateElement();
    private:
        std::vector<TilePropertyChip*> m_Chips;
        std::vector<std::byte> m_HasChip{};
        bool m_IsWall = false;
        bool m_IsStep[4] = {false, false, false, false};
    };
}


#endif //FILL_TILES_TILEMAPMATELEMENT_H
