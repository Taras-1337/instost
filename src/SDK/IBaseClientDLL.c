#include "IBaseClientDLL.h"

#include "common.h"

struct client_class *
get_all_classes(void *self)
{
    typedef struct client_class *(*vfn)(void *);
    vfn vfunc = (vfn) getvfunc(self, 8, 0);
    return vfunc(self);
}
