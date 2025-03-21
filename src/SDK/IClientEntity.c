#include "IClientEntity.h"

#include <stdint.h>
#include <string.h>

#include "common.h"

#include "../offsets.h"

float *
get_flash_max_alpha(void *self)
{
    return (float *)(((uintptr_t) self) + offsets.DT_INSPlayer.m_flFlashMaxAlpha);
}

int
get_health(void *self)
{
    return *(int *)(((uintptr_t) self) + offsets.DT_BasePlayer.m_iHealth);
}

void *
get_active_weapon(void *self)
{
    return (void *)(((uintptr_t) self) + offsets.DT_BaseCombatCharacter.m_hActiveWeapon);
}

uint8_t
get_live_state(void *self)
{
    return *(uint8_t *)(((uintptr_t) self) + offsets.DT_BasePlayer.m_lifeState);
}

bool
is_alive(void *self)
{
    return get_health(self) > 0 && get_live_state(self) == LIFE_ALIVE;
}

int
get_ammo(void *self)
{
    return *(int *)(((uintptr_t) self) + offsets.DT_BaseCombatWeapon.m_iClip1);
}

char *
get_weapon_name(void *self)
{
    typedef char *(*vfn)(void *);
    vfn vfunc = (vfn) getvfunc(self, 402, 0);
    return vfunc(self);
}

int
get_fire_mode(void *self)
{
    return *(int *)(((uintptr_t) self) + offsets.DT_BaseCombatWeapon.m_iActiveFiremode);
}

unsigned *
GetINSFlags(void *self)
{
    return (unsigned *)(((uintptr_t) self) + offsets.DT_INSPlayer.m_iPlayerFlags);
}

bool
is_scoped(void *self)
{
    return (bool) (*(GetINSFlags(self)) & 1);
}

bool
IsSprinting(void *self)
{
    return (bool) (*(GetINSFlags(self)) & 4);
}

bool
is_dormant(void *self)
{
    typedef bool (*vfn)(void *);
    vfn vfunc = (vfn) getvfunc(self, 79, 0);
    return vfunc(self);
}

enum team_id
get_team_num(void *self)
{
    return *(enum team_id *)(((uintptr_t) self) + offsets.DT_BaseEntity.m_iTeamNum);
}

vector3
get_pos_origin(void *self)
{
    return *(vector3 *)(((uintptr_t) self) + offsets.DT_BaseEntity.m_vecOrigin);
}

vector3
get_aim_punch_angle(void *self)
{
    return *(vector3 *)(((uintptr_t) self) + offsets.DT_BasePlayer.m_aimPunchAngle);
}

vector3
get_vec_view_offset(void *self)
{
    return *(vector3 *)(((uintptr_t) self) + offsets.DT_BasePlayer.m_vecViewOffset);
}

vector3
get_pos_eye(void *self)
{
    vector3 res;

    vector3 origin = get_pos_origin(self);
    vector3 offset = get_vec_view_offset(self);
    res.x = origin.x + offset.x;
    res.y = origin.y + offset.y;
    res.z = origin.z + offset.z;

    return res;
}

vector3
get_eye_angles(void *self)
{
    return *(vector3 *)(((uintptr_t) self) + offsets.DT_INSPlayer.m_angEyeAngles[0]);
}


struct model_t *
get_model(void *self)
{
    typedef struct model_t *(*vfn)(struct model_t *);
/*
 if (!pizdos) {
        pizdos = true;
    for (int i = 0; i < 512; ++i) {
        if ( getvfunc(self, i, 0) == (void*) addr) {
            printf("PIZDOS(%d): %p\n", i, getvfunc(self, i, 0));
            fflush(stdout);
        }
    }
    }
 */
    vfn vfunc = (vfn) getvfunc(self, 450, 0); // In C++ index is 8...
    return vfunc(self + 4);                   // Total zrada
}

bool
setup_bones(void *self,
            struct matrix3x4_t *bone_matrix,
            int                 max_bones,
            int                 bone_mask,
            float               cur_time)
{
    typedef  struct model_t *(*vfn)(void *, struct matrix3x4_t *, int, int, float);
    vfn vfunc = (vfn) getvfunc(self, 455, 0); // In C++ index is 13...
    return vfunc(self + 4 /* Yet another zrada */, bone_matrix, max_bones, bone_mask, cur_time);
}

bool
is_grenade(const char *name)
{
    return strstr(name, "f1")
        || strstr(name, "m67")
        || strstr(name, "m18")
        || strstr(name, "anm14")
        || strstr(name, "molotov")
        || strstr(name, "rpg7")
        || strstr(name, "at4")
        || strstr(name, "c4_clicker")
        || strstr(name, "m26a2")
        || strstr(name, "ied")
        || strstr(name, "m84")
        || strstr(name, "gp25")
        || strstr(name, "m203");
}
