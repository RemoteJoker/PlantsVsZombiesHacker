#include "PlantsVsZombies.h"

static HANDLE g_client_pipe = INVALID_HANDLE_VALUE;
static LPCWSTR g_client_pipe_name = L"\\\\.\\pipe\\PVZ";
static BOOL g_status = TRUE;
static UINT8 g_y = 0;
static UINT8 g_x = 0;
static UINT8 g_plant = 0;
static UINT8 g_zombie = 0;
static int g_currentSpeed = 100; // 100% = �����ٶ�
static CRITICAL_SECTION g_cs;
static LARGE_INTEGER g_previousRealCount = { 0 };
static LARGE_INTEGER g_previousFakeCount = { 0 };
static LONGLONG g_realFrequency = 0;
static HANDLE g_current_process = INVALID_HANDLE_VALUE;

// ԭʼ����ָ��
BOOL(WINAPI* TrueQueryPerformanceCounter)(LARGE_INTEGER*) = nullptr;
BOOL(WINAPI* TrueQueryPerformanceFrequency)(LARGE_INTEGER*) = nullptr;
DWORD(WINAPI* TrueGetTickCount)(void) = nullptr;

VOID InitGameCheat() {
    g_current_process = GetCurrentProcess();//��ȡ����ID
    g_client_pipe = CreateFile(g_client_pipe_name,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
    DWORD v_mode = PIPE_READMODE_MESSAGE;
    SetNamedPipeHandleState(g_client_pipe, &v_mode, NULL, NULL);

    InitializeCriticalSection(&g_cs);
    // ��װDetours Hook
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    // ����Hook
    DetourAttach(&(PVOID&)TrueQueryPerformanceCounter, HookedQueryPerformanceCounter);
    DetourAttach(&(PVOID&)TrueQueryPerformanceFrequency, HookedQueryPerformanceFrequency);
    DetourAttach(&(PVOID&)TrueGetTickCount, HookedGetTickCount);
    if (DetourTransactionCommit() != NO_ERROR) {
        // Hookʧ�ܴ���
        MessageBoxA(NULL, "Failed to install hooks!", "Error", MB_ICONERROR);
    }
}

VOID FuncUnLoadDll() {
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&(PVOID&)TrueQueryPerformanceCounter, HookedQueryPerformanceCounter);
    DetourDetach(&(PVOID&)TrueQueryPerformanceFrequency, HookedQueryPerformanceFrequency);
    DetourDetach(&(PVOID&)TrueGetTickCount, HookedGetTickCount);
    DetourTransactionCommit();
    // ɾ���ٽ���
    DeleteCriticalSection(&g_cs);
    ReturnControlResult(Successful);
}

VOID FuncSun() {
    DWORD current_pointer = GAMEBASEMENT + 0x355E0C;  // ��һ����ַ
    DWORD value;
    SIZE_T bytes_read;
    // ��ȡ��һ��ָ��
    ReadProcessMemory(g_current_process,(LPCVOID)current_pointer,&value,
        sizeof(DWORD),&bytes_read);
    current_pointer = value + 0x868;  // ����ڶ�����ַ
    // ��ȡ�ڶ���ָ��
    ReadProcessMemory(g_current_process,(LPCVOID)current_pointer,&value,
        sizeof(DWORD),&bytes_read);
    current_pointer = value + 0x5578;  // �����������ַ
    /*std::wstring str2 = std::to_wstring(current_pointer);
    MessageBox(NULL, str2.c_str(), L"����", MB_ICONERROR);*/
    // д�����յ�Ŀ��ֵ
    DWORD target_value = 0x2710;  // �����ʼֵ�ᱻ����
    WriteProcessMemory(g_current_process,(LPVOID)current_pointer,&target_value,
        sizeof(DWORD),&bytes_read);
    ReturnControlResult(Successful);
}

