#ifndef SERVER_H
#define SERVER_H

#include <QThread>
#include "Configure.h"

class Server : public QThread
{
    Q_OBJECT
public:
    Server();
    ~Server();
signals:
    void SendServerMsg(quint8 v_control_result);//发送服务信息

public slots:
    void RecRequest(quint8 v_control_type);//接收请求

protected:
    void run();

private:
    void FuncDispatch(ServerData v_data);//核心函数

private:
    bool t_status;

//关键API
    bool Injectdll();
    bool UnloadDll();
};

#endif // SERVER_H
