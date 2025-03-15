#include "common.h"
#include <stddef.h>
#include <string.h>
#include <dlfcn.h>

void **
getvtable(void *inst, size_t offset)
{
    return *(void ***)((size_t)inst + offset);
}

const void **
getvtable_const(const void *inst, size_t offset)
{
    return *(const void ***)((size_t)inst + offset);
}

const void *
getvfunc(const void *inst, size_t index, size_t offset)
{
    return getvtable_const(inst, offset)[index];
}

void *
get_interface(const char *filename, const char *version, bool exact)
{
    void* library = dlopen(filename, RTLD_NOLOAD | RTLD_NOW);
    if (!library) {
        return nullptr;
    }

    void *interfaces_sym = dlsym(library, "s_pInterfaceRegs");
    dlclose(library);
    if (!interfaces_sym) {
        return nullptr;
    }

    struct interface_reg *interfaces = *((struct interface_reg **) interfaces_sym);
    for (struct interface_reg *cur_interface = interfaces; cur_interface; cur_interface = cur_interface->m_pNext) {
        if (exact) {
            if (strcmp(cur_interface->m_pName, version) == 0) {
                return (void *)(cur_interface->m_CreateFn());
            }
        } else {
            if (strstr(cur_interface->m_pName, version) && strlen(cur_interface->m_pName) - 3 == strlen(version)) {
                return (void *)(cur_interface->m_CreateFn());
            }
        }
    }

    return nullptr;
}
