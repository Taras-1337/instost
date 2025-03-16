#include "SDK/common.h"
#include "interfaces.h"
#include "offsets.h"
#include "vmt.h"

#include "SDK/IEngineVGui.h"

int
__attribute__((constructor))
instost_in(void)
{
    /* Search for SourceEngine interfaces */
    find_interfaces();
    se_msg("instost_in_start\n");

    /* TODO: Setup font */
    // setup_font("Arial", 22, 0);
    font = 11; // 11

    /* Dump offsets from Netvars */
    get_offsets();

    /* Apply defined VMT hooks */
    init_hooks();

    se_msg("instost_in_end\n");
    return 0;
}

void
__attribute__((destructor))
instost_clup(void)
{
    se_msg("instost_clup_start\n");

    cleanup_hooks();

    se_msg("instost_clup_end\n");
}
