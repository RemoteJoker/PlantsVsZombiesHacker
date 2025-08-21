#include "server.h"
#include "Configure.h"
#include <Windows.h>

extern GlobalData* g_global_data;

Server::Server() {
    t_status = true;
    g_local_server = new QLocalServer();
    g_local_socket = new QLocalSocket();
    g_local_server->listen("PVZ");
    connect(g_local_server,&QLocalServer::newConnection,this,[=](){
        if(g_local_server->hasPendingConnections()){
            g_local_socket = g_local_server->nextPendingConnection();
            connect(g_local_socket, &QLocalSocket::readyRead, [=]() {
                if (g_local_socket && g_local_socket->bytesAvailable() > 0) {
                    Core(g_local_socket->readAll());
                }
            });

            // 连接断开信号
            connect(g_local_socket, &QLocalSocket::disconnected, [=]() {
                //"客户端断开连接"
                g_local_socket = nullptr;
                //t_status = false;可反复连接
            });
        }
    });
}

Server::~Server() {
    //
    g_local_socket->deleteLater();
    g_local_server->deleteLater();
}

void Server::run(){
    while(t_status){
        //接收信息
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
    }break;
    case UnLoadDll:
    {
        if(UnloadDll()){
            emit SendServerMsg(Successful);
        }else{
            emit SendServerMsg(Failed);
        }
    }break;
    case Start:
    {
        v_client_data.str_id = Start;
    }break;
    case End:
    {
        v_client_data.str_id = End;
    }break;
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
    char *v_temp_str = nullptr;
    memcpy(v_temp_str,&v_client_data,sizeof(ClientData));
    g_local_socket->write(v_temp_str);
    g_local_socket->flush();
}

void Server::Core(QByteArray v_byte_array){
    char *v_temp_str = v_byte_array.data();
    ServerData *v_server_data = (ServerData*)v_temp_str;
    if(v_server_data->str_result == Successful){
        emit SendServerMsg(Successful);
    }else{
        emit SendServerMsg(Failed);
    }
}

bool Server::Injectdll(){
    HWND v_hwnd = FindWindowA(nullptr,"Plants vs. Zombies");
    //打开窗口失败
    if(!v_hwnd){
        return false;
    }
    DWORD v_pid;
    GetWindowThreadProcessId(v_hwnd, &v_pid);
    HANDLE v_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, v_pid);
    //打开进程失败
    if(!v_handle){
        return false;
    }
    char *v_dll_path = g_global_data->GetDllPath().toLatin1().data();
    LPVOID v_remote_mem = VirtualAllocEx(v_handle, nullptr, strlen(v_dll_path) + 1,
                                       MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    //申请内存失败
    if(!v_remote_mem){
        CloseHandle(v_handle);
        return false;
    }
    //写入DLL失败
    if (!WriteProcessMemory(v_handle, v_remote_mem, v_dll_path, strlen(v_dll_path) + 1, nullptr)) {
        VirtualFreeEx(v_handle, v_remote_mem, 0, MEM_RELEASE);
        CloseHandle(v_handle);
        return false;
    }
    LPTHREAD_START_ROUTINE v_load_library = (LPTHREAD_START_ROUTINE)
        GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
    //获取LoadLibrary失败
    if (!v_load_library) {
        VirtualFreeEx(v_handle, v_remote_mem, 0, MEM_RELEASE);
        CloseHandle(v_handle);
        return false;
    }

    // 创建远程线程
    HANDLE v_remote_thread = CreateRemoteThread(v_handle, nullptr, 0, v_load_library,
                                              v_remote_mem, 0, nullptr);
    //创建远程线程失败
    if (!v_remote_thread) {
        VirtualFreeEx(v_handle, v_remote_mem, 0, MEM_RELEASE);
        CloseHandle(v_handle);
        return false;
    }

    // 等待线程执行完成
    WaitForSingleObject(v_remote_thread, INFINITE);

    // 获取线程退出码检查是否成功
    DWORD v_exit_code;
    GetExitCodeThread(v_remote_thread, &v_exit_code);

    // 清理资源
    VirtualFreeEx(v_handle, v_remote_mem, 0, MEM_RELEASE);
    CloseHandle(v_remote_thread);
    CloseHandle(v_handle);

    if (v_exit_code == 0) {
        return false;
    }
    return true;
}

bool Server::UnloadDll(){
    return false;
}
