#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server.h"
#include "Configure.h"

extern GlobalData* g_global_data;

MainWindow::MainWindow(Server *s, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    g_server = s;

    InitApp();
    InitData();
    InitConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitApp(){
    setWindowTitle("植物大战僵尸辅助器");
    setFixedSize(600,400);
}

void MainWindow::InitData(){
    g_global_data->SetStatus(UNINIT);//初始状态
}

void MainWindow::InitConnect(){
    connect(ui->InjectAction,&QAction::triggered,this,&MainWindow::InjectDll);
    connect(ui->UnloadAction,&QAction::triggered,this,&MainWindow::UnloadDll);
    connect(g_server,&Server::SendServerMsg,this,&MainWindow::RecServerMsg);
    connect(this,&MainWindow::RequestServerFunc,g_server,&Server::RecRequest);
}

void MainWindow::RecServerMsg(quint8 v_control_result){
    switch (v_control_result) {
    case Successful:
    {
        //成功
        QMessageBox::information(nullptr,"提示","操作成功");
    }break;
    case Failed:
    {
        //失败
        QMessageBox::warning(nullptr,"警告","操作失败");
    }break;
    default:
        break;
    }
}

void MainWindow::InjectDll(){
    //注入DLL
    QString v_dll_path = QFileDialog::getOpenFileName(nullptr,"加载库","C:/","(*.dll)");
    if(v_dll_path==""){
        return;
    }
    g_global_data->SetDllPath(v_dll_path);
    emit RequestServerFunc(LoadDll);
}

void MainWindow::UnloadDll(){
    //卸载DLL
    if(g_global_data->GetStatus() != LOAD){
        return;
    }
    g_global_data->SetStatus(UNLOAD);
    emit RequestServerFunc(UnLoadDll);
}
