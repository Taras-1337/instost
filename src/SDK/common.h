#pragma once

#include <dlfcn.h>

typedef void *(*instantiate_interface_fn)();
struct interface_reg {
    instantiate_interface_fn m_CreateFn;
    const char *m_pName;
    struct interface_reg *m_pNext;
};

const void *
getvfunc(const void *inst, size_t index, size_t offset);

void *
get_interface(const char *filename, const char *version, bool exact);
