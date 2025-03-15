#pragma once

#include <stdint.h>
#include <wchar.h>

#define PAINT_IDX 15

#define WBUF_SIZE 128

typedef struct {
    uintptr_t  *vmt;
    uintptr_t **interface;
    uintptr_t  *original_vmt;
} vmt_hook;

extern wchar_t *wbuffer;
extern vmt_hook engine_vgui_vmt;

void
init_hooks();

void
cleanup_hooks();
