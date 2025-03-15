#pragma once

#include <stdint.h>

#include "../math.h"

struct player_info_s
{
    union {
        int64_t xuid;
        struct {
            int xuidlow;
            int xuidhigh;
        };
    };
    char          name[32];
    int           userid;
    char          guid[33];
    unsigned int  friendsid;
    char          friendsname[32];
    bool          fakeplayer;
    bool          ishltv;
    unsigned int  customfiles[4];
    unsigned char filesdownloaded;
};

void
get_screen_size(void *self, int *width, int *height);

void
get_view_angles(void *self, vector3 *angles);

int
get_local_player(void *self);

bool
get_player_info(void *self, int index, struct player_info_s *info);

int
get_max_clients(void *self);

bool
is_ingame(void *self);

bool
is_taking_screenshot(void *self);
