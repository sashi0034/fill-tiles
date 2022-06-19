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

    void TileMapMatElement::AddChip(const TilePropertyChip *chip)
    {
        m_ChipList.push_back(chip);
        // @todo: フラグ管理をlong longで行うクラスを作りたい

        m_IsWall = chip->IsWall;


        m_HasChip[static_cast<int>(chip->Kind)] = std::byte(1);
    }

    bool TileMapMatElement::RemoveChip(const TilePropertyChip *chip)
    {
        if (m_ChipList.size()==0) return false;
        auto iter = std::find(m_ChipList.begin(), m_ChipList.end(), chip);
        if (iter==m_ChipList.end()) return false;
        m_ChipList.erase(iter);
        m_HasChip[static_cast<int>(chip->Kind)] = std::byte(0);
        return true;
    }

    bool TileMapMatElement::RemoveChip(const ETileKind kind)
    {
        if (m_ChipList.size() == 0) return false;
        auto iter = std::find_if(m_ChipList.begin(), m_ChipList.end(),
                                 [kind](const TilePropertyChip *chip) { return chip->Kind == kind; });
        if (iter == m_ChipList.end()) return false;
        m_ChipList.erase(iter);
        m_HasChip[static_cast<int>(kind)] = std::byte(0);
        return true;
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

    void TileMapMatElement::OverwriteIsWall(bool isWall)
    {
        m_IsWall = isWall;
    }

}