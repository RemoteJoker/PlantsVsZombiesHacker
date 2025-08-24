// dllmain.cpp : 定义 DLL 应用程序的入口点。

#include "PlantsVsZombies.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        MessageBox(nullptr, L"加载成功", L"标题", 0);
        CreateThread(nullptr, 0, MainLoop, nullptr, 0, nullptr);
        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
    {
        //MessageBox(nullptr, L"卸载成功", L"标题", 0);
        break;
    }
    }
    return TRUE;
}

