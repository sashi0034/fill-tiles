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

        Rect(T x, T y, T width, T height)
        {
            X = x;
            Y = y;
            Width = width;
            Height = height;
        }

        Rect(const Vec2<T>& startingPoint, const Vec2<T>& size)
        {
            X = startingPoint.X;
            Y = startingPoint.Y;
            Width = size.X;
            Height = size.Y;
        }

        Vec2<T> GetStartingPoint() const
        {
            return Vec2<T>{X, Y};
        }

        Vec2<T> GetSize() const
        {
            return Vec2<T>{Width, Height};
        }
    };
}


#endif //FILL_TILES_RECT_H
