#include "PlantsVsZombies.h"

static HANDLE g_pipe = INVALID_HANDLE_VALUE;
static LPCWSTR g_pipe_name = L"\\\\.\\pipe\\PVZ";
static BOOL g_status = TRUE;
static UINT8 g_y = 0;
static UINT8 g_x = 0;
static UINT8 g_plant = 0;
static UINT8 g_zombie = 0;

VOID InitGameCheat() {
    g_pipe = CreateFile(g_pipe_name,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
    DWORD v_mode = PIPE_READMODE_MESSAGE;
    SetNamedPipeHandleState(g_pipe, &v_mode, NULL, NULL);
}

VOID SetEnable(UINT8 v_index, BOOL v_status) {
}

VOID FuncUnLoadDll() {
    g_status = FALSE;
}

VOID FuncSun() {
}

VOID FuncCold() {
}

VOID FuncTree() {
}

VOID FuncGold() {
}

VOID FuncKill() {
}

VOID FuncBomb() {
}

VOID FuncPlantsHealth() {
}

VOID FuncZombiesHealth() {
}

VOID FuncLook() {
}

VOID FuncPlantsSet() {
}

VOID FuncZombiesSet() {
}

VOID FuncSpeed() {
}

VOID FuncDriver() {
}

VOID FuncDispatch(ClientData v_data) {
    g_y = v_data.str_y;
    g_x = v_data.str_x;
    g_plant = v_data.str_plant;
    g_zombie = v_data.str_zombie;
    switch (v_data.str_id) {
    case UnLoadDll: { FuncUnLoadDll(); }break;
    case Sun: { FuncSun(); }break;
    case Cold: { FuncCold(); }break;
    case Tree: { FuncTree(); }break;
    case Gold: { FuncGold(); }break;
    case Kill: { FuncKill(); }break;
    case Bomb: { FuncBomb(); }break;
    case PlantsHealth: { FuncPlantsHealth(); }break;
    case ZombiesHealth: { FuncZombiesHealth(); }break;
    case Look: { FuncLook(); }break;
    case PlantsSet: { FuncPlantsSet(); }break;
    case ZombiesSet: { FuncZombiesSet(); }break;
    case Speed: { FuncSpeed(); }break;
    case Driver: { FuncDriver(); }break;
    default:break;
    }
}

DWORD WINAPI MainLoop(LPVOID lpParam) {
    InitGameCheat();
    while (g_status) {
        ClientData v_data;
        DWORD v_bytesRead;
        if (ReadFile(g_pipe, &v_data,sizeof(ClientData),&v_bytesRead,NULL)) {
            if (v_bytesRead == sizeof(ClientData)) {
                FuncDispatch(v_data);
            }
        }
    }
    return 0;
}