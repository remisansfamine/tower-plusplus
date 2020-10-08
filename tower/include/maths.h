#pragma once

#include <gp/gp.h>

class Vector2
{
    public:
        float x = 0, y = 0;

        Vector2() = default;
        Vector2(float x, float y, bool isUnitary = false);
        Vector2(int x, int y, bool isUnitary = false);
        Vector2(GPVector2 vect, bool isUnitary = false);

        float get_square_magnitude() const;
        float get_magnitude() const;
        float get_distance(const Vector2& other) const;
        Vector2& normalize();

        Vector2 operator+(const Vector2&) const;
        Vector2& Vector2::operator+=(const Vector2&);
        Vector2 operator-(const Vector2&) const;
        Vector2 operator*(float) const;
        Vector2 operator/(float scale) const;

        operator GPVector2();

        static const Vector2 zero;
};

class Circle
{
    public:
        float radius;
        Vector2 center;
};

class Rectangle
{
    public:
        Vector2 position;
        float halfwidth;
        float halfheight;
};