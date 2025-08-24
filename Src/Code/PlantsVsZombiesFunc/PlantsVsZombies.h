#pragma once
#ifndef PLANTSVSZOMBIES_H
#define PLANTSVSZOMBIES_H

#include <windows.h>
#include <iostream>
#include <string>

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

//���ܿ���
VOID SetEnable(UINT8 v_index,BOOL v_status);

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

/*��Ϸ����--����*/

VOID FuncDispatch(ClientData v_data);//������ǲ����

//��ѭ��
DWORD WINAPI MainLoop(LPVOID lpParam);

#endif // !PLANTSVSZOMBIES
