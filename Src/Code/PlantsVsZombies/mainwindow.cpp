#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "server.h"
#include <QDir>
#include <QMessageBox>

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

    ui->SpeedSlider->setMaximum(5);
    ui->SpeedSlider->setMinimum(1);
}

void MainWindow::InitData(){
    g_global_data->SetStatus(UNINIT);//初始状态
    g_global_data->SetX(0);
    g_global_data->SetY(0);
    g_global_data->SetPlant(0);
    g_global_data->SetZombie(0);
    g_global_data->SetSpeed(1);
}

void MainWindow::InitConnect(){
    connect(g_server,&Server::SendServerMsg,this,&MainWindow::RecServerMsg);
    connect(this,&MainWindow::RequestServerFunc,g_server,&Server::RecRequest);

    connect(ui->InjectAction,&QAction::triggered,this,&MainWindow::InjectDll);
    connect(ui->UnloadAction,&QAction::triggered,this,&MainWindow::UnloadDll);

    connect(ui->YComBox,&QComboBox::currentTextChanged,this,[=](){
        g_global_data->SetY(ui->YComBox->currentIndex());
    });
    connect(ui->XComBox,&QComboBox::currentTextChanged,this,[=](){
        g_global_data->SetX(ui->XComBox->currentIndex());
    });
    connect(ui->PlantsComBox,&QComboBox::currentTextChanged,this,[=](){
        g_global_data->SetPlant(ui->PlantsComBox->currentIndex());
    });
    connect(ui->ZombiesComBox,&QComboBox::currentTextChanged,this,[=](){
        g_global_data->SetZombie(ui->ZombiesComBox->currentIndex());
    });
    connect(ui->SpeedSlider,&QSlider::valueChanged,this,[=](int v_speed){
        g_global_data->SetSpeed(v_speed);
        ui->lspeed->setText(QString::number(v_speed));
    });

    connect(ui->FunBtn_00,&QPushButton::clicked,this,&MainWindow::ServerDispatch);
    connect(ui->FunBtn_01,&QPushButton::clicked,this,&MainWindow::ServerDispatch);
    connect(ui->FunBtn_02,&QPushButton::clicked,this,&MainWindow::ServerDispatch);
    connect(ui->FunBtn_03,&QPushButton::clicked,this,&MainWindow::ServerDispatch);
    connect(ui->FunBtn_04,&QPushButton::clicked,this,&MainWindow::ServerDispatch);
    connect(ui->FunBtn_05,&QPushButton::clicked,this,&MainWindow::ServerDispatch);
    connect(ui->FunBtn_06,&QPushButton::clicked,this,&MainWindow::ServerDispatch);
    connect(ui->FunBtn_07,&QPushButton::clicked,this,&MainWindow::ServerDispatch);
    connect(ui->FunBtn_08,&QPushButton::clicked,this,&MainWindow::ServerDispatch);
    connect(ui->FunBtn_09,&QPushButton::clicked,this,&MainWindow::ServerDispatch);
    connect(ui->FunBtn_10,&QPushButton::clicked,this,&MainWindow::ServerDispatch);
    connect(ui->FunBtn_11,&QPushButton::clicked,this,&MainWindow::ServerDispatch);
    connect(ui->FunBtn_12,&QPushButton::clicked,this,&MainWindow::ServerDispatch);
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
        QMessageBox::warning(nullptr,"警告","选取文件错误");
        return;
    }
    g_global_data->SetDllPath(v_dll_path);
    emit RequestServerFunc(LoadDll);
}

void MainWindow::UnloadDll(){
    //卸载DLL
    if(g_global_data->GetStatus() != LOAD){
        QMessageBox::warning(nullptr,"警告","驱动未加载");
        return;
    }
    g_global_data->SetStatus(UNLOAD);
    emit RequestServerFunc(UnLoadDll);
}

void MainWindow::ServerDispatch(){
    QPushButton* v_clicked_btn = qobject_cast<QPushButton*>(sender());
    if (v_clicked_btn) {
        quint8 v_index = v_clicked_btn->objectName().mid(7).toUInt();
        switch(v_index){
        case 0:{
            emit RequestServerFunc(Sun);
        }break;
        case 1:{
            emit RequestServerFunc(Cold);
        }break;
        case 2:{
            emit RequestServerFunc(Tree);
        }break;
        case 3:{
            emit RequestServerFunc(Gold);
        }break;
        case 4:{
            emit RequestServerFunc(Kill);
        }break;
        case 5:{
            emit RequestServerFunc(Bomb);
        }break;
        case 6:{
            emit RequestServerFunc(PlantsHealth);
        }break;
        case 7:{
            emit RequestServerFunc(ZombiesHealth);
        }break;
        case 8:{
            emit RequestServerFunc(Look);
        }break;
        case 9:{
            emit RequestServerFunc(PlantsSet);
        }break;
        case 10:{
            emit RequestServerFunc(ZombiesSet);
        }break;
        case 11:{
            emit RequestServerFunc(Speed);
        }break;
        case 12:{
            emit RequestServerFunc(Driver);
        }break;
        default:break;
        }
    }
}
