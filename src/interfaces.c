#include "interfaces.h"

#include <stdarg.h>
#include <stdbool.h>

#include <dlfcn.h>

#include "SDK/common.h"

void *engine = nullptr;
void *engine_vgui = nullptr;
void *surface = nullptr;
void *client = nullptr;
void *entity_list = nullptr;
void *model_info = nullptr;
void *debug_overlay = nullptr;
void *trace = nullptr;
se_msg_fn _msgfn;

void
se_msg(const char *msg, ...) {
    char buffer[256];
    va_list list;

    if (msg == nullptr) {
        return;
    }

    va_start(list, msg);
    vsprintf(buffer, msg, list);
    va_end(list);

    _msgfn(buffer, list);
}

void
find_interfaces(void)
{
    void *libtier0 = dlopen("./bin/libtier0.so", 1);
    _msgfn = (se_msg_fn) dlsym(libtier0, "Msg");

    engine = get_interface("./bin/engine.so", "VEngineClient", false);
    engine_vgui = get_interface("./bin/engine.so", "VEngineVGui", false);
    surface = get_interface("./bin/vguimatsurface.so", "VGUI_Surface", false);
    client = get_interface("./insurgency/bin/client.so", "VClient", false);
    entity_list = get_interface("./insurgency/bin/client.so", "VClientEntityList", false);
    model_info = get_interface("./bin/engine.so", "VModelInfoClient", false);
    debug_overlay = get_interface("./bin/engine.so", "VDebugOverlay", false);
    trace = get_interface("./bin/engine.so", "EngineTraceClient", false);
}
