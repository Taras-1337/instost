#include "hud.h"

#include <strings.h>
#include <wchar.h>

#include "../vmt.h"
#include "../interfaces.h"

#include "../SDK/IClientEntity.h"
#include "../SDK/IClientEntityList.h"
#include "../SDK/IEngineVGui.h"

void
hk_hud(void *local_player, int width, int height)
{
    draw_set_color(surface, 0, 255, 0, 255);

    /* CROSSHAIR */
    draw_line(surface, width / 2, height / 2 - 6, width / 2, height / 2 + 5);
    draw_line(surface, width / 2 - 6, height / 2, width / 2 + 5, height / 2);

    /* HEALTH */
    const int health = get_health(local_player);
    if (health < 31) {
        draw_set_text_color(surface, 255, 0, 0, 255);
    } else {
        draw_set_text_color(surface, 0, 255, 0, 255);
    }
    draw_set_text_pos(surface, width / 2 - 35, height / 2 - 6);
    draw_set_text_font(surface, font);
    bzero(wbuffer, 4 * sizeof(wchar_t));
    swprintf(wbuffer, 4, L"%d", health);
    draw_print_text(surface, wbuffer, wcslen(wbuffer));

    void *weapon = get_client_entity_from_handle(entity_list, get_active_weapon(local_player));
    if (weapon) {
        const int ammo = get_ammo(weapon);
        if (ammo < 5) {
            draw_set_text_color(surface, 255, 0, 0, 255);
        } else {
            draw_set_text_color(surface, 0, 255, 0, 255);
        }
        draw_set_text_pos(surface, width / 2 + 18, height / 2 - 7);
        draw_set_text_font(surface, font);
        bzero(wbuffer, 9 * sizeof(wchar_t));
        swprintf(wbuffer, 9, L"%d", ammo);
        draw_print_text(surface, wbuffer, wcslen(wbuffer));
    }
}
