#include "IEngineTrace.h"

#include "common.h"

#include "../interfaces.h"
#include <stdio.h>
#include <stddef.h>

struct ray_t
rayt_init(vector3 start, vector3 end)
{
    struct ray_t res;

    res.m_Delta.x = end.x - start.x;
    res.m_Delta.y = end.y - start.y;
    res.m_Delta.z = end.z - start.z;
    res.m_IsSwept = true /*(m_Delta.LengthSqr() != 0)*/;
    res.m_Extents.x = res.m_Extents.y = res.m_Extents.z = 0.0f;
    res.pizdos = 0;
    res.m_pWorldAxisTransform = NULL;
    res.m_IsRay = true;
    res.m_StartOffset.x = res.m_StartOffset.y = res.m_StartOffset.z = 0.0f;
    res.m_Start.x = start.x;
    res.m_Start.y = start.y;
    res.m_Start.z = start.z;

    return res;
}

bool
ShouldHitEntity(struct trace_filter *self, void *pEntity, int contentsMask)
{
    return pEntity != self->p_skip && pEntity != self->p_skip2;
}

int
GetTraceType(void)
{
    return 0;
}

void
trace_ray(void *self, struct ray_t *ray, unsigned int mask, struct trace_filter *filter, struct trace_t *trace)
{
    typedef void (*vfn)(void *, struct ray_t *, unsigned int, struct trace_filter *, struct trace_t *);
    vfn vfunc = (vfn) getvfunc(self, 5, 0);
    vfunc(self, ray, mask, filter, trace);
}

bool
send_ray(void *local_player, void *player, vector3 start, vector3 end)
{
    struct ray_t ray = rayt_init(start, end);

    static void *vtable[2] =  {
        ShouldHitEntity,
        GetTraceType,
    };

    struct trace_filter tf;
    tf.vtable = vtable;
    tf.p_skip = local_player;
    tf.p_skip2 = player;

    struct trace_t tr;
    trace_ray(trace, &ray, 1|0x40000000, &tf, &tr);

    // printf("TS: %d\n", offsetof(vector3_aligned, y));
    // printf("FR: %f\n", tr.fraction);
    // fflush(stdout);

    return tr.fraction > 0.998;
}
