#include "server.h"
#include "Configure.h"

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
                qDebug() << "客户端断开连接";
                g_local_socket->deleteLater();
                g_local_socket = nullptr;
                t_status = false;
            });
        }
    });
}

Server::~Server() {
    //
}

void Server::run(){
    while(t_status){
        //接收信息
    }
}

void Server::RecRequest(quint8 v_control_type){
    switch (v_control_type) {
    case LoadDll:
    {}break;
    case UnLoadDll:
    {}break;
    case Start:
    {}break;
    default:
        break;
    }
}

void Server::Core(QByteArray v_byte_array){}
