#include "maze.h"

namespace the_maze
{
Maze::Maze(int size, int wall_size, POINT start /* =  */, POINT end /* = */)
    : start_(start), end_(end), size_(size), wall_size_(wall_size)
{
    // 行,列都设置为奇数
    size_ = size_ | 1;
    InitMap();

    srand((unsigned int)time(nullptr));
}

Maze::~Maze()
{

}

std::stack<POINT>  Maze::SearchByDFS()
{
    std::vector<std::vector<int>> direction = { {1,0}, {0,1},{-1,0},{0,-1} };   // 方向：右->下->左->上
    std::stack<POINT> path;    // 辅助栈

    POINT current_point = start_;
    path.push(current_point);

    while (!path.empty())
    {
        int i = 0;
        for (i = 0; i < 4; ++i)
        {
            // 当前点位置向i方向走1步后的位置点
            int new_point_x = current_point.x + direction[i][0];
            int new_point_y = current_point.y + direction[i][1];
            // 若下一步的位置是Path,则把该Path存起来
            if (new_point_x >= 0 && new_point_x <= size_ - 1 && new_point_y >= 0 && new_point_y <= size_ - 1
                && map_[new_point_y][new_point_x] == kTypePath)
            {
                map_[current_point.y][current_point.x] = kTypeFlag; // 当前点标记为通路
                current_point.x = new_point_x;
                current_point.y = new_point_y;
                path.push(current_point);
                // 如果是出口直接返回
                if (current_point.x == end_.x && current_point.y == end_.y)
                {
                    for (auto &row : map_)  // 遍历每一行
                    {
                        for (auto &col : row)   // 遍历每一列
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
            // 4个方向都走不动时,把当前点出栈,并标志为已走过
            map_[current_point.y][current_point.x] = kTypeFlag;
            path.pop();
        }
        if (!path.empty())
        {
            current_point = path.top();
        }
    }
    
    // 需要将遍历过的标志恢复成Path,否则再次调用该方法会搜索不到路径
    for (auto &row : map_)  // 遍历每一行
    {
        for (auto &col : row)   // 遍历每一列
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

    std::vector<std::vector<int>> direction = { {1,0}, {0,1},{-1,0},{0,-1} };   // 方向：右->下->左->上
    std::stack<POINT> tools;    // 辅助栈

    // 随机生成一个点
    POINT current_point = { (rand() % (size_ - 2) + 1) | 1 ,(rand() % (size_ - 2) + 1) | 1 };
    tools.push(current_point);

    while (!tools.empty())
    {
        // 将当前点设置为Path
        if (map_[current_point.y][current_point.x] != kTypePath)
        {
            map_[current_point.y][current_point.x] = kTypePath;
        }

        // 遍历4个方向
        std::random_shuffle(direction.begin(), direction.end());
        int i = 0;
        for (i = 0; i < 4; ++i)
        {
            // 从当前点位置向i方向走2步后的新点坐标
            int new_point_x = current_point.x + 2 * direction[i][0];
            int new_point_y = current_point.y + 2 * direction[i][1];
            // 新点坐标不越界,且类型是Wall时把新点入栈;并把两点中间的位置点设为Path
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
            // 当前点4个方向前进2步都不是Wall后,该点出栈
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
    // 先清空原来的地图
    if (!map_.empty())
    {
        for (size_t i = 0; i < map_.size(); ++i)
        {
            map_[i].clear();
        }
        map_.clear();
    }

    // 再初始化新地图
    for (int row = 0; row < size_; ++row)
    {
        // 初始化地图上所有点为Wall
        map_.push_back(std::vector<int>(size_, kTypeWall));
    }
    end_ = { size_ - 1,size_ - 2 };
    // 将起点和终点设置为Path
    // 注意;本项目统一使用屏幕坐标,即左上角为(0,0),向右是x正方向,向下是y正方向
    // 因此,坐标为(x,y)的点对应二维数组中的第y行,第x列的元素;在二维数组赋值时,
    // 注意要把点坐标反过来,即map_[y][x];
    map_[start_.y][start_.x] = kTypePath;
    map_[end_.y][end_.x] = kTypePath;
}

}   // namespace the_maze