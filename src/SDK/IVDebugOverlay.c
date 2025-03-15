#include "IVDebugOverlay.h"

#include "common.h"

bool
screen_position(void *self, const vector3 *in, vector3 *out)
{
    typedef bool (*vfn)(void *, const vector3 *, vector3 *);
    vfn vfunc = (vfn) getvfunc(self, 11, 0);
    return vfunc(self, in, out);
}
