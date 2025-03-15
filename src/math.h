#pragma once

typedef struct {
  float x;
  float y;
  float z;
} vector3;

typedef __attribute__((aligned(16))) struct {
  float x;
  float y;
  float z;
} vector3_aligned;

typedef struct {
  float x;
  float y;
  float z;
  float w;
} vector4;

typedef struct {
  float x;
  float y;
} vector2;

struct matrix3x4_t {
    float mat_val[3][4];
};

int
is_zero_pos(vector3 pos);

int
is_vector3_equals(vector3 vec1, vector3 vec2);

float
vector3_distance(vector3 vec1, vector3 vec2);

float
to_radian(float degree);
