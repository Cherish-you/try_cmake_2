#ifndef BOSS_H
#define BOSS_H
#include "worker.h"
class Boss:public Worker {

public:

    Boss(int Id,string name,int Dept);
    void showInfo() override;
    string getDeptName() override;


};


#endif