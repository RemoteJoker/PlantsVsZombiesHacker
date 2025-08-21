#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
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

    void InitApp();
    void InitData();
    void InitConnect();

signals:
    void RequestServerFunc(quint8 v_control_type);

private slots:
    void RecServerMsg(quint8 v_control_result);

    void InjectDll();
    void UnloadDll();
    void StartFunc();
    void EndFunc();
    void ServerDispatch();

private:
    Ui::MainWindow *ui;
    Server *g_server;//后台服务
};
#endif // MAINWINDOW_H
