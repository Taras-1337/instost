#include "interfaces.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define __USE_GNU
#include <link.h>
#include <dlfcn.h>
#include <stdint.h>

#include "SDK/common.h"

#include "c-vector/vec.h"

void *engine = nullptr;
void *engine_vgui = nullptr;
void *surface = nullptr;
void *client = nullptr;
void *entity_list = nullptr;
void *model_info = nullptr;
void *debug_overlay = nullptr;
void *trace = nullptr;
void *client_mode = nullptr;
void *input_system = nullptr;
se_msg_fn _msgfn;

struct dlinfo_t *vec_libraries = nullptr;

bool
bp_compare(const unsigned char *p_data, const unsigned char *b_mask, const char *sz_mask);

uintptr_t
find_pattern(uintptr_t dw_address, uintptr_t dw_len, unsigned char *b_mask, const char *sz_mask);

bool
get_lib_info(const char *library, uintptr_t *address, size_t *size);

uintptr_t
get_absolute_address(uintptr_t instruction_ptr, int offset, int size);

uintptr_t
find_pattern_in_module(const char *module_name, unsigned char *b_mask, const char *sz_mask);

void
se_msg(const char *msg, ...) {
    char buffer[256];
    va_list list;

    if (msg == nullptr) {
        return;
    }

    va_start(list, msg);
    vsprintf(buffer, msg, list);
    va_end(list);

    _msgfn(buffer, list);
}

void
find_interfaces(void)
{
    void *libtier0 = dlopen("./bin/libtier0.so", 1);
    _msgfn = (se_msg_fn) dlsym(libtier0, "Msg");

    engine = get_interface("./bin/engine.so", "VEngineClient", false);
    engine_vgui = get_interface("./bin/engine.so", "VEngineVGui", false);
    surface = get_interface("./bin/vguimatsurface.so", "VGUI_Surface", false);
    client = get_interface("./insurgency/bin/client.so", "VClient", false);
    entity_list = get_interface("./insurgency/bin/client.so", "VClientEntityList", false);
    model_info = get_interface("./bin/engine.so", "VModelInfoClient", false);
    debug_overlay = get_interface("./bin/engine.so", "VDebugOverlay", false);
    trace = get_interface("./bin/engine.so", "EngineTraceClient", false);
    input_system = get_interface("./bin/inputsystem.so", "InputSystemVersion", false);
}

void
find_client_mode(void)
{
    vec_libraries = vector_create();

    uintptr_t func_ptr = find_pattern_in_module("bin/client.so", (unsigned char *) ICLIENTMODE_SIG, ICLIENTMODE_MASK) + strlen(ICLIENTMODE_MASK);

    typedef void *(*get_client_mode_fn)(void);
    get_client_mode_fn get_client_mode = (void *) get_absolute_address(func_ptr, 0, 4);
    client_mode = get_client_mode();

    // TODO: FREE MEM SOMEWHERE free(vec_libraries);
}

uintptr_t
find_pattern_in_module(const char *module_name, unsigned char *b_mask, const char *sz_mask)
{
    uintptr_t base_addr;
    size_t mem_size;

    if (!get_lib_info(module_name, &base_addr, &mem_size)) {
        return 0;
    }

    return find_pattern(base_addr, base_addr + mem_size, b_mask, sz_mask);
}

int
callback_dl_phdr(struct dl_phdr_info *info, size_t, void *)
{
    struct dlinfo_t library_info = {};

    library_info.library = info->dlpi_name;
    library_info.address = info->dlpi_addr + info->dlpi_phdr[0].p_vaddr;
    library_info.size = info->dlpi_phdr[0].p_memsz;

    vector_add(&vec_libraries, library_info);

    return 0;
}

bool
get_lib_info(const char *library, uintptr_t *address, size_t *size)
{
    if (vector_size(vec_libraries) == 0) {
        dl_iterate_phdr(callback_dl_phdr, nullptr);
    }

    for (size_t i = 0; i < vector_size(vec_libraries); ++i) {
        if (!strcasestr(vec_libraries[i].library, library)) {
            continue;
        }

        if (address) {
            *address = vec_libraries[i].address;
        }

        if (size) {
            *size = vec_libraries[i].size;
        }

        return true;
    }

    return false;
}

uintptr_t
get_absolute_address(uintptr_t instruction_ptr, int offset, int size)
{
    return instruction_ptr + *((uint32_t *)(instruction_ptr + offset)) + size;
}

uintptr_t
find_pattern(uintptr_t dw_address, uintptr_t dw_len, unsigned char *b_mask, const char *sz_mask)
{
    for (uintptr_t i = 0; i < dw_len; i++) {
        if (bp_compare((unsigned char *)(dw_address + i), b_mask, sz_mask)) {
            return (uintptr_t)(dw_address + i);
        }
    }

    return 0;
}

bool
bp_compare(const unsigned char *p_data, const unsigned char *b_mask, const char *sz_mask)
{
    for (; *sz_mask; ++sz_mask, ++p_data, ++b_mask) {
        if (*sz_mask == 'x' && *p_data != *b_mask) {
            return false;
        }
    }

    return (*sz_mask) == 0;
}
