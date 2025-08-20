#ifndef CHEATFUNC_H
#define CHEATFUNC_H

#include <QThread>
#include <QLocalSocket>
class CheatFunc : public QThread
{
    Q_OBJECT
public:
    explicit CheatFunc(QObject *parent = nullptr);

private:
    void Core(QByteArray v_byte_array);

protected:
    void run();

private:
    bool g_status;
    QLocalSocket *g_socket;
};

#endif // CHEATFUNC_H
