// ���ƣ�maze.h
// ��Ȩ������ѧϰ
// ���ߣ�Sean (eppesh@163.com)
// ������VS2019;EasyX_20211109
// ʱ�䣺03/22/2022
// ˵�����Թ�

#ifndef MAZE_H_
#define MAZE_H_

#include <algorithm>
#include <iostream>
#include <stack>
#include <time.h>
#include <vector>

#include <graphics.h>                   // EasyXͷ�ļ�

namespace the_maze
{
const int kTypePath = 0;                // ·��
const int kTypeWall = 1;                // �ϰ���
const int kTypeFlag = 2;                // �Ƿ��ѱ������ı�־


class Maze
{
public:
    Maze(int size, int wall_size, POINT start = { 0,1 }, POINT end = { 0,0 }); 
    ~Maze();

    std::stack<POINT> SearchByDFS();                     // ����DFS�㷨Ѱ�����·��
    std::vector<std::vector<int>> CreateByDFS();         // ����DFS�㷨�����Թ�

private:
    void InitMap();                                     // ��ʼ����ͼ

private:
    std::vector<std::vector<int>> map_;                 // ��ͼ
    POINT start_;                                       // �Թ���ںͳ���λ��
    POINT end_;
    int size_;                                          // ��ͼ��������������Ϊsize_
    int wall_size_;                                     // ��ͼ��ǽ��(������)�Ŀ��
};
}   // namespace the_maze

#endif