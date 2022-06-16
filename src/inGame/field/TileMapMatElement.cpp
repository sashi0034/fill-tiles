//
// Created by sashi0034 on 2022/06/13.
//

#include "TileMapMatElement.h"
#include "magic_enum.h"

namespace inGame::field{

    TileMapMatElement::TileMapMatElement()
    {
        int numKind = magic_enum::enum_count<ETileKind>();
        m_HasChip.resize(numKind, std::byte(0));
    }

    void TileMapMatElement::AddChip(TilePropertyChip *chip)
    {
        m_ChipList.push_back(chip);
        // @todo: フラグ管理をlong longで行うクラスを作りたい

        if (chip->Kind==ETileKind::normal_plateau_cliff) m_IsWall = true;


        m_HasChip[static_cast<int>(chip->Kind)] = std::byte(1);
    }

    const std::vector<const TilePropertyChip *> &TileMapMatElement::GetChipList() const
    {
        return m_ChipList;
    }

    bool TileMapMatElement::HasChip(ETileKind kind)
    {
        return m_HasChip[static_cast<int>(kind)]!=std::byte{0};
    }

    bool TileMapMatElement::IsWall() const
    {
        return m_IsWall;
    }

}