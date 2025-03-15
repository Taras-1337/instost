#pragma once

#include <stdio.h>

#include "SDK/IEngineClient.h"

typedef void(*se_msg_fn)(const char *msg, va_list);

extern void *engine;
extern void *engine_vgui;
extern void *surface;
extern void *client;
extern void *entity_list;
extern void *model_info;
extern void *debug_overlay;
extern void *trace;

void
se_msg(const char *msg, ...);

void
find_interfaces(void);
