// ���ƣ��Թ�
// ��Ȩ������ѧϰ
// ���ߣ�Sean (eppesh@163.com)
// ������VS2019;EasyX_20211109
// ʱ�䣺03/22/2022
// ˵���������Թ�������ʾDFS���㷨

#include <conio.h>
#include <iostream>     // cout, endl
#include <thread>       // thread

#include "ui.h"
#include "maze.h"

using namespace the_maze;

int main()
{
    UI ui;
    ui.Draw();
    std::thread listener_thread(&UI::Run, &ui);

    system("pause");
    closegraph();
    return 0;
}