#include "vmt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hacks/esp.h"
#include "hacks/radar.h"
#include "interfaces.h"

#include "SDK/IEngineClient.h"
#include "SDK/IClientEntityList.h"
#include "SDK/IEngineClient.h"
#include "SDK/IEngineVGui.h"

#include "hacks/hud.h"
#include "hacks/noflash.h"

wchar_t *wbuffer;
vmt_hook engine_vgui_vmt;
vmt_hook client_mode_vmt;

void
vmt_ini(vmt_hook *vmt, void *interface);

void
vmt_hook_method(vmt_hook *vmt, void *method, size_t method_index);

void
vmt_hook_apply(vmt_hook *vmt);

void
vmt_hook_restore(vmt_hook *vmt);

void
hook_paint(void *self, enum paintmode mode);

bool
hook_create_move(void *self, float flInputSampleTime, struct CUserCmd *cmd);

void
init_hooks()
{
    wbuffer = malloc(WBUF_SIZE * sizeof(wchar_t));

    vmt_ini(&engine_vgui_vmt, engine_vgui);
    vmt_hook_method(&engine_vgui_vmt, (void *) hook_paint, PAINT_IDX);
    vmt_hook_apply(&engine_vgui_vmt);

    /*
    vmt_ini(&client_mode_vmt, client_mode);
    vmt_hook_method(&client_mode_vmt, (void *) hook_create_move, CREATE_MOVE_IDX);
    vmt_hook_apply(&client_mode_vmt);
    */
}

void
cleanup_hooks()
{
    vmt_hook_restore(&engine_vgui_vmt);
    vmt_hook_restore(&client_mode_vmt);
    if (wbuffer) {
        free(wbuffer);
    }
}

void
vmt_ini(vmt_hook *vmt, void *interface)
{
    vmt->interface = (uintptr_t **)interface;

    size_t method_count = 0;

    while ((*vmt->interface)[method_count]) ++method_count;
    vmt->original_vmt = *(vmt->interface);

    vmt->vmt = (uintptr_t *)malloc(sizeof(uintptr_t) * method_count);
    memcpy(vmt->vmt, vmt->original_vmt, sizeof(uintptr_t) * method_count);
}

void
vmt_hook_method(vmt_hook *vmt, void *method, size_t method_index)
{
    vmt->vmt[method_index] = (uintptr_t)method;
}

void
vmt_hook_apply(vmt_hook *vmt)
{
    *vmt->interface = vmt->vmt;
}

void
vmt_hook_restore(vmt_hook *vmt)
{
    *vmt->interface = vmt->original_vmt;
    free(vmt->vmt);
}

void
hook_paint(void *self, enum paintmode mode)
{
    int width, height;

    ((void (*)(void *, enum paintmode)) engine_vgui_vmt.original_vmt[PAINT_IDX])(self, mode);

    if (is_taking_screenshot(engine)) {
        se_msg("PIZDOS SCREENER");
        return;
    }

    if (!(mode & PAINT_UIPANELS))
    {
        void *local_player = get_client_entity(entity_list, get_local_player(engine));
        if (local_player) {
            get_screen_size(engine, &width, &height);

            hk_noflash(local_player);
            hk_esp(local_player);
            hk_hud(local_player, width, height);
            // TODO: fix radar
            // hk_radar(local_player, width, height);
            return;
        }
    }
}

bool
hook_create_move(void *self, float flInputSampleTime, struct CUserCmd *cmd)
{
    ((bool (*)(void *, float, struct CUserCmd *)) client_mode_vmt.original_vmt[CREATE_MOVE_IDX])(self, flInputSampleTime, cmd);

    if (cmd && cmd->command_number) {
        void *local_player = get_client_entity(entity_list, get_local_player(engine));
        // hk_ambt(local_player, cmd);
    }

    return false;
}
