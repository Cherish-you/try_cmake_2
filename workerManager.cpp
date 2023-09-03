#include "workerManager.h"
// 对于需要读写文件实现数据存储的，读的情况就这三种
WorkerManager::WorkerManager()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    // 文件不存在的情况
    if (!ifs.is_open())
    {
        // cout << "文件不存在" << endl;//测试代码
        // 初始化指针，数组长度为0，文件不存在，当然也是空；
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FileIsEmpty = 1;
        ifs.close();
        return;
    }
    // 文件存在但是为空
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        // cout << "文件为空" << endl;//测试代码
        // 初始化指针，数组长度为0，文件不存在，当然也是空；
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FileIsEmpty = 1;
        ifs.close();
        return;
    }
    // 文件存在且有数据，为了方便维护，我们写成员函数来拿到m_EmpNum,m_EmpArray
    cout << "这是有数据的一种" << endl;
    ifs.close(); // 关掉开始的ifs,这里应该是一个open,一个close
    init_EmpNumAndArray();
}

// 堆区的指针数组的内存释放
WorkerManager::~WorkerManager()
{
    if (this->m_EmpArray != NULL)
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            delete this->m_EmpArray[i];
            this->m_EmpArray[i] = NULL; // 理论上删除 +  =null 是最安全的
        }
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}
// 菜单页面的打印
void WorkerManager::show_Menu()
{

    cout << "*******************************************" << endl;
    cout << "**********  欢迎使用职工管理系统！ **********" << endl;
    cout << "************* 0.退出管理系统   *************" << endl;
    cout << "************* 1.增加职工信息   *************" << endl;
    cout << "************* 2.显示职工信息   *************" << endl;
    cout << "************* 3.删除离职职工   *************" << endl;
    cout << "************* 4.修改职工信息   *************" << endl;
    cout << "************* 5.查找职工信息   *************" << endl;
    cout << "************* 6.按照编号排序   *************" << endl;
    cout << "************* 7.清空所有文档   *************" << endl;
    cout << "*******************************************" << endl;
    cout << endl; // 表示空一行
}
// 退出，使用的是exit（）
void WorkerManager::isToExit()
{
    cout << "请确定你的选择，是(1)/否(0)" << endl;
    int temp;
    cin >> temp;
    if (temp)
    {
        exit(0);
    }
}

// 添加职工 知识点是对传统数组的扩容操作 确定大小 开辟新的内存 将原数据+新增数据放进去 删除原数组内存
void WorkerManager::add_Emp()
{
    cout << "请输入添加人数：" << endl;
    int addNum = 0;
    cin >> addNum;
    if (addNum > 0)
    {
        int newSize = this->m_EmpNum + addNum;     // 临时变量，记录现在的人数
        Worker **newSpace = new Worker *[newSize]; // 数组中的数据先解决去处，才能释放原有的位置
        if (this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                newSpace[i] = *(this->m_EmpArray + i); //*(this->m+i)=this->m[i]
            }
        }
        int temp_id;           // 编号
        string temp_name;      // 姓名
        int temp_dept;         // 职位类型编号
        Worker *worker = NULL; // 这些量的值在循环中不断改变，但变量并没有变，所以声明在了外头
        // 以下输入皆没有检验是否合规，有时间再优化
        for (int i = 0; i < addNum; i++)
        {
            cout << "请输入第 " << i + 1 << "位的编号" << endl;
            cin >> temp_id;
            cout << "请输入第 " << i + 1 << "位的姓名" << endl;
            cin >> temp_name;
            cout << "请输入第 " << i + 1 << "位的职位编号 " << '\n'
                 << "1.职工 " << '\n'
                 << "2.经理 " << '\n'
                 << "3.老板" << endl;
            cin >> temp_dept;
            switch (temp_dept)
            {
            case 1:
                worker = new Employee(temp_id, temp_name, temp_dept);
                break;
            case 2:
                worker = new Manager(temp_id, temp_name, temp_dept);
                break;
            case 3:
                worker = new Boss(temp_id, temp_name, temp_dept);
                break;
            default:
                cout << "没有这个职位" << endl;
                i = i - 1;
                break;
            }
            newSpace[i + this->m_EmpNum] = worker;
            // delete worker; // 有疑问是否要加，经测试加上会导致无法写入
        }
        delete[] m_EmpArray;         // 释放之前的数组内存
        this->m_EmpNum = newSize;    // 更新成员变量，数量
        this->m_EmpArray = newSpace; // 更新现在的首地址，使新数组的地址指向成员变量
        this->m_FileIsEmpty = 0;     // 新增加的成员变量，也需要更新；
        cout << "添加成功" << addNum << "个人" << endl;
        this->save();
    }
    // delete一定是对应着new ,而且是释放指针指向的内存，指针还在指着这片内存，但操作会产生不可控行为，最好ptr=nullptr; 这样才悬空
    //  newSpace不能释放，如果释放会导致成员变量指针指向无效，出现上述情况    对这两种，析构函数最终完成了这个释放的任务
    // 同理worker与数组数据（worker *）指向一致
    else
    {
        cout << "输入有误" << endl;
    }
}

