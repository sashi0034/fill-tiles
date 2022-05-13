//
// Created by sashi0034 on 2022/05/07.
//

#ifndef FILL_TILES_RECT_H
#define FILL_TILES_RECT_H

#include <memory>
using std::unique_ptr;

namespace gameEngine
{
    template<typename T> struct Rect
    {
        T X;
        T Y;
        T Width;
        T Height;

        Vec2<T>& GetStartingPoint()
        {
            return Vec2{X, Y};
        }
        Vec2<T>& GetSize()
        {
            return Vec2{Width, Height};
        }
    };
}


#endif //FILL_TILES_RECT_H
