//
// Created by sashi0034 on 2022/06/13.
//

#ifndef FILL_TILES_TILEMAPMATELEMENT_H
#define FILL_TILES_TILEMAPMATELEMENT_H

#include "../ActorBase.h"
#include "../character/CharacterBase.h"
#include <bitset>
#include "../Angle.h"

namespace inGame::field
{
    enum class ETileKind
    {
        none,
        fines,
        low_basin,
        low_basin_shade_face,
        low_basin_shade_edge,
        normal_plain,
        normal_plain_cliff,
        normal_plain_shade_face,
        normal_plain_shade_edge,
        high_plateau,
        high_plateau_cliff,
        small_tree,
        big_tree,
        stairs,

        max,
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
        [[nodiscard]] virtual bool IsWall() const = 0;
        virtual bool GetCliffFlag(EAngle aspect) = 0;
        virtual void OverwriteIsWall(bool isWall) = 0;
    };

    class TileMapMatElement : public ITileMapMatElement
    {
    public:
        TileMapMatElement();

        void AddChip(const TilePropertyChip *chip);
        bool InsertChip(const TilePropertyChip *frontChip, const TilePropertyChip *newBackChip);
        bool ReplaceChip(const TilePropertyChip *oldChip, const TilePropertyChip *newChip);
        bool RemoveChip(const TilePropertyChip *chip);
        bool RemoveChip(ETileKind kind);

        bool HasChip(ETileKind kind);

        [[nodiscard]] const std::vector<const TilePropertyChip *> &GetChipList() const override;

        bool GetCliffFlag(EAngle aspect) override;

        [[nodiscard]] bool IsWall() const override;

        void SetCliffFlag(EAngle aspect, bool flag);

        void OverwriteIsWall(bool isWall) override;
    private:
        std::vector<const TilePropertyChip *> m_ChipList;

        std::bitset<int(ETileKind::max)> m_HasChip{};

        bool m_IsWall = false;

        std::bitset<4> m_CliffAspect{};
    };
}


#endif //FILL_TILES_TILEMAPMATELEMENT_H
