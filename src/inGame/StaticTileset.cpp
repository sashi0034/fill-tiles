//
// Created by sashi0034 on 2022/06/16.
//

#include "StaticTileset.h"

namespace inGame
{
    StaticTileset::StaticTileset()
    : m_StaticTileset(createStaticTileset())
    {}

    std::unordered_map<ETileKind, TilePropertyChip> StaticTileset::createStaticTileset()
    {
        auto tileset = std::unordered_map<ETileKind, TilePropertyChip>();

        tileset[ETileKind::normal_plateau_cliff] = TilePropertyChip{ETileKind::normal_plateau_cliff, true, Vec2{0, 0}};

        return tileset;
    }

    TilePropertyChip *StaticTileset::GetOf(ETileKind kind) const
    {
        auto iter = m_StaticTileset.find(kind);
        assert(iter != m_StaticTileset.end());
        auto ret = &iter->second;
        return const_cast<TilePropertyChip*>(ret);
    }
}
