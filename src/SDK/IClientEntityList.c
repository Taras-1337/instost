#include "IClientEntityList.h"

#include "common.h"

void *
get_client_entity(void *self, int index)
{
    typedef void *(*vfn)(void *, int);
    vfn vfunc = (vfn) getvfunc(self, 3, 0);
    return vfunc(self, index);
}

void *
get_client_entity_from_handle(void *self, void *handle)
{
    typedef void *(*vfn)(void *, void *);
    vfn vfunc = (vfn) getvfunc(self, 4, 0);
    return vfunc(self, handle);
}