VOID FuncCold() {
    DWORD current_pointer = GAMEBASEMENT + 0x9CE02;  // ��һ����ַ
    WORD value;
    SIZE_T bytes_read;
    // ��ȡ��һ��ָ��
    ReadProcessMemory(g_current_process, (LPCVOID)current_pointer, &value,
        sizeof(WORD), &bytes_read);
    DWORD v_old_protect, temp_protect;
    VirtualProtectEx(g_current_process, (LPVOID)current_pointer,
        sizeof(WORD), PAGE_EXECUTE_READWRITE, &v_old_protect);
    // д�����յ�Ŀ��ֵ
    WORD target_value = 0x9090;  // �����ʼֵ�ᱻ����
    WriteProcessMemory(g_current_process, (LPVOID)current_pointer, &target_value,
        sizeof(WORD), &bytes_read);
    VirtualProtectEx(g_current_process, (LPVOID)current_pointer,
        sizeof(WORD), v_old_protect, &temp_protect);
    ReturnControlResult(Successful);
}

VOID FuncTree() {
    DWORD current_pointer = GAMEBASEMENT + 0x355E0C;  // ��һ����ַ
    DWORD value;
    SIZE_T bytes_read;
    // ��ȡ��һ��ָ��
    ReadProcessMemory(g_current_process, (LPCVOID)current_pointer, &value,
        sizeof(DWORD), &bytes_read);
    current_pointer = value + 0x950;  // ����ڶ�����ַ
    // ��ȡ�ڶ���ָ��
    ReadProcessMemory(g_current_process, (LPCVOID)current_pointer, &value,
        sizeof(DWORD), &bytes_read);
    current_pointer = value + 0x11C;  // �����������ַ
    // д�����յ�Ŀ��ֵ
    DWORD target_value = 0x2710;
    WriteProcessMemory(g_current_process, (LPVOID)current_pointer, &target_value,
        sizeof(DWORD), &bytes_read);
    ReturnControlResult(Successful);
}

VOID FuncGold() {
    DWORD current_pointer = GAMEBASEMENT + 0x355E0C;  // ��һ����ַ
    DWORD value;
    SIZE_T bytes_read;
    // ��ȡ��һ��ָ��
    ReadProcessMemory(g_current_process, (LPCVOID)current_pointer, &value,
        sizeof(DWORD), &bytes_read);
    current_pointer = value + 0x950;  // ����ڶ�����ַ
    // ��ȡ�ڶ���ָ��
    ReadProcessMemory(g_current_process, (LPCVOID)current_pointer, &value,
        sizeof(DWORD), &bytes_read);
    current_pointer = value + 0x50;  // �����������ַ
    // д�����յ�Ŀ��ֵ
    DWORD target_value = 0x2710000;
    WriteProcessMemory(g_current_process, (LPVOID)current_pointer, &target_value,
        sizeof(DWORD), &bytes_read);
    ReturnControlResult(Successful);
}

VOID FuncKill() {
    DWORD current_pointer = GAMEBASEMENT + 0x355E0C;  // ��һ����ַ
    DWORD value;
    SIZE_T bytes_read;
    // ��ȡ��һ��ָ��
    ReadProcessMemory(g_current_process, (LPCVOID)current_pointer, &value,
        sizeof(DWORD), &bytes_read);
    current_pointer = value + 0x868;  // ����ڶ�����ַ
    // ��ȡ�ڶ���ָ��
    ReadProcessMemory(g_current_process, (LPCVOID)current_pointer, &value,
        sizeof(DWORD), &bytes_read);
    current_pointer = value + 0xA8;  // �����������ַ
    // ��ȡ������ָ��
    ReadProcessMemory(g_current_process, (LPCVOID)current_pointer, &value,
        sizeof(DWORD), &bytes_read);
    current_pointer = value + 0xC8;  // ������ļ���ַ
    // д�����յ�Ŀ��ֵ
    DWORD target_value = 0xA;
    WriteProcessMemory(g_current_process, (LPVOID)current_pointer, &target_value,
        sizeof(DWORD), &bytes_read);
    ReturnControlResult(Successful);
}

VOID FuncBomb() {
    DWORD v_x, v_y, v_plant;
    v_x = 0;
    v_y = 0;
    v_plant = 2;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 5; j++) {
            v_x = i;
            v_y = j;
            CreateThread(NULL, 0, AsmThreadFunctionPlant, NULL, 0, NULL);
        }
    }
    ReturnControlResult(Successful);
}

