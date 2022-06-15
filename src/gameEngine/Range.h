//
// Created by sashi0034 on 2022/06/10.
//

#ifndef FILL_TILES_RANGE_H
#define FILL_TILES_RANGE_H

#include "cassert"

namespace gameEngine
{
    template <typename T>
    class Range
    {
    private:
        const T m_Min;
        const T m_Max;
    public:
        Range(T min, T max)
        : m_Min(min), m_Max(max)
        {
            assert(min<=max);
        }
        T GetDiff() const{
            return m_Max - m_Min;
        }
        bool IsBetween(T targetValue) const
        {
            return m_Min <= targetValue && targetValue <= m_Max;
        }
    };
}


#endif //FILL_TILES_RANGE_H
