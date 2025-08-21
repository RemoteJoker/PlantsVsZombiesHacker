#include "plantsvszombiesfunc.h"
#include "cheatfunc.h"

DWORD WINAPI CheatMain(LPVOID lpParameter){
    CheatFunc *g_cheat = new CheatFunc();
    g_cheat->start();
    return 0;
}
