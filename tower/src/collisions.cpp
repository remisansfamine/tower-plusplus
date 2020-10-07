#include "collisions.h"
#include <cmath>

#include <iostream>

bool c_circle_point(Circle circle,Vector2 point)
{
    return (point - circle.center).get_square_magnitude() <= pow(circle.radius, 2);
}

bool c_point_box(Vector2 point, Rectangle box)
{
    return point.x >= box.position.x - box.halfwidth
        && point.x <= box.position.x + box.halfwidth
        && point.y >= box.position.y - box.halfheight
        && point.y <= box.position.y + box.halfheight;
}