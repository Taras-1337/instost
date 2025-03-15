#pragma once

#include <stdint.h>

#include "../math.h"

#include "IVModelRender.h"

#define LIFE_ALIVE 0

enum team_id
{
    TEAM_UNASSIGNED,
    TEAM_SPECTATOR,
    TEAM_TERRORIST,
    TEAM_COUNTER_TERRORIST,
};

float *
get_flash_max_alpha(void *self);

int
get_health(void *self);

void *
get_active_weapon(void *self);

uint8_t
get_live_state(void *self);

bool
is_alive(void *self);

int
get_ammo(void *self);

char *
get_weapon_name(void *self);

bool
is_dormant(void *self);

enum team_id
get_team_num(void *self);

vector3
get_pos_origin(void *self);

vector3
get_vec_view_offset(void *self);

vector3
get_pos_eye(void *self);

vector3
get_eye_angles(void *self);

struct model_t *
get_model(void *self);

bool
setup_bones(void *self,
            struct matrix3x4_t *bone_matrix,
            int                 max_bones,
            int                 bone_mask,
            float               cur_time);

bool
is_grenade(const char *name);
