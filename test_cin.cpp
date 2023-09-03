#include <iostream>
#include <limits>
#include <cctype>
using namespace std;
// 目前未找到更好办法使得 不接受字符串的首位作为字符输入
int main()
{

    cout << "请输入一个字符" << endl;
    char ch;
    cin >> ch;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "你输入类型有误，请重新输入" << endl;
        cin >> ch;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // while(!isalpha(ch)||!isdigit(ch)) {
    //     cout<<"你还是输入有误，再给我输"<<'\n';

    // }
    if (isalpha(ch) || isdigit(ch))
    {
        cout << ch << endl;
        char ch_2;
        cin >> ch_2;
        cout << ch_2 << endl;
        return 0;
    }
    else
        main();
}