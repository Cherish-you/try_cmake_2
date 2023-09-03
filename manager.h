#ifndef MANAGER_H
#define MANAGER_H
#include "worker.h"
class Manager:public Worker {

public:

    Manager(int Id,string name,int Dept);
    void showInfo() override;
    string getDeptName() override;


};


















#endif 