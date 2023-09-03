#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "worker.h"

class Employee:public Worker {

public:
    Employee(int Id,string name,int DeptId);
    void showInfo() override;
    virtual string getDeptName();


};

















#endif