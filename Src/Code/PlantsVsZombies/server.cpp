#include "server.h"
#include <Windows.h>

extern GlobalData* g_global_data;
static HANDLE g_server_pipe;//服务管道
static LPCWSTR g_pipe_name = L"\\\\.\\pipe\\PVZ";//管道名

Server::Server() {
    t_status = true;
    g_server_pipe = CreateNamedPipe(
                g_pipe_name,                     // 管道名称
                PIPE_ACCESS_DUPLEX,              // 双向访问
                PIPE_TYPE_MESSAGE |              // 消息类型管道
                PIPE_READMODE_MESSAGE |          // 消息读模式
                PIPE_NOWAIT,                     // 非阻塞模式
                PIPE_UNLIMITED_INSTANCES,        // 最大实例数
                1024, 1024,                      // 输入输出缓冲区大小
                0,                               // 默认超时时间
                NULL);
}

Server::~Server() {
}

void Server::run(){
    qDebug()<<"等待链接";
    ConnectNamedPipe(g_server_pipe, NULL);
    qDebug()<<"有链接";
    // 读取客户端数据
    while (t_status) {
        ServerData v_data;
        DWORD v_dw_read;
        if (ReadFile(g_server_pipe, &v_data, sizeof(ServerData), &v_dw_read, NULL)) {
            FuncDispatch(v_data);
        }
    }
}

void Server::RecRequest(quint8 v_control_type){
    ClientData v_client_data;
    v_client_data.str_x = g_global_data->GetX();
    v_client_data.str_y = g_global_data->GetY();
    v_client_data.str_plant = g_global_data->GetPlant();
    v_client_data.str_zombie = g_global_data->GetZombie();
    switch (v_control_type) {
    case LoadDll:
    {
        if(Injectdll()){
            emit SendServerMsg(Successful);
        }else{
            emit SendServerMsg(Failed);
        }
    }return;
    case UnLoadDll:
    {
        if(UnloadDll()){
            emit SendServerMsg(Successful);
        }else{
            emit SendServerMsg(Failed);
        }
    }return;
    case Sun:
    {
        v_client_data.str_id = Sun;
    }break;
    case Cold:
    {
        v_client_data.str_id = Cold;
    }break;
    case Tree:
    {
        v_client_data.str_id = Tree;
    }break;
    case Gold:
    {
        v_client_data.str_id = Gold;
    }break;
    case Kill:
    {
        v_client_data.str_id = Kill;
    }break;
    case Bomb:
    {
        v_client_data.str_id = Bomb;
    }break;
    case PlantsHealth:
    {
        v_client_data.str_id = PlantsHealth;
    }break;
    case ZombiesHealth:
    {
        v_client_data.str_id = ZombiesHealth;
    }break;
    case Look:
    {
        v_client_data.str_id = Look;
    }break;
    case PlantsSet:
    {
        v_client_data.str_id = PlantsSet;
    }break;
    case ZombiesSet:
    {
        v_client_data.str_id = ZombiesSet;
    }break;
    case Speed:
    {
        v_client_data.str_id = Speed;
    }break;
    case Driver:
    {
        v_client_data.str_id = Driver;
    }break;
    default:{}break;
    }
    char v_temp_str[sizeof(ClientData)];
    memcpy(v_temp_str,&v_client_data,sizeof(ClientData));
    // 回复客户端
    DWORD v_bytes_read;
    qDebug()<<"写入消息-准备"<<v_temp_str<<sizeof(ClientData);
    WriteFile(g_server_pipe, v_temp_str, sizeof(ClientData), &v_bytes_read, NULL);
    qDebug()<<"写入消息-完成"<<v_bytes_read;
}

void Server::FuncDispatch(ServerData v_data){
    if(v_data.str_result == Successful){
        emit SendServerMsg(Successful);
    }else{
        emit SendServerMsg(Failed);
    }
}

bool Server::Injectdll(){
    HWND v_hwnd = FindWindowA(nullptr,"Plants vs. Zombies");
    //打开窗口失败
    if(nullptr == v_hwnd){
        emit SendServerMsg(Failed);
        return false;
    }
    DWORD v_pid;
    GetWindowThreadProcessId(v_hwnd, &v_pid);
    HANDLE v_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, v_pid);
    //打开进程失败
    if(nullptr == v_handle){
        emit SendServerMsg(Failed);
        return false;
    }
    QByteArray v_byte = g_global_data->GetDllPath().toUtf8();
    const char *v_dll_path = v_byte.constData();
    LPVOID v_remote_mem = VirtualAllocEx(v_handle, nullptr, strlen(v_dll_path) + 1,
                                       MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    //申请内存失败
    if(nullptr == v_remote_mem){
        CloseHandle(v_handle);
        emit SendServerMsg(Failed);
        return false;
    }
    //写入DLL失败
    if (!WriteProcessMemory(v_handle, v_remote_mem, v_dll_path, strlen(v_dll_path) + 1, nullptr)) {
        VirtualFreeEx(v_handle, v_remote_mem, 0, MEM_RELEASE);
        CloseHandle(v_handle);
        emit SendServerMsg(Failed);
        return false;
    }
    LPTHREAD_START_ROUTINE v_load_library = (LPTHREAD_START_ROUTINE)
        GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
    //获取LoadLibrary失败
    if (nullptr == v_load_library) {
        VirtualFreeEx(v_handle, v_remote_mem, 0, MEM_RELEASE);
        CloseHandle(v_handle);
        emit SendServerMsg(Failed);
        return false;
    }
    // 创建远程线程
    HANDLE v_remote_thread = CreateRemoteThread(v_handle, nullptr, 0, v_load_library,
                                              v_remote_mem, 0, nullptr);
    //创建远程线程失败
    if (!v_remote_thread) {
        VirtualFreeEx(v_handle, v_remote_mem, 0, MEM_RELEASE);
        CloseHandle(v_handle);
        emit SendServerMsg(Failed);
        return false;
    }
    // 清理资源
    //VirtualFreeEx(v_handle, v_remote_mem, 0, MEM_RELEASE);
    CloseHandle(v_remote_thread);
    CloseHandle(v_handle);
    return true;
}

bool Server::UnloadDll(){
    return false;
}
