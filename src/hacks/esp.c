#include "esp.h"

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stddef.h>
#include <wchar.h>

#include "../SDK/IVModelInfo.h"
#include "../SDK/IEngineVGui.h"
#include "../SDK/IEngineTrace.h"
#include "../SDK/IVDebugOverlay.h"
#include "../SDK/IEngineClient.h"
#include "../SDK/IClientEntity.h"
#include "../SDK/IClientEntityList.h"

#include "../interfaces.h"
#include "../vmt.h"

void
draw_skeleton(void *player, void *local_player, bool dormant, bool same_team);

void
hk_esp(void *local_player)
{
    for (int i = 0; i <= get_max_clients(engine); ++i) {
        void *player = get_client_entity(entity_list, i);
        if (!player || player == local_player) {
            continue;
        }

        bool alive = is_alive(player);
        bool dormant = is_dormant(player);
        bool same_team = get_team_num(player) == get_team_num(local_player);
        vector3 ppos = get_pos_origin(player);
        vector3 spos;

        if (!alive) {
            continue;
        }

        draw_skeleton(player, local_player, dormant, same_team);

        struct player_info_s pinfo;
        if (!get_player_info(engine, i, &pinfo)) {
            continue;
        }

        if (!screen_position(debug_overlay, &ppos, &spos)) {
            if (dormant) {
                draw_set_text_color(surface, 71, 71, 71, 255);
            } else if (same_team) {
                draw_set_text_color(surface, 0, 183, 255, 255);
            } else {
                draw_set_text_color(surface, 255, 0, 0, 255);
            }
            draw_set_text_pos(surface, spos.x - 35, spos.y);
            draw_set_text_font(surface, font);
            bzero(wbuffer, 23 * sizeof(wchar_t));
            swprintf(wbuffer, 23, L"(%d) %s", get_health(player), pinfo.name);
            draw_print_text(surface, wbuffer, wcslen(wbuffer));

            const float range = vector3_distance(get_pos_origin(local_player), ppos) * 0.0254f;
            if (range < 25) {
                draw_set_text_color(surface, 255, 0, 0, 255);
            } else if (range < 50) {
                draw_set_text_color(surface, 255, 238, 0, 255);
            } else if (range < 90) {
                draw_set_text_color(surface, 136, 255, 0, 255);
            } else {
                draw_set_text_color(surface, 166, 0, 255, 255);
            }
            draw_set_text_pos(surface, spos.x - 35, spos.y + 12);
            draw_set_text_font(surface, font);
            bzero(wbuffer, 5 * sizeof(wchar_t));
            swprintf(wbuffer, 5, L"%.0f", range);
            draw_print_text(surface, wbuffer, wcslen(wbuffer));


            void *enemyweapon = get_client_entity_from_handle(entity_list, get_active_weapon(player));
            if (enemyweapon) {
                char* weapname = get_weapon_name(enemyweapon);
                if (weapname) {
                    if (strncmp(weapname, "weapon_", 7) == 0) {
                        weapname += 7;
                    }
                    if (is_grenade(weapname)) {
                        draw_set_text_color(surface, 255, 0, 0, 255);
                    } else if (/*enemyweapon->GetInReload() TODO: Looks like it doesn't even work*/ false) {
                        draw_set_text_color(surface, 130, 130, 130, 255);
                    } else {
                        draw_set_text_color(surface, 252, 3, 186, 255);
                    }
                    draw_set_text_pos(surface, spos.x - 35, spos.y + 24);
                    draw_set_text_font(surface, font);
                    bzero(wbuffer, 18 * sizeof(wchar_t));
                    swprintf(wbuffer, 18, L"%s", weapname);
                    draw_print_text(surface, wbuffer, wcslen(wbuffer));
                }
            }
        }
    }
}

void
draw_skeleton(void *player, void *local_player, bool dormant, bool same_team)
{
    void *mdl = get_model(player);
    if (!mdl) {
        return;
    }

    struct studiohdr_t *p_studio_model = get_studio_model(model_info, mdl);
    if (!p_studio_model) {
        return;
    }

    static struct matrix3x4_t bone_matrix[128];
    if (setup_bones(player, bone_matrix, 128, 0x100, 0))
    {
        for (int i = 0; i < p_studio_model->numbones; i++)
        {
            struct mstudiobone_t *p_bone =
                (struct mstudiobone_t *)
                ((((unsigned char * ) (p_studio_model))
                  + p_studio_model->boneindex) + i * 216 /* NOTE: sizeof real sturct */);

            if (!p_bone || !(p_bone->flags & 256) || p_bone->parent == -1) {
                continue;
            }

            vector3 bpos1 = { bone_matrix[i].mat_val[0][3], bone_matrix[i].mat_val[1][3], bone_matrix[i].mat_val[2][3] };
            vector3 spos1;
            if (screen_position(debug_overlay, &bpos1, &spos1)) {
                continue;
            }

            vector3 bpos2 = { bone_matrix[p_bone->parent].mat_val[0][3], bone_matrix[p_bone->parent].mat_val[1][3], bone_matrix[p_bone->parent].mat_val[2][3] };
            vector3 spos2;
            if (screen_position(debug_overlay, &bpos2, &spos2)) {
                continue;
            }

            if (dormant) {
                draw_set_color(surface, 71, 71, 71, 255);
                draw_line(surface, spos1.x, spos1.y, spos2.x, spos2.y);
            } else if (same_team) {
                draw_set_color(surface, 0, 183, 255, 255);
                draw_line(surface, spos1.x, spos1.y, spos2.x, spos2.y);
            } else {
                vector3 dbone;
                dbone.x = bone_matrix[i].mat_val[0][3] + bone_matrix[i].mat_val[0][0] * 8;
                dbone.y = bone_matrix[i].mat_val[1][3] + bone_matrix[i].mat_val[1][0] * 8;
                dbone.z = bone_matrix[i].mat_val[2][3] + bone_matrix[i].mat_val[2][0] * 8;

                vector3 eye_pos = get_pos_eye(local_player);
                static struct matrix3x4_t local_bone_matrix[128];
                if (setup_bones(local_player, local_bone_matrix, 128, 0x100, 0)){
                    eye_pos.x = local_bone_matrix[21].mat_val[0][3];
                    eye_pos.y = local_bone_matrix[21].mat_val[1][3];
                    eye_pos.z = local_bone_matrix[21].mat_val[2][3];
                } else {
                    eye_pos = get_pos_eye(local_player);
                }

                if (send_ray(local_player, player, eye_pos, dbone)) {
                    draw_set_color(surface, 0, 255, 0, 255);
                    draw_line(surface, spos1.x, spos1.y, spos2.x, spos2.y);
                } else {
                    draw_set_color(surface, 255, 0, 0, 255);
                    draw_line(surface, spos1.x, spos1.y, spos2.x, spos2.y);
                }
            }
        }
    }
}
