// 名称：迷宫
// 版权：仅供学习
// 作者：Sean (eppesh@163.com)
// 环境：VS2019;EasyX_20211109
// 时间：03/22/2022
// 说明：利用迷宫程序演示DFS等算法

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