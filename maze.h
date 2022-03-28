// 名称：maze.h
// 版权：仅供学习
// 作者：Sean (eppesh@163.com)
// 环境：VS2019;EasyX_20211109
// 时间：03/22/2022
// 说明：迷宫

#ifndef MAZE_H_
#define MAZE_H_

#include <algorithm>
#include <iostream>
#include <stack>
#include <time.h>
#include <vector>

#include <graphics.h>                   // EasyX头文件

namespace the_maze
{
const int kTypePath = 0;                // 路径
const int kTypeWall = 1;                // 障碍物
const int kTypeFlag = 2;                // 是否已遍历过的标志


class Maze
{
public:
    Maze(int size, int wall_size, POINT start = { 0,1 }, POINT end = { 0,0 }); 
    ~Maze();

    std::stack<POINT> SearchByDFS();                     // 采用DFS算法寻找最短路径
    std::vector<std::vector<int>> CreateByDFS();         // 采用DFS算法生成迷宫

private:
    void InitMap();                                     // 初始化地图

private:
    std::vector<std::vector<int>> map_;                 // 地图
    POINT start_;                                       // 迷宫入口和出口位置
    POINT end_;
    int size_;                                          // 地图的行数和列数均为size_
    int wall_size_;                                     // 地图中墙块(正文形)的宽度
};
}   // namespace the_maze

#endif