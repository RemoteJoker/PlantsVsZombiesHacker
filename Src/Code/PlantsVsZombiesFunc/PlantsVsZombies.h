#pragma once
#ifndef PLANTSVSZOMBIES_H
#define PLANTSVSZOMBIES_H

#include <windows.h>
#include <iostream>
#include <string>
#include "include/detours.h"

#define GAMEBASEMENT 0x00400000

// 原始函数指针
extern BOOL(WINAPI* TrueQueryPerformanceCounter)(LARGE_INTEGER*);
extern BOOL(WINAPI* TrueQueryPerformanceFrequency)(LARGE_INTEGER*);
extern DWORD(WINAPI* TrueGetTickCount)(void);

enum ControlType {
    LoadDll,
    UnLoadDll,
    Sun,
    Cold,
    Tree,
    Gold,
    Kill,
    Bomb,
    PlantsHealth,
    ZombiesHealth,
    Look,
    PlantsSet,
    ZombiesSet,
    Speed,
    Driver
};

enum ControlResult {
    Successful,
    Failed
};

struct ClientData {
    UINT8 str_id;
    UINT8 str_y;
    UINT8 str_x;
    UINT8 str_plant;
    UINT8 str_zombie;
    ClientData()
        : str_id(0), str_y(0), str_x(0), str_plant(0), str_zombie(0)
    {
    }
};

struct ServerData {
    UINT8 str_result;
    ServerData()
        : str_result(0)
    {
    }
};

//初始化游戏作弊
VOID InitGameCheat();

//卸载函数
VOID FuncUnLoadDll();

/*游戏功能--开始*/
VOID FuncSun();

VOID FuncCold();

VOID FuncTree();

VOID FuncGold();

VOID FuncKill();

VOID FuncBomb();

VOID FuncPlantsHealth();

VOID FuncZombiesHealth();

VOID FuncLook();

VOID FuncPlantsSet();

VOID FuncZombiesSet();

VOID FuncSpeed();

VOID FuncDriver();

VOID AsmThreadFunctionPlant();

VOID AsmThreadFunctionZombie();
/*游戏功能--结束*/

VOID FuncDispatch(ClientData v_data);//功能派遣函数

VOID ReturnControlResult(UINT result);//返回操作结果

VOID SetSpeed(int speedPercent);//设置变速

BOOL WINAPI HookedQueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount);

BOOL WINAPI HookedQueryPerformanceFrequency(LARGE_INTEGER* lpFrequency);

DWORD WINAPI HookedGetTickCount(void);

//主循环
DWORD WINAPI MainLoop(LPVOID lpParam);

#endif // !PLANTSVSZOMBIES
