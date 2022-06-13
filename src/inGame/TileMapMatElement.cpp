//
// Created by sashi0034 on 2022/06/13.
//

#include "TileMapMatElement.h"
namespace inGame{

    void TileMapMatElement::AddChip(TilePropertyChip *chip)
    {
        m_Chips.push_back(chip);
    }
}