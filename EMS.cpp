#include "workerManager.h"
#include <windows.h>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
// #include <iostream>

// using namespace std;
int main()
{
    WorkerManager wm; // 构造函数并没有进循环，这意味着构造函数只执行一次，即只读入了一次数据
    int choice = 0;
    while (true)
    {

        wm.show_Menu(); // 显示菜单
        cout << "请输入你的选择" << endl;
        cin >> choice;

        while (cin.fail())
        { // 处理输入错误
            cout << "输入类型错误，请重新输入: ";
            cin.clear();            // 清除cin的错误状态
            cin.ignore(1000, '\n'); // 清除输入缓冲区中的字符，直到遇到换行符（这样避免影响到下一次的输入）
            cin >> choice;          // 尝试重新读取输入
        }

        cin.ignore(1000, '\n'); // 清除输入缓冲区中的字符，直到遇到换行符

        switch (choice)
        {
        case 0: // 0,退出
            wm.isToExit();
            break;
        case 1: // 1,增加职工
            wm.add_Emp();
            break;
        case 2: // 2,显示职工
            wm.show_Emp();
            break;
        case 3: // 3,删除职工
            wm.del_Emp();
            break;
        case 4: // 4，修改职工
            wm.mod_Emp();
            break;
        case 5: // 5，查找职工
            wm.find_Emp();
            break;
        case 6: // 6，排序，可升可降
            wm.sort_Emp();
            break;
        case 7: // 7，清空文档，并提供确认服务
            wm.clean_Emp();
            break;
        default:
            cout << "你输入数字的有误，请重新输入" << endl;
            Sleep(2000);
            // system("cls");
            break;
        }
        system("cls");
        system("pause");
    }

    // 测试worker代码
    //  Worker *ptr = NULL;
    //  ptr = new Employee(1, "wangqiang", 1);
    //  ptr->showInfo();
    //  delete ptr;
    //  ptr=new Manager(2,"zhaozi",2);
    //  ptr->showInfo();
    //  delete ptr;
    //  ptr=new Boss(3,"weichunle",3);
    //  ptr->showInfo();
    //  delete ptr;

    return 0;
}