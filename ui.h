// 名称：ui.h
// 版权：仅供学习
// 作者：Sean (eppesh@163.com)
// 环境：VS2019;EasyX_20211109
// 时间：03/27/2022
// 说明：用于界面等内容的绘制与交互

#ifndef UI_H_
#define UI_H_

#include <chrono>
#include <iostream>
#include <graphics.h>               // EasyX头文件


#include "maze.h"
#include "resource.h"

namespace the_maze
{
class UI
{
public:
    UI(int maze_size = 15, int maze_wall_size = 30);
    ~UI();

    void Run();                     // 监听鼠标和键盘事件
    void Draw();                    // 绘制

    int GetMazeSize();
private:
    void OnEvent(ExMessage msg);
    void Init();
    // 根据图片位置和大小显示图片; color是图片待放置处置的背景颜色
    void ShowImage(IMAGE image, COLORREF color, const int img_width,
        const int img_height, const int dst_x, const int dst_y);
    void DrawMzae(bool is_search_path = false);      // 绘制迷宫;is_search_path表示是否是在搜索最短路径
    void ShowTips(TCHAR *tips);                      // 在底部状态栏显示提示信息

private:
    int maze_region_;                   // 迷宫区域(长=宽)
    int gap_;                           // 迷宫区域与菜单区域之间的缝隙宽
    int menu_widith_;                   // 菜单区域的宽度
    int menu_height_;                   // 菜单区域的高度
    int win_width_;                     // 整个窗体的宽度
    int win_height_;                    // 整个窗体的高度

    //int sensitivity_;                 // 区域灵敏度,指鼠标距离某区域多近时可被感知
    int refresh_x_;                     // refresh 按钮左上角的x坐标
    int refresh_y_;                     // refresh 按钮左上角的y坐标
    int execute_x_;                     // execute 按钮左上角的x坐标
    int execute_y_;                     // execute 按钮左上角的y坐标
    

    IMAGE img_btn_execute_;
    IMAGE img_btn_execute_light_;
    IMAGE img_btn_refresh_;
    IMAGE img_btn_refresh_light_;
    
    // 矩形区域,用于鼠标触发判断
    RECT rect_refresh_;
    RECT rect_execute_;
    RECT rect_refresh_buff_;
    RECT rect_open_;

    Maze *maze_;
    int maze_wall_size_;                // 迷宫中墙块的大小
    int maze_size_;                     // 迷宫地图大小; 迷宫区域大小 = 迷宫地图大小*墙块大小


    bool is_show_path_;                 // 是否绘制最短路径

    std::stack<POINT> paths_;           // 最短路径
    int shortest_paths_;                // 最短路径步数
    std::vector<std::vector<int>> map_; // 地图
};
} // namespace the_maze
#endif 