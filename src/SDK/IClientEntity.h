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

enum ebone {
    EBONE_INVALID = -1,

    EBONE_PELVIS = 0,
    EBONE_SPINE_0 = 1,
    EBONE_SPINE_1 = 2,
    EBONE_SPINE_2 = 3,
    EBONE_SPINE_3 = 4, // center mass
    EBONE_SPINE_4 = 5,
    EBONE_NECK = 6,
    EBONE_HEAD = 21, //

    EBONE_HAND_L = 10,
    EBONE_ELBOW_L = 9, //
    EBONE_SHOULDER_L = 8,
    EBONE_COLLAR_L = 7,

    EBONE_HAND_R = 14,
    EBONE_ELBOW_R = 13, //
    EBONE_SHOULDER_R = 12,
    EBONE_COLLAR_R = 11,

    EBONE_FOOT_L = 20,
    EBONE_KNEE_L = 19, //
    EBONE_HIP_L = 18,

    EBONE_FOOT_R = 17,
    EBONE_KNEE_R = 16, //
    EBONE_HIP_R = 15
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

int
get_fire_mode(void *self);

unsigned *
GetINSFlags(void *self);

bool
is_scoped(void *self);

bool
IsSprinting(void *self);

vector3
get_aim_punch_angle(void *self);

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
