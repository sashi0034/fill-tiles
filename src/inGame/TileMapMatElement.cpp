//
// Created by sashi0034 on 2022/06/13.
//

#include "TileMapMatElement.h"
#include "magic_enum.h"

namespace inGame{

    void TileMapMatElement::AddChip(TilePropertyChip *chip)
    {
        m_ChipList.push_back(chip);
    }

    void TileMapMatElement::UpdateChipList()
    {
        int numKind = magic_enum::enum_count<ETileKind>();
        m_HasChip.resize(numKind, std::byte(0));

        for (auto &chip : m_ChipList)
            m_HasChip[static_cast<int>(chip->Kind)] = std::byte(1);
    }

    const std::vector<const TilePropertyChip *> &TileMapMatElement::GetChipList() const
    {
        return m_ChipList;
    }
}