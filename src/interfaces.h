#pragma once

#include <stdio.h>

#include "SDK/IEngineClient.h"

typedef void(*se_msg_fn)(const char *msg, va_list);

struct dlinfo_t {
    const char *library;
    uintptr_t   address;
    size_t      size;
};

extern struct dlinfo_t *vec_libraries;

extern void *engine;
extern void *engine_vgui;
extern void *surface;
extern void *client;
extern void *entity_list;
extern void *model_info;
extern void *debug_overlay;
extern void *trace;
extern void *client_mode;
extern void *input_system;

#define ICLIENTMODE_MASK "xxxxxxxxxx????xx????xxxxxxxxx????x"
#define ICLIENTMODE_SIG "\x55\x89\xe5\x83\xec\x18\x89\x5d\xf8\xe8\x00\x00\x00\x00\x81\xc3\x00\x00\x00\x00\x89\x75\xfc\x0f\xb6\x75\x0c\x81\xe6\x00\x00\x00\x00\xe8"

void
se_msg(const char *msg, ...);

void
find_interfaces(void);

void
find_client_mode(void);
