#pragma once

#include "IVModelRender.h"

#include "../math.h"

struct studiohdr_t {
    int id;
    int version;
    int checksum;
    char name[64];
    int length;

    vector3 eyeposition;
    vector3 illumposition;
    vector3 hull_min;
    vector3 hull_max;
    vector3 view_bbmin;
    vector3 view_bbmax;

    int flags;
    int numbones;
    int boneindex;
};

struct mstudiobone_t {
    int sznameindex;

    int parent;
    int bonecontroller[6];

    vector3 pos;
    float quat[4];
    float rot[3];
    vector3 posscale;
    vector3 rotscale;

    struct matrix3x4_t poseToBone;
    float qAlignment[4];
    int flags;
};

struct studiohdr_t *
get_studio_model(void *self, const struct model_t *model);
