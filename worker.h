#ifndef WORKER_H
#define WORKER_H
#include <iostream>
#include <string>

using namespace std;

class Worker
{

public:
    virtual ~Worker() {}
    virtual void showInfo() = 0;
    virtual string getDeptName() = 0;

    // protected 会导致除派生类之外的访问不到，除非设置相应的set get()
    int m_Id;
    string m_name;
    int m_DeptId;
};

#endif