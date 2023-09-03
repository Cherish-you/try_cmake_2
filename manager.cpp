#include "manager.h"

Manager::Manager(int Id,string name,int Dept) {
    m_Id=Id;
    m_name=name;
    m_DeptId=Dept;
}


void Manager:: showInfo() {
    cout<<"职工编号： "<<m_Id
        <<"\t职工姓名: "<<m_name
        <<"\t岗位: "<<getDeptName()
        <<"\t岗位职责: 完成经理的任务"<<endl;
}

string Manager::getDeptName() {
    return string("经理");
}
