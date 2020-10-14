#include <cmath>

#include "maths.h"

#include <iostream>

#pragma region constants
const Vector2 Vector2::zero (0, 0);
#pragma endregion

#pragma region constructors
Vector2::Vector2(float x, float y, bool isUnitary): x(x), y(y)
{
    if (isUnitary)
        normalize();
}
Vector2::Vector2(int x, int y, bool isUnitary): x(x), y(y)
{
    if (isUnitary)
        normalize();
}
Vector2::Vector2(GPVector2 vect, bool isUnitary) : x(vect.x), y(vect.y)
{
    if (isUnitary)
        normalize();
}
#pragma endregion

#pragma region vector functions
float Vector2::get_square_magnitude() const { return pow(x, 2) + pow(y, 2); }
float Vector2::get_magnitude() const { return sqrt(get_square_magnitude()); }
float Vector2::get_distance(const Vector2& other) const { return (*this - other).get_magnitude(); }
float Vector2::get_square_distance(const Vector2& other) const { return (*this - other).get_square_magnitude(); }
Vector2& Vector2::normalize()
{
    float magnitude = get_magnitude();
    if (magnitude == 0)
        *this = Vector2::zero;
    else
        *this = *this / magnitude;

    return *this;
}
#pragma endregion

#pragma region vector operators
Vector2 Vector2::operator+(const Vector2& other) const
{
    return {x + other.x, y + other.y};
}
Vector2 Vector2::operator-(const Vector2& other) const
{
    return {x - other.x, y - other.y};
}
Vector2 Vector2::operator*(float scale) const
{
    return Vector2{x * scale, y * scale};
}
Vector2 Vector2::operator/(float scale) const
{
    return Vector2{x / scale, y / scale};
}
Vector2& Vector2::operator+=(const Vector2& vect)
{
    *this = Vector2(x + vect.x, y + vect.y);
    return *this;
}
Vector2::operator GPVector2()
{
    return GPVector2{x, y};
}
#pragma endregion

#pragma region boolean operator
bool Vector2::operator==(const Vector2& vect) const
{
    return x == vect.x && y == vect.y;
}
bool Vector2::operator!=(const Vector2& vect) const
{
    return x != vect.x || y != vect.y;
}
#pragma endregion

#pragma region maths functions
float clamp(float value, float min, float max)
{
    return value < min ? min : value > max ? max : value;
}
#pragma endregion