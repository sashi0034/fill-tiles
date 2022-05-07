//
// Created by sashi0034 on 2022/05/07.
//

#ifndef FILL_TILES_VEC_H
#define FILL_TILES_VEC_H


namespace gameEngine
{
    template<typename T> struct Vec2
    {
        T X;
        T Y;

        Vec2<T> operator+(Vec2<T> other)
        {
            return Vec2<T>{this->X + other.X, this->Y + other.Y};
        }

        Vec2<T> operator-(Vec2<T> other)
        {
            return Vec2<T>{this->X - other.X, this->Y - other.Y};
        }

        Vec2<T> operator*(int times)
        {
            return Vec2<T>{X * times, Y * times};
        }

        Vec2<T> operator*(double times)
        {
            return Vec2<T>{X * times, Y * times};
        }

        Vec2<T> operator/(int div)
        {
            return Vec2<T>{static_cast<T>(X / div), static_cast<T>(Y / div)};
        }

        Vec2<T> operator/(double div)
        {
            return Vec2<T>{static_cast<T>(X / div), static_cast<T>(Y / div)};
        }

        template<typename U>
        Vec2<U> EachTo()
        {
            return Vec2<U>{static_cast<U>(this->X), static_cast<U>(this->Y)};
        }
    };
}

#endif //FILL_TILES_VEC_H
