#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QString>

enum ControlType{
    LoadDll,//加载库
    UnLoadDll,//卸载库
    Sun,
    Cold,
    Tree,
    Gold,
    Kill,
    Bomb,
    PlantsHealth,
    ZombiesHealth,
    Look,
    PlantsSet,
    ZombiesSet,
    Speed,
    Driver
};

enum ControlResult{
    Successful,//成功
    Failed//失败
};

enum GlobalStatus{
    UNINIT,
    LOAD,
    UNLOAD
};

struct ClientData{
    quint8 str_id;
    quint8 str_y;
    quint8 str_x;
    quint8 str_plant;
    quint8 str_zombie;
    ClientData()
        : str_id(0), str_y(0), str_x(0), str_plant(0), str_zombie(0)
    {}
};

struct ServerData{
    quint8 str_result;
};

class GlobalData
{
public:
    void SetDllPath(QString v_dll_path){
        g_dll_path = v_dll_path;
    }
    QString GetDllPath(){
        return g_dll_path;
    }
    void SetStatus(quint8 v_status){
        g_status = v_status;
    }
    quint8 GetStatus(){
        return g_status;
    }
    void SetY(quint8 v_y){
        g_y = v_y;
    }
    quint8 GetY(){
        return g_y;
    }
    void SetX(quint8 v_x){
        g_x = v_x;
    }
    quint8 GetX(){
        return g_x;
    }
    void SetPlant(quint8 v_plant){
        g_plant = v_plant;
    }
    quint8 GetPlant(){
        return g_plant;
    }
    void SetZombie(quint8 v_zombie){
        g_zombie = v_zombie;
    }
    quint8 GetZombie(){
        return g_zombie;
    }
    void SetSpeed(quint8 v_speed){
        g_speed = v_speed;
    }
    quint8 GetSpeed(){
        return g_speed;
    }
private:
    QString g_dll_path;
    quint8 g_y;
    quint8 g_x;
    quint8 g_plant;
    quint8 g_zombie;
    quint8 g_speed;
    quint8 g_status;//全局状态

/*---------------------------*/
public:
    // 删除拷贝构造函数和赋值运算符
    GlobalData(const GlobalData&) = delete;
    GlobalData& operator=(const GlobalData&) = delete;

    // 获取单例实例
    static GlobalData* instance(){
        if (!m_instance) {
            m_instance = new GlobalData();
        }
        return m_instance;
    }

private:
    // 私有构造函数
    explicit GlobalData(){}
    ~GlobalData(){}

    // 单例实例指针
    static GlobalData* m_instance;
};

#endif // CONFIGURE_H