VOID FuncPlantsHealth() {
    DWORD current_pointer = GAMEBASEMENT + 0x14BA6D;  // ��һ����ַ
    BYTE value;
    SIZE_T bytes_read;
    // ��ȡ��һ��ָ��
    ReadProcessMemory(g_current_process, (LPCVOID)current_pointer, &value,
        sizeof(BYTE), &bytes_read);
    DWORD v_old_protect, temp_protect;
    VirtualProtectEx(g_current_process, (LPVOID)current_pointer,
        sizeof(BYTE), PAGE_EXECUTE_READWRITE, &v_old_protect);
    // д�����յ�Ŀ��ֵ
    BYTE target_value = 0x00;  // �����ʼֵ�ᱻ����
    WriteProcessMemory(g_current_process, (LPVOID)current_pointer, &target_value,
        sizeof(BYTE), &bytes_read);
    VirtualProtectEx(g_current_process, (LPVOID)current_pointer,
        sizeof(BYTE), v_old_protect, &temp_protect);
    ReturnControlResult(Successful);
}

VOID FuncZombiesHealth() {
    DWORD current_pointer = GAMEBASEMENT + 0x14CD8C;  // ��һ����ַ
    BYTE value[6];
    SIZE_T bytes_read;
    // ��ȡ��һ��ָ��
    ReadProcessMemory(g_current_process, (LPCVOID)current_pointer, &value,
        sizeof(BYTE)*6, &bytes_read);
    DWORD v_old_protect, temp_protect;
    VirtualProtectEx(g_current_process, (LPVOID)current_pointer,
        sizeof(BYTE) * 6, PAGE_EXECUTE_READWRITE, &v_old_protect);
    // д�����յ�Ŀ��ֵ
    BYTE target_value[6] = {0xB9,0xFF,0xFF ,0xFF ,0x7F ,0x90 };  // �����ʼֵ�ᱻ����
    WriteProcessMemory(g_current_process, (LPVOID)current_pointer, &target_value,
        sizeof(BYTE) * 6, &bytes_read);
    VirtualProtectEx(g_current_process, (LPVOID)current_pointer,
        sizeof(BYTE) * 6, v_old_protect, &temp_protect);
    ReturnControlResult(Successful);
}

VOID FuncLook() {
    DWORD current_pointer = GAMEBASEMENT + 0x59C1C;  // ��һ����ַ
    BYTE value[3];
    SIZE_T bytes_read;
    // ��ȡ��һ��ָ��
    ReadProcessMemory(g_current_process, (LPCVOID)current_pointer, &value,
        sizeof(BYTE) * 3, &bytes_read);
    DWORD v_old_protect, temp_protect;
    VirtualProtectEx(g_current_process, (LPVOID)current_pointer,
        sizeof(BYTE) * 3, PAGE_EXECUTE_READWRITE, &v_old_protect);
    // д�����յ�Ŀ��ֵ
    BYTE target_value[3] = { 0x90,0x90,0x40 };  // �����ʼֵ�ᱻ����
    WriteProcessMemory(g_current_process, (LPVOID)current_pointer, &target_value,
        sizeof(BYTE) * 3, &bytes_read);
    VirtualProtectEx(g_current_process, (LPVOID)current_pointer,
        sizeof(BYTE) * 3, v_old_protect, &temp_protect);
    ReturnControlResult(Successful);
}

VOID FuncPlantsSet() {
    CreateThread(NULL, 0, AsmThreadFunctionPlant, NULL, 0, NULL);
    ReturnControlResult(Successful);
}

VOID FuncZombiesSet() {
    CreateThread(NULL, 0, AsmThreadFunctionZombie, NULL, 0, NULL);
    ReturnControlResult(Successful);
}

VOID FuncSpeed() {
    ReturnControlResult(Successful);
}

