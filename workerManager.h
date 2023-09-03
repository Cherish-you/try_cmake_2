#ifndef WORKER_MANAGER_H
#define WORKER_MANAGER_H
#include <iostream>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream>

#define FILENAME "empFile.txt"
using namespace std;
class WorkerManager
{

public:
    WorkerManager();

    void init_EmpNumAndArray(); // 有数据时初始化成员变量
    ~WorkerManager();
    void show_Menu();
    void isToExit();

    void add_Emp();
    void save();

    int m_EmpNum;
    Worker **m_EmpArray;
    // 一个是人数，一个是数组，数据类型是worker*
    bool m_FileIsEmpty;
    // 作为读入数据的辅助，文件是否为空标志，

    // 之后的操作就比较简单了，
    void show_Emp(); // 展示职工信息

    void del_Emp();   // 删除职工信息
    void mod_Emp();   // 修改职工信息
    void find_Emp();  // 查找职工信息
    void sort_Emp();  // 排序职工id
    void clean_Emp(); // 清空文件
};

#endif