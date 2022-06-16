//
// Created by sashi0034 on 2022/06/16.
//

#ifndef FILL_TILES_MATPOS_H
#define FILL_TILES_MATPOS_H

#include "../gameEngine/gameEngine.h"

namespace inGame
{
    class MatPos
    {
    public:
        explicit MatPos(const Vec2<int>& pos);
        MatPos(int x, int y);
        [[nodiscard]] Vec2<int> GetVec() const;

        MatPos operator+(const MatPos& other) const;
        MatPos operator-(const MatPos& other) const;
        MatPos operator*(int times) const;

        std::string ToString() const;
    private:
        const Vec2<int> m_Pos;

    };
}


#endif //FILL_TILES_MATPOS_H
