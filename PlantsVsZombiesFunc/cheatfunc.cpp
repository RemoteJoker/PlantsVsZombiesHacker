#include "cheatfunc.h"

CheatFunc::CheatFunc(QObject *parent)
    : QThread{parent}
{
    g_status = true;
    g_socket = new QLocalSocket();
    g_socket->connectToServer("PVZ");
    connect(g_socket, &QLocalSocket::readyRead, [=]() {
        if (g_socket && g_socket->bytesAvailable() > 0) {
            Core(g_socket->readAll());
        }
    });
}

void CheatFunc::run(){
    while(g_status){}
}

void CheatFunc::Core(QByteArray v_byte_array){
    //处理消息
}
