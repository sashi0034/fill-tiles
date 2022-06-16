//
// Created by sashi0034 on 2022/06/13.
//

#ifndef FILL_TILES_TILEMAPMATELEMENT_H
#define FILL_TILES_TILEMAPMATELEMENT_H

#include "../ActorBase.h"

namespace inGame::field
{
    enum class ETileKind
    {
        none,
        grass,
        normal_plateau,
        normal_plateau_cliff,
    };

    struct TilePropertyChip
    {
        ETileKind Kind = ETileKind::none;
        bool IsWall = false;
        Vec2<int> SrcPoint{};
    };

    class ITileMapMatElement
    {
    public:
        [[nodiscard]] virtual const std::vector<const TilePropertyChip *> &GetChipList() const = 0;
    };

    class TileMapMatElement : public ITileMapMatElement
    {
    public:
        TileMapMatElement();

        void AddChip(TilePropertyChip *chip);

        bool HasChip(ETileKind kind);

        [[nodiscard]] const std::vector<const TilePropertyChip *> &GetChipList() const override;

    private:
        std::vector<const TilePropertyChip *> m_ChipList;
        std::vector<std::byte> m_HasChip{};
        bool m_IsWall = false;
        bool m_IsStep[4] = {false, false, false, false};
    };
}


#endif //FILL_TILES_TILEMAPMATELEMENT_H