VOID FuncDriver() {
    ReturnControlResult(Successful);
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

VOID ReturnControlResult(UINT result) {
    ServerData v_data;
    v_data.str_result = result;
    char v_temp_str[sizeof(ClientData)];
    memcpy(v_temp_str, &v_data, sizeof(ClientData));
    DWORD v_bytes_read;
    WriteFile(g_client_pipe, v_temp_str, sizeof(ServerData), &v_bytes_read, NULL);
}

VOID SetSpeed(int speedPercent) {
    int actualSpeedPercent;
    switch (speedPercent) {
    case 1: actualSpeedPercent = 100; break; // 1�� = �����ٶ�
    case 2: actualSpeedPercent = 200; break; // 2���ٶ�
    case 3: actualSpeedPercent = 300; break; // 3���ٶ�
    case 4: actualSpeedPercent = 400; break; // 4���ٶ�
    case 5: actualSpeedPercent = 500; break; // 5���ٶ�
    default: actualSpeedPercent = 100; break; // Ĭ�������ٶ�
    }

    EnterCriticalSection(&g_cs);
    g_currentSpeed = actualSpeedPercent;
    LeaveCriticalSection(&g_cs);
}

BOOL WINAPI HookedQueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount) {
    EnterCriticalSection(&g_cs);

    // ��ȡ��ʵ�ļ�����ֵ
    LARGE_INTEGER realCount;
    TrueQueryPerformanceCounter(&realCount);

    // ��ʼ������һ�ε��ã�
    if (g_previousRealCount.QuadPart == 0) {
        g_previousRealCount = realCount;
        g_previousFakeCount = realCount;
        *lpPerformanceCount = realCount;
        LeaveCriticalSection(&g_cs);
        return TRUE;
    }

    // ��ȡ��ʵƵ�ʣ�ֻ��Ҫһ�Σ�
    if (g_realFrequency == 0) {
        LARGE_INTEGER freq;
        TrueQueryPerformanceFrequency(&freq);
        g_realFrequency = freq.QuadPart;
    }

    // ������ʵʱ������
    LONGLONG realDelta = realCount.QuadPart - g_previousRealCount.QuadPart;
    LONGLONG fakeDelta = realDelta;

    // Ӧ���ٶ�ϵ�������ı����߼���
    if (g_currentSpeed != 100) {
        double speedFactor = g_currentSpeed / 100.0;
        fakeDelta = static_cast<LONGLONG>(realDelta * speedFactor);
    }

    // ����α��ļ�����ֵ
    g_previousFakeCount.QuadPart += fakeDelta;
    g_previousRealCount = realCount;

    // ����α���ֵ
    *lpPerformanceCount = g_previousFakeCount;

    LeaveCriticalSection(&g_cs);
    return TRUE;
}

BOOL WINAPI HookedQueryPerformanceFrequency(LARGE_INTEGER* lpFrequency) {
    lpFrequency->QuadPart = 1000000;
    return TRUE;
}

DWORD WINAPI HookedGetTickCount(void) {
    EnterCriticalSection(&g_cs);

    static DWORD baseTime = 0;
    static DWORD lastRealTime = 0;

    DWORD realTime = TrueGetTickCount();

    // ��ʼ��
    if (baseTime == 0) {
        baseTime = realTime;
        lastRealTime = realTime;
        LeaveCriticalSection(&g_cs);
        return realTime;
    }

    // ������ʵʱ������������
    DWORD realDelta = realTime - lastRealTime;
    DWORD fakeDelta = static_cast<DWORD>(realDelta * (g_currentSpeed / 100.0));

    baseTime += fakeDelta;
    lastRealTime = realTime;

    LeaveCriticalSection(&g_cs);
    return baseTime;
}

DWORD WINAPI AsmThreadFunctionPlant(LPVOID lpParam) {
    DWORD v_x, v_y, v_plant;
    v_x = g_x;
    v_y = g_y;
    v_plant = g_plant;
    __asm {
        pushad
        mov ecx, [0x755E0C]
        mov ecx, [ecx + 0x868]
        push - 1
        push v_plant
        mov eax, v_y
        push v_x
        push ecx
        mov edx, 0x00418D70
        call edx
        popad
        ret
    };
    return 0;
}

DWORD WINAPI AsmThreadFunctionZombie(LPVOID lpParam) {
    DWORD v_x, v_y, v_zombie;
    v_x = g_x;
    v_y = g_y;
    v_zombie = g_zombie;
    __asm {
        pushad
        mov edx, [0x755E0C]
        mov edx, [edx + 0x868]
        mov edx, [edx + 0x178]
        push v_x
        push v_zombie
        mov eax, v_y
        mov ecx, edx
        mov edx, 0x00435390
        call edx
        popad
        ret
    };
    return 0;
}

DWORD WINAPI MainLoop(LPVOID lpParam) {
    InitGameCheat();
    while (g_status) {
        ClientData v_data;
        DWORD v_bytesRead;
        if (ReadFile(g_client_pipe, &v_data,sizeof(ClientData),&v_bytesRead,NULL)) {
            if (v_bytesRead == sizeof(ClientData)) {
                FuncDispatch(v_data);
            }
        }
    }
    return 0;
}