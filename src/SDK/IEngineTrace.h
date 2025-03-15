#pragma once

#include "../math.h"
#include <stdint.h>

enum hit_groups
{
    HITGROUP_GENERIC = 0,
    HITGROUP_HEAD,
    HITGROUP_CHEST,
    HITGROUP_STOMACH,
    HITGROUP_LEFTARM,
    HITGROUP_RIGHTARM,
    HITGROUP_LEFTLEG,
    HITGROUP_RIGHTLEG,
    HITGROUP_GEAR
};

struct ray_t
{
    vector3_aligned m_Start;
    vector3_aligned m_Delta;
    vector3_aligned m_StartOffset;
    vector3_aligned m_Extents;

    const struct matrix3x4_t *m_pWorldAxisTransform;

    bool m_IsRay;
    bool m_IsSwept;

};

struct trace_filter
{
    void *p_skip;
    void *p_skip2;
};

struct cplane_t
{
    vector3 normal;
    float dist;
    unsigned char type;
    unsigned char signbits;
    unsigned char pad[2];
};

struct csurface_t
{
    const char* name;
    short surfaceProps;
    unsigned short flags;
};

struct trace_t
{
    vector3 startpos;
    vector3 endpos;
    struct cplane_t plane;

    float fraction;

    int contents;
    unsigned int dispFlags;

    bool allsolid;
    bool startsolid;

    float fractionleftsolid;

    struct csurface_t surface;

    enum hit_groups hitgroup;

    void *m_pEntityHit;

    uint16_t physicsbone;
    uint16_t worldSurfaceIndex;

    int hitbox;
};

struct ray_t
rayt_init(vector3 start, vector3 end);

void
trace_ray(void *self, const struct ray_t *ray, unsigned int mask, struct trace_filter *filter, struct trace_t *trace);

bool
send_ray(void *local_player, void *player, vector3 start, vector3 end);
