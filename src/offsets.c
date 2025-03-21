#include "offsets.h"
#include "netvar.h"

#include "SDK/IBaseClientDLL.h"

#include "c-vector/vec.h"

struct c_offsets offsets;

void
get_offsets(void)
{
    struct recv_table **tables = netvar_get_tables();

    offsets.DT_BasePlayer.m_iHealth = netvar_get_offset(tables, "DT_BasePlayer", "m_iHealth");
    offsets.DT_BasePlayer.m_lifeState = netvar_get_offset(tables, "DT_BasePlayer", "m_lifeState");
    offsets.DT_BasePlayer.m_vecViewOffset = netvar_get_offset(tables, "DT_BasePlayer", "m_vecViewOffset[0]");
    offsets.DT_BasePlayer.m_aimPunchAngle = netvar_get_offset(tables, "DT_BasePlayer", "m_aimPunchAngle");

    offsets.DT_BaseEntity.m_vecOrigin = netvar_get_offset(tables, "DT_BaseEntity", "m_vecOrigin");
    offsets.DT_BaseEntity.m_iTeamNum = netvar_get_offset(tables, "DT_BaseEntity", "m_iTeamNum");

    offsets.DT_INSPlayer.m_angEyeAngles[0] = netvar_get_offset(tables, "DT_INSPlayer", "m_angEyeAngles[0]");
    offsets.DT_INSPlayer.m_angEyeAngles[1] = netvar_get_offset(tables, "DT_INSPlayer", "m_angEyeAngles[1]");
    offsets.DT_INSPlayer.m_flFlashMaxAlpha = netvar_get_offset(tables, "DT_INSPlayer", "m_flFlashMaxAlpha");
    offsets.DT_INSPlayer.m_iPlayerFlags = netvar_get_offset(tables, "DT_INSPlayer", "m_iPlayerFlags");

    offsets.DT_BaseCombatCharacter.m_hActiveWeapon = netvar_get_offset(tables, "DT_BaseCombatCharacter", "m_hActiveWeapon");

    offsets.DT_BaseCombatWeapon.m_iClip1 = netvar_get_offset(tables, "DT_BaseCombatWeapon", "m_iClip1");
    offsets.DT_BaseCombatWeapon.m_iActiveFiremode = netvar_get_offset(tables, "DT_INSWeaponBallistic", "m_iActiveFiremode");

    vector_free(tables);
}
