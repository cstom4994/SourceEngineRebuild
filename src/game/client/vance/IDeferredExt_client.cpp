#include "cbase.h"
#include "IDeferredExt.h"

#include "tier0/memdbgon.h"

CSysModule *__g_pDeferredShaderModule = NULL;
static IDeferredExtension *__g_defExt = NULL;

IDeferredExtension *GetDeferredExt() {
    return __g_defExt;
}

bool ConnectDeferredExt() {
    char modulePath[MAX_PATH * 4];
    Q_snprintf(modulePath, sizeof(modulePath), "%s/bin/game_shader_dx9.dll", engine->GetGameDirectory());
    if (!Sys_LoadInterface(modulePath, DEFERRED_EXTENSION_VERSION, &__g_pDeferredShaderModule,
                           reinterpret_cast<void **>(&__g_defExt))) {
        Warning("Unable to pull IDeferredExtension interface from game_shader_dx9.dll.\nPulling from stdshader_dx9.dll\n");
    } else {
        Msg("Loaded IDeferredExtension interface from game_shader_dx9.dll\n");
        return __g_defExt != NULL;
    }

    Q_snprintf(modulePath, sizeof(modulePath), "bin/stdshader_dx9.dll");
    if (!Sys_LoadInterface(modulePath, DEFERRED_EXTENSION_VERSION, &__g_pDeferredShaderModule,
                           reinterpret_cast<void **>(&__g_defExt)))
        Warning("Unable to pull IDeferredExtension interface from stdshader_dx9.dll.\n");

    return __g_defExt != NULL;
}

void ShutdownDeferredExt() {
    if (!__g_defExt)
        return;

    //__g_defExt->CommitLightData_Common(NULL);

    __g_defExt = NULL;

    Sys_UnloadModule(__g_pDeferredShaderModule);
}