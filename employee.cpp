#include "employee.h"


 Employee::Employee(int Id,string name,int DeptId)/*:m_Id(Id),m_name(name),DeptId(DeptId)*/ {
    this->m_Id=Id;
    this->m_name=name;
    this->m_DeptId=DeptId;

}


void Employee::showInfo() {
    cout<<"职工编号： "<<m_Id
        <<"\t职工姓名: "<<m_name
        <<"\t岗位: "<<getDeptName()
        <<"\t岗位职责: 完成职工的任务"<<endl;
}


string Employee::getDeptName() {    
    return string("员工");
}