#include "noflash.h"

#include "../SDK/IEngineVGui.h"
#include "../SDK/IClientEntity.h"

void
hk_noflash(void *local_player)
{
    float *flash_max_alpha = get_flash_max_alpha(local_player);
    if (flash_max_alpha && *flash_max_alpha > 1.5) {
        *flash_max_alpha = 1.0;
    }
}
