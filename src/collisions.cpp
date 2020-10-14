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

bool c_circle_box(Circle circle, Rectangle box)
{
    float x = clamp(circle.center.x, box.position.x - box.halfwidth, box.position.x + box.halfwidth);
    float y = clamp(circle.center.y, box.position.y - box.halfheight, box.position.y + box.halfheight);
    Vector2 H(x, y);

    if (c_point_box(circle.center, box))
        return true;

    if (H.get_square_distance(circle.center) <= powf(circle.radius, 2))
        return true;

    return false;
}