// 知识点：程序写入文件的操作：保存到文件中
void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);
    for (int i = 0; i < m_EmpNum; i++)
    {
        // ofs<<m_EmpArray[i]->showInfo(); ofs不能接受这样的写入
        ofs << m_EmpArray[i]->m_Id << " "
            << m_EmpArray[i]->m_name << " "
            << m_EmpArray[i]->m_DeptId << endl; // return的东西是可以通过ofs写入的

        m_EmpArray[i]->showInfo(); // 测试代码，用到了多态
    }
    ofs.close();
}

// 用于构造函数的第三种初始化，读入文件的操作
void WorkerManager::init_EmpNumAndArray()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int temp_id;
    string temp_name;
    int temp_deptId;
    // Worker *worker=NULL;
    int num = 0;
    // 怎么写出去的，要对应着怎么写回来，153行
    while (ifs >> temp_id && ifs >> temp_name && ifs >> temp_deptId) // ifs 与cin 读数据以空格，换行分隔
    {
        num++;
    }
    this->m_EmpNum = num;
    ifs.close(); // 一个ifs读完文件之后是不可以在重复读的，要新建对象
    Worker **worker = new Worker *[this->m_EmpNum];
    int temp = 0; // temp+while 起到了for 遍历数组的作用
    ifstream ifs_;
    ifs_.open(FILENAME, ios::in);
    ifs_.seekg(0); //// 以防意外，将文件读取位置设置为文件开头
    while (ifs_ >> temp_id && ifs_ >> temp_name && ifs_ >> temp_deptId)
    {
        switch (temp_deptId)
        {
        case 1:
            worker[temp] = new Employee(temp_id, temp_name, temp_deptId);
            break;
        case 2:
            worker[temp] = new Manager(temp_id, temp_name, temp_deptId);
            break;
        case 3:
            worker[temp] = new Boss(temp_id, temp_name, temp_deptId);
            break;
        default:
            cout << "没有这个职位" << endl;
            break;
        }
        temp++;
    }
    // cout << "职工人数为：" << this->m_EmpNum << endl; // 测试代码
    this->m_EmpArray = worker;
    this->m_FileIsEmpty = 0; // 完成了初始化
    // show_Emp();              // 用于测试，人为断点debug,程序跑到这里停了，说明这里有问题
    ifs_.close();
}

// 用于展示职工 传统数组指针的遍历
void WorkerManager::show_Emp()
{
    if (m_FileIsEmpty)
    {
        cout << "目前还没有职工" << endl;
    }
    else
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            this->m_EmpArray[i]->showInfo();
        }
    system("pause");
}

// 删除职工  传统数组无法做到动态删除，后面没用到的内存只能等整个数组一起释放
void WorkerManager::del_Emp()
{
    if (m_FileIsEmpty)
    {
        cout << "文件没有员工信息，不能删" << endl;
    }
    else
    {
        int id;
        cout << "请输入你要删除职工的编号" << endl;
        cin >> id;
        for (int i = 0; i < m_EmpNum; i++)
        {
            if (m_EmpArray[i]->m_Id == id)
            {
                int is;
                cout << "请确认你的操作:是(1),否(0)" << endl;
                cin >> is;
                if (is)
                {
                    // 思路：把这个位置的数据拿掉，把后面数据补上来,最后面的虽然暂时不能释放，但等下次再重新开辟时就能一起释放
                    for (int j = i; j < m_EmpNum - 1; j++)
                    { // 再次强调，不知道写什么就举个小数验算一下
                        m_EmpArray[j] = m_EmpArray[j + 1];
                    }
                    m_EmpNum = m_EmpNum - 1;
                    this->save();
                    cout << "删除成功" << endl;
                    break;
                }
                else
                    break;
            }
            else
                cout << "你输入的编号有误" << endl;
            break;
        }
    }
    system("pause");
    system("cls");
}

void WorkerManager::mod_Emp()
{
    if (m_FileIsEmpty)
    {
        cout << "文件没有员工信息，不能修改" << endl;
    }
    else
    {
        int id;
        cout << "请输入你要修改职工的编号" << endl;
        cin >> id;
        for (int i = 0; i < m_EmpNum; i++)
        {
            if (m_EmpArray[i]->m_Id == id)
            {

                // 思路：把这个数组数据（worker *）更改指向即可
                int newId;
                string newName;
                int newDeptId;
                cout << "请输入他的新编号" << endl;
                cin >> newId;
                cout << "请输入他的新名字" << endl;
                cin >> newName;
                cout << "请输入他的新职位编号" << endl;
                cin >> newDeptId;
                // m_EmpArray[i]->m_Id=newId;
                // m_EmpArray[i]->m_name=newName;
                // m_EmpArray[i]->m_DeptId=newDeptId;//这样会导致worker* 没有明确的指向哪一个派生类

                delete m_EmpArray[i];
                Worker *worker = NULL;
                switch (newDeptId)
                {
                case 1:
                    worker = new Employee(newId, newName, newDeptId);
                    break;
                case 2:
                    worker = new Manager(newId, newName, newDeptId);
                    ;
                    break;
                case 3:
                    worker = new Boss(newId, newName, newDeptId);
                    ;
                    break;
                default:
                    cout << "没有这个职位" << endl;
                    break;
                }
                m_EmpArray[i] = worker;
                cout << "修改成功" << endl;
                this->save();
                break;
            }
            else
                cout << "你输入的编号有误" << endl;
            break;
        }
    }
    system("pause");
    system("cls");
}

