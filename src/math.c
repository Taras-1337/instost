#include "math.h"

#include <math.h>

int
is_zero_pos(vector3 pos)
{
    return pos.x == 0.0 && pos.y == 0.0 && pos.z == 0.0;
}

int
is_vector3_equals(vector3 vec1, vector3 vec2)
{
    return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z;
}

float
vector3_distance(vector3 vec1, vector3 vec2)
{
    return sqrt(pow(vec1.x - vec2.x, 2) + pow(vec1.y - vec2.y, 2) + pow(vec1.z - vec2.z, 2));
}

float
to_radian(float degree)
{
    return degree * (M_PI / 180);
}

void
vector_angles(const vector3 *forward, vector3 *angles)
{
    if (forward->y == 0.0f && forward->x == 0.0f)
    {
        angles->x = (forward->z > 0.0f) ? 270.0f : 90.0f; // Pitch (up/down)
        angles->y = 0.0f;  //yaw left/right
    }
    else
    {
        angles->x = atan2(-forward->z, sqrt(forward->x * forward->x + forward->y * forward->y)) * -180 / M_PI;
        angles->y = atan2(forward->y, forward->x) * 180 / M_PI;

        if (angles->y > 90) {
            angles->y -= 180;
        } else if (angles->y < 90) {
            angles->y += 180;
        } else if (angles->y == 90) {
            angles->y = 0;
        }
    }

    angles->z = 0.0f;
}

vector3
calc_angle(vector3 src, vector3 dst)
{
    vector3 angles;
    vector3 delta;
    delta.x = src.x - dst.x;
    delta.y = src.y - dst.y;
    delta.z = src.z - dst.z;

    vector_angles(&delta, &angles);

    // TODO: NEED TO DELTA.NORMALIZE?????7??77??7??77??
    return angles;
}

float
get_fov(const vector3 *viewAngle, const vector3 *aimAngle)
{
    vector3 delta;
    delta.x = aimAngle->x - viewAngle->x;
    delta.y = aimAngle->y - viewAngle->y;
    delta.z = aimAngle->z - viewAngle->z;
    normalize_angles(&delta);

    return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
}

vector3
delta_angles(const vector3 *start, const vector3 *end)
{
    vector3 delta;
    delta.x = end->x - start->x;
    delta.y = end->y - start->y;
    delta.z = end->z - start->z;

    normalize_angles(&delta);
    clamp_angles(&delta);

    return delta;
}

void
normalize_angles(vector3 *angle)
{
    while (angle->x > 89.0f) {
        angle->x -= 180.f;
    }

    while (angle->x < -89.0f) {
        angle->x += 180.f;
    }

    while (angle->y > 180.f) {
        angle->y -= 360.f;
    }

    while (angle->y < -180.f) {
        angle->y += 360.f;
    }
}

void
clamp_angles(vector3 *angle)
{
    if (angle->y > 180.0f) {
        angle->y = 180.0f;
    } else if (angle->y < -180.0f) {
        angle->y = -180.0f;
    }

    if (angle->x > 89.0f) {
        angle->x = 89.0f;
    } else if (angle->x < -89.0f) {
        angle->x = -89.0f;
    }

    angle->z = 0;
}
