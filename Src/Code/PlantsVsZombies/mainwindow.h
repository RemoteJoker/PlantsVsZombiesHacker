#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Server;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Server *s,QWidget *parent = nullptr);
    ~MainWindow();

    void InitApp();//初始化界面
    void InitData();//初始化数据
    void InitConnect();//初始化信号槽

signals:
    void RequestServerFunc(quint8 v_control_type);//请求服务功能

private slots:
    void RecServerMsg(quint8 v_control_result);//接收服务信息

    void InjectDll();//注入DLL
    void UnloadDll();//卸载DLL
    void ServerDispatch();//服务分发

private:
    Ui::MainWindow *ui;
    Server *g_server;//后台服务
};
#endif // MAINWINDOW_H
