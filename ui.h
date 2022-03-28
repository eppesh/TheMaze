// ���ƣ�ui.h
// ��Ȩ������ѧϰ
// ���ߣ�Sean (eppesh@163.com)
// ������VS2019;EasyX_20211109
// ʱ�䣺03/27/2022
// ˵�������ڽ�������ݵĻ����뽻��

#ifndef UI_H_
#define UI_H_

#include <chrono>
#include <iostream>
#include <graphics.h>               // EasyXͷ�ļ�


#include "maze.h"
#include "resource.h"

namespace the_maze
{
class UI
{
public:
    UI(int maze_size = 15, int maze_wall_size = 30);
    ~UI();

    void Run();                     // �������ͼ����¼�
    void Draw();                    // ����

    int GetMazeSize();
private:
    void OnEvent(ExMessage msg);
    void Init();
    // ����ͼƬλ�úʹ�С��ʾͼƬ; color��ͼƬ�����ô��õı�����ɫ
    void ShowImage(IMAGE image, COLORREF color, const int img_width,
        const int img_height, const int dst_x, const int dst_y);
    void DrawMzae(bool is_search_path = false);      // �����Թ�;is_search_path��ʾ�Ƿ������������·��
    void ShowTips(TCHAR *tips);                      // �ڵײ�״̬����ʾ��ʾ��Ϣ

private:
    int maze_region_;                   // �Թ�����(��=��)
    int gap_;                           // �Թ�������˵�����֮��ķ�϶��
    int menu_widith_;                   // �˵�����Ŀ��
    int menu_height_;                   // �˵�����ĸ߶�
    int win_width_;                     // ��������Ŀ��
    int win_height_;                    // ��������ĸ߶�

    //int sensitivity_;                 // ����������,ָ������ĳ������ʱ�ɱ���֪
    int refresh_x_;                     // refresh ��ť���Ͻǵ�x����
    int refresh_y_;                     // refresh ��ť���Ͻǵ�y����
    int execute_x_;                     // execute ��ť���Ͻǵ�x����
    int execute_y_;                     // execute ��ť���Ͻǵ�y����
    

    IMAGE img_btn_execute_;
    IMAGE img_btn_execute_light_;
    IMAGE img_btn_refresh_;
    IMAGE img_btn_refresh_light_;
    
    // ��������,������괥���ж�
    RECT rect_refresh_;
    RECT rect_execute_;
    RECT rect_refresh_buff_;
    RECT rect_open_;

    Maze *maze_;
    int maze_wall_size_;                // �Թ���ǽ��Ĵ�С
    int maze_size_;                     // �Թ���ͼ��С; �Թ������С = �Թ���ͼ��С*ǽ���С


    bool is_show_path_;                 // �Ƿ�������·��

    std::stack<POINT> paths_;           // ���·��
    int shortest_paths_;                // ���·������
    std::vector<std::vector<int>> map_; // ��ͼ
};
} // namespace the_maze
#endif 