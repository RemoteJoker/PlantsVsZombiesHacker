#ifndef SERVER_H
#define SERVER_H

#include <QThread>

class Server : public QThread
{
    Q_OBJECT
public:
    Server();
    ~Server();
signals:
    void SendServerMsg(quint8 v_control_result);

public slots:
    void RecRequest(quint8 v_control_type);

protected:
    void run();

private:
    void Core(QByteArray v_byte_array);

private:
    bool t_status;

//关键API
    bool Injectdll();
    bool UnloadDll();
};

#endif // SERVER_H
