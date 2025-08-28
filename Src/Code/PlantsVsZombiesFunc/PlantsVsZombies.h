#pragma once
#ifndef PLANTSVSZOMBIES_H
#define PLANTSVSZOMBIES_H

#include <windows.h>
#include <iostream>
#include <string>
#include "include/detours.h"

#define GAMEBASEMENT 0x00400000

// ԭʼ����ָ��
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

//��ʼ����Ϸ����
VOID InitGameCheat();

//ж�غ���
VOID FuncUnLoadDll();

/*��Ϸ����--��ʼ*/
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
/*��Ϸ����--����*/

VOID FuncDispatch(ClientData v_data);//������ǲ����

VOID ReturnControlResult(UINT result);//���ز������

VOID SetSpeed(int speedPercent);//���ñ���

BOOL WINAPI HookedQueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount);

BOOL WINAPI HookedQueryPerformanceFrequency(LARGE_INTEGER* lpFrequency);

DWORD WINAPI HookedGetTickCount(void);

//��ѭ��
DWORD WINAPI MainLoop(LPVOID lpParam);

#endif // !PLANTSVSZOMBIES
