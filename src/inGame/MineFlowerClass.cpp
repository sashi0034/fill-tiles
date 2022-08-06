//
// Created by sashi0034 on 2022/08/06.
//

#include "MineFlowerClass.h"

namespace inGame
{
    MineFlowerClass::MineFlowerClass(field::ETileKind mineFlowerTile, field::ETileKind blockTile, int classLevel)
            : MineFlowerTile(mineFlowerTile), BlockTile(blockTile), m_ClassLevel{classLevel}
    {}

    void MineFlowerClass::IncreaseMineFlower()
    {
        ++m_MineFlowerCount;
    }

    void MineFlowerClass::DecreaseMineFlower()
    {
        --m_MineFlowerCount;
    }

    bool MineFlowerClass::HasMineFlower()
    {
        return m_MineFlowerCount>0;
    }

    int MineFlowerClass::GetClassLevel() const
    {
        return m_ClassLevel;
    }

    int MineFlowerClass::GetMaxMineFlowerCount() const
    {
        return m_MaxMineFlowerCount;
    }

    void MineFlowerClass::FixMaxMineFlowerCount()
    {
        assert(m_MaxMineFlowerCount==0);
        m_MaxMineFlowerCount = m_MineFlowerCount;
    }

    int MineFlowerClass::GetMineFlowerCount() const
    {
        return m_MineFlowerCount;
    }

    void MineFlowerClass::SetRespawnMatPos(const MatPos &pos)
    {
        assert(m_RespawnMatPos== nullptr);

        m_RespawnMatPos = std::make_unique<MatPos>(pos.GetVec());
    }

    MatPos MineFlowerClass::GetRespawnMatPos() const
    {
        return MatPos(m_RespawnMatPos->GetVec());
    }

} // inGame