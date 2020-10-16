#include "collisions.h"
#include <cmath>

bool c_circle_point(Circle circle,Vector2 point)
{
    return (point - circle.center).getSquareMagnitude() <= pow(circle.radius, 2);
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
    float x = clamp(circle.center.x, box.position.x -
                    box.halfwidth, box.position.x + box.halfwidth);
    float y = clamp(circle.center.y, box.position.y -
                    box.halfheight, box.position.y + box.halfheight);

    Vector2 height(x, y);

    if (c_point_box(circle.center, box))
        return true;

    if (height.getSquareDistance(circle.center) <= powf(circle.radius, 2))
        return true;

    return false;
}