#include "IEngineClient.h"

#include <stdbool.h>

#include "../math.h"

#include "common.h"

void
get_screen_size(void *self, int *width, int *height) {
    typedef void (*vfn)(void *, int *, int *);
    vfn vfunc = (vfn) getvfunc(self, 5, 0);
    vfunc(self, width, height);
}

bool
get_player_info(void *self, int index, struct player_info_s *info)
{
    typedef bool (*vfn)(void *, int, struct player_info_s *);
    vfn vfunc = (vfn) getvfunc(self, 8, 0);
    return vfunc(self, index, info);
}

int
get_local_player(void *self) {
    typedef int (*vfn)(void *);
    vfn vfunc = (vfn) getvfunc(self, 12, 0);
    return vfunc(self);
}

void
get_view_angles(void *self, vector3 *angles)
{
    typedef void (*vfn)(void *, vector3 *);
    vfn vfunc = (vfn) getvfunc(self, 18, 0);
    vfunc(self, angles);
}

int
get_max_clients(void *self) {
    typedef int (*vfn)(void *);
    vfn vfunc = (vfn) getvfunc(self, 22, 0);
    return vfunc(self);
}

bool
is_ingame(void *self) {
    typedef bool (*vfn)(void *);
    vfn vfunc = (vfn) getvfunc(self, 28, 0);
    return vfunc(self);
}

bool
is_taking_screenshot(void *self) {
    typedef bool (*vfn)(void *);
    vfn vfunc = (vfn) getvfunc(self, 91, 0);
    return vfunc(self);
}
