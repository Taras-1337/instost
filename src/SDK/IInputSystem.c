#include "IInputSystem.h"

#include "common.h"

bool
is_buttom_down(void *self, enum buttoncode_t code)
{
    typedef bool (*vfn)(void *, enum buttoncode_t);
    vfn vfunc = (vfn) getvfunc(self, 14, 0);
    return vfunc(self, code);
}
