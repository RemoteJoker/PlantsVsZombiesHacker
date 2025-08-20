#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <QDir>
#include <QFile>
#include <QString>

enum ControlType{
    LoadDll,//加载库
    UnLoadDll,//卸载库
    Start//启动功能
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
private:
    QString g_dll_path;
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
