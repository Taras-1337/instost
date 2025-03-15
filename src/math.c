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
