#pragma once

#include <stdint.h>
#include <wchar.h>

#include "math.h"

#define PAINT_IDX 15
#define CREATE_MOVE_IDX 25

#define WBUF_SIZE 128

typedef struct {
    uintptr_t  *vmt;
    uintptr_t **interface;
    uintptr_t  *original_vmt;
} vmt_hook;

struct CUserCmd {
    void          *vtable; // virtual ~CUserCmd() {};
    int            command_number;
    int            tick_count;
    vector3        viewangles;
    vector3        aimdirection;
    float          forwardmove;
    float          sidemove;
    float          upmove;
    int            buttons;
    unsigned char  impulse;
    int            weaponselect;
    int            weaponsubtype;
    int            random_seed;
    short          mousedx;
    short          mousedy;
    bool           hasbeenpredicted;
    vector3        headangles;
    vector3        headoffset;
    vector3        unknown;
    vector3        muzzleangle;
    vector3        muzzlepos;
};

extern wchar_t *wbuffer;
extern vmt_hook engine_vgui_vmt;
extern vmt_hook client_mode_vmt;

void
init_hooks();

void
cleanup_hooks();
