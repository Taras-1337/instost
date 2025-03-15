#include "IVModelInfo.h"

#include "common.h"

struct studiohdr_t *
get_studio_model(void *self, const struct model_t *model)
{
    typedef struct studiohdr_t *(*vfn)(void *, const struct model_t *);
    vfn vfunc = (vfn) getvfunc(self, 31, 0);
    return vfunc(self, model);
}
