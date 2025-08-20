#include "plantsvszombiesfunc.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved
                      )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CreateThread(nullptr,0,CheatMain,nullptr,0,nullptr);
    }
    // case DLL_THREAD_ATTACH:
    // case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
    {}
        //     break;
    }
    return TRUE;
}