void WorkerManager::find_Emp()
{
    if (!m_FileIsEmpty)
    {
        cout << "请输入你要查找的人,按编号(1),按姓名(0)" << endl;
        bool isId;
        cin >> isId;
        if (isId)
        {
            cout << "请输入你要查找的编号" << endl;
            int temp_Id;
            cin >> temp_Id;
            for (int i = 0; i < m_EmpNum; i++)
            {
                if (this->m_EmpArray[i]->m_Id == temp_Id)
                {
                    // 进行查找工作
                    cout << "存在该职工，这个人的信息是: " << endl;
                    this->m_EmpArray[i]->showInfo();
                    system("pause");
                    break;
                }
                else
                {
                    cout << "不存在这个人" << endl;
                    system("pause");
                    break;
                }
            }
        }
        else
        {
            cout << "请输入你要查找的姓名" << endl;
            string temp_name;
            cin >> temp_name;
            for (int i = 0; i < m_EmpNum; i++)
            {
                if (this->m_EmpArray[i]->m_name == temp_name)
                {
                    // 进行查找工作
                    cout << "存在该职工，这个人的信息是: " << endl;
                    this->m_EmpArray[i]->showInfo();
                    system("pause");
                    break;
                }
                else
                {
                    cout << "不存在这个人" << endl;
                    system("pause");
                    break;
                }
            }
        }
    }
    else
    {
        cout << "文件为空" << endl;
        system("pause");
    }
}

// 冒泡和选择，  多重循环，是一层一层逐渐思考的过程，一层后发现又构成重复，就有了下一层
void WorkerManager::sort_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件为空，没有职工，无法排序" << endl;
    }
    else
    {
        cout << "请选择正向排序(1)和倒向排序(0)" << endl;
        bool ch;
        cin >> ch;
        if (ch)
        {
            // 正向排序 循环都是一点一点补充，写成的  思路：随着排序进行，后面的循环比较次数会越来越少,冒泡
            for (int i = 0; i < m_EmpNum - 1; i++)
            {
                for (int j = 0; j < m_EmpNum - 1 - i; j++)
                {
                    if (m_EmpArray[j]->m_Id > m_EmpArray[j + 1]->m_Id)
                    {
                        Worker *temp = NULL;
                        temp = m_EmpArray[j];
                        m_EmpArray[j] = m_EmpArray[j + 1];
                        m_EmpArray[j + 1] = temp;
                    }
                }
            }
            this->save();
            // for(int i=0;i<m_EmpNum-2;i++) {

            // }
            // //最后一次是i=0;i<m_EMpNum-(m_EmpNum-1);i++
        }
        else
        { // 倒向排序   尝试一下选择排序 人为认为最大的就是每次的第一个
            for (int i = 0; i < m_EmpNum; i++)
            {
                int max = i;
                for (int j = i + 1; j < m_EmpNum; j++)
                {
                    if (m_EmpArray[max]->m_Id < m_EmpArray[j]->m_Id)
                    {
                        max = j;
                    }
                }
                if (max != i)
                {
                    Worker *worker = NULL;
                    worker = m_EmpArray[i];
                    m_EmpArray[i] = m_EmpArray[max];
                    m_EmpArray[max] = worker;
                }
            }
            this->save();
        }
        system("pause");
    }
}

//这个提示你写程序时要注意考虑全面 多用判断语句
void WorkerManager::clean_Emp()
{
    cout << "请确定你的操作：yes(1),no(0)" << endl;
    bool isClean;
    cin >> isClean;
    if (isClean)
    {
        ofstream ofs(FILENAME, ios::trunc); // 这个模式如果存在文件就删除重新创建新的，之后不往里写=清空
        ofs.close();                        // 文件清空操作，接下来是程序内清空
        if (!this->m_FileIsEmpty)
        {
            for (int i = 0; i < m_EmpNum; i++)
            {
                delete m_EmpArray[i];
            }
            delete[] m_EmpArray;
            m_EmpNum = 0;
            m_EmpArray = NULL;
            m_FileIsEmpty = true; // 重新初始化成员变量
            cout << "清空成功" << endl;
        }
        else
            cout << "文件本来就是空的，不需要清空" << endl;
        system("pause");
    }
    else
        return;
}