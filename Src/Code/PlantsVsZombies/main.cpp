#include "mainwindow.h"
#include "server.h"
#include "Configure.h"
#include <QApplication>

GlobalData* g_global_data = GlobalData::instance();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //读取样式文件
    QFile v_style_file(":/src/style.qss");
    v_style_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString v_str_file = v_style_file.readAll();
    v_style_file.close();
    //启动服务线程
    Server *s = new Server;
    s->start();
    //启动主线程
    MainWindow w(s);
    w.setStyleSheet(v_str_file);
    w.show();
    return a.exec();
}
