#include "maze.h"

namespace the_maze
{
Maze::Maze(int size, int wall_size, POINT start /* =  */, POINT end /* = */)
    : start_(start), end_(end), size_(size), wall_size_(wall_size)
{
    // ��,�ж�����Ϊ����
    size_ = size_ | 1;
    InitMap();

    srand((unsigned int)time(nullptr));
}

Maze::~Maze()
{

}

std::stack<POINT>  Maze::SearchByDFS()
{
    std::vector<std::vector<int>> direction = { {1,0}, {0,1},{-1,0},{0,-1} };   // ������->��->��->��
    std::stack<POINT> path;    // ����ջ

    POINT current_point = start_;
    path.push(current_point);

    while (!path.empty())
    {
        int i = 0;
        for (i = 0; i < 4; ++i)
        {
            // ��ǰ��λ����i������1�����λ�õ�
            int new_point_x = current_point.x + direction[i][0];
            int new_point_y = current_point.y + direction[i][1];
            // ����һ����λ����Path,��Ѹ�Path������
            if (new_point_x >= 0 && new_point_x <= size_ - 1 && new_point_y >= 0 && new_point_y <= size_ - 1
                && map_[new_point_y][new_point_x] == kTypePath)
            {
                map_[current_point.y][current_point.x] = kTypeFlag; // ��ǰ����Ϊͨ·
                current_point.x = new_point_x;
                current_point.y = new_point_y;
                path.push(current_point);
                // ����ǳ���ֱ�ӷ���
                if (current_point.x == end_.x && current_point.y == end_.y)
                {
                    for (auto &row : map_)  // ����ÿһ��
                    {
                        for (auto &col : row)   // ����ÿһ��
                        {
                            if (col == kTypeFlag)
                            {
                                col = kTypePath;
                            }
                        }
                    }
                    return path;
                }
                break;
            }            
        }
        if (i == 4)
        {
            // 4�������߲���ʱ,�ѵ�ǰ���ջ,����־Ϊ���߹�
            map_[current_point.y][current_point.x] = kTypeFlag;
            path.pop();
        }
        if (!path.empty())
        {
            current_point = path.top();
        }
    }
    
    // ��Ҫ���������ı�־�ָ���Path,�����ٴε��ø÷�������������·��
    for (auto &row : map_)  // ����ÿһ��
    {
        for (auto &col : row)   // ����ÿһ��
        {
            if (col == kTypeFlag)
            {
                col = kTypePath;
            }
        }
    }
    return path;
}

std::vector<std::vector<int>> Maze::CreateByDFS()
{
    InitMap();

    std::vector<std::vector<int>> direction = { {1,0}, {0,1},{-1,0},{0,-1} };   // ������->��->��->��
    std::stack<POINT> tools;    // ����ջ

    // �������һ����
    POINT current_point = { (rand() % (size_ - 2) + 1) | 1 ,(rand() % (size_ - 2) + 1) | 1 };
    tools.push(current_point);

    while (!tools.empty())
    {
        // ����ǰ������ΪPath
        if (map_[current_point.y][current_point.x] != kTypePath)
        {
            map_[current_point.y][current_point.x] = kTypePath;
        }

        // ����4������
        std::random_shuffle(direction.begin(), direction.end());
        int i = 0;
        for (i = 0; i < 4; ++i)
        {
            // �ӵ�ǰ��λ����i������2������µ�����
            int new_point_x = current_point.x + 2 * direction[i][0];
            int new_point_y = current_point.y + 2 * direction[i][1];
            // �µ����겻Խ��,��������Wallʱ���µ���ջ;���������м��λ�õ���ΪPath
            if (new_point_x >= 1 && new_point_x <= size_ - 2 && new_point_y >= 1 && new_point_y <= size_ - 2
                && map_[new_point_y][new_point_x] == kTypeWall)
            {
                map_[current_point.y + direction[i][1]][current_point.x + direction[i][0]] = kTypePath;
                current_point.x = new_point_x;
                current_point.y = new_point_y;
                tools.push(current_point);
                break;
            }
        }
        if (i == 4)
        {
            // ��ǰ��4������ǰ��2��������Wall��,�õ��ջ
            tools.pop();
        }
        if (!tools.empty())
        {
            current_point = tools.top();
        }
    }

    return map_;
}


void Maze::InitMap()
{
    // �����ԭ���ĵ�ͼ
    if (!map_.empty())
    {
        for (size_t i = 0; i < map_.size(); ++i)
        {
            map_[i].clear();
        }
        map_.clear();
    }

    // �ٳ�ʼ���µ�ͼ
    for (int row = 0; row < size_; ++row)
    {
        // ��ʼ����ͼ�����е�ΪWall
        map_.push_back(std::vector<int>(size_, kTypeWall));
    }
    end_ = { size_ - 1,size_ - 2 };
    // �������յ�����ΪPath
    // ע��;����Ŀͳһʹ����Ļ����,�����Ͻ�Ϊ(0,0),������x������,������y������
    // ���,����Ϊ(x,y)�ĵ��Ӧ��ά�����еĵ�y��,��x�е�Ԫ��;�ڶ�ά���鸳ֵʱ,
    // ע��Ҫ�ѵ����귴����,��map_[y][x];
    map_[start_.y][start_.x] = kTypePath;
    map_[end_.y][end_.x] = kTypePath;
}

}   // namespace the_maze