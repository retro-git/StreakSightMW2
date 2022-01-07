#include "windows.h"
#include "renderer.h"
#include "vfunc_hook.hpp"
#include "structs.h"
#include "utils.h"

RendererPtr renderer;
FontHandle font;
vfunc_hook d3d_hook;

stats_t* stats;
cg_t* cg;
refdef_t* refdef;

namespace index
{
    constexpr auto EndScene = 42;
    constexpr auto Reset = 16;
}

long __stdcall hkEndScene(IDirect3DDevice9* device)
{
    using EndScene = long(__stdcall*)(IDirect3DDevice9*);

    static auto oEndScene = d3d_hook.get_original<EndScene>(index::EndScene);
    static bool initResources = true;
    static int killsStart = stats->kills;
    static int deathsStart = stats->deaths;

    if (initResources && device)
    {
        renderer = std::make_shared<Renderer>(device, 1536);
        font = renderer->create_font("Verdana", 12, FONT_BOLD);

        initResources = false;
    }

    if (!cg->isIngame) {
        killsStart = stats->kills;
        return oEndScene(device);
    }
    else if (stats->deaths != deathsStart)
    {
        killsStart = stats->kills;
        deathsStart = stats->deaths;
    }

    renderer->begin();
    renderer->draw_text(font, { (float)(0.95 * refdef->width), (float)(0.015 * refdef->height) },
        std::string("streak: ") + std::to_string(stats->kills - killsStart), 0xffffffff);
    renderer->draw();
    renderer->end();

    return oEndScene(device);
}

long __stdcall hkReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    using Reset = long(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);

    static auto oReset = d3d_hook.get_original<Reset>(index::Reset);

    renderer->release();

    auto hr = oReset(device, pPresentationParameters);

    if (hr >= 0)
        renderer->reacquire();

    return hr;
}

DWORD WINAPI OnDllAttach(HMODULE hModule) {
    Sleep(1000);

    auto mod = GetModuleHandle(NULL);
    cg = *(cg_t**)(Utils::PatternScan(mod, "8B C7 B9 ? ? ? ?") + 3);
    refdef = *(refdef_t**)(Utils::PatternScan(mod, "8D 4C 24 08 B8 ? ? ? ?") + 5);
    stats = (stats_t*)(0x1B8B768 + 0x80);

    d3d_hook.setup(*reinterpret_cast<IDirect3DDevice9**>(0x6664C60));
    d3d_hook.hook_index(index::EndScene, hkEndScene);
    d3d_hook.hook_index(index::Reset, hkReset);

    while (!GetAsyncKeyState(VK_INSERT))
        Sleep(100);

    d3d_hook.unhook_all();
    FreeLibraryAndExitThread(static_cast<HMODULE>(hModule), 1);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)OnDllAttach, hModule, NULL, NULL);
    }

    return TRUE;
}
