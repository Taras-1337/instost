#pragma once

#include <stdint.h>

extern struct c_offsets {
    struct {
        uintptr_t m_iHealth;
        uintptr_t m_vecViewOffset;
        uintptr_t m_lifeState;
    } DT_BasePlayer;

    struct {
        uintptr_t m_angEyeAngles[2];
        uintptr_t m_flFlashMaxAlpha;
    } DT_INSPlayer;

    struct
    {
        uintptr_t m_hActiveWeapon;
    } DT_BaseCombatCharacter;

    struct
    {
        uintptr_t m_iClip1;
    } DT_BaseCombatWeapon;

    struct
    {
        uintptr_t m_vecOrigin;
        uintptr_t m_iTeamNum;
    } DT_BaseEntity;
} offsets;

void
get_offsets(void);
