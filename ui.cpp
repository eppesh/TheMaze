#include "ui.h"

namespace the_maze
{
UI::UI(int maze_size /* = 15 */, int maze_wall_size /* = 30 */) :
    maze_size_(maze_size), maze_wall_size_(maze_wall_size), is_show_path_(false), shortest_paths_(0)
{
    maze_size_ |= 1;    // 保持为奇数
    maze_region_ = maze_size_ * maze_wall_size_;
    gap_ = maze_wall_size_ * 2; // 30
    menu_widith_ = maze_region_ / 2; // 200;
    menu_height_ = maze_region_ + 2 * gap_;
    win_width_ = menu_widith_ + 2 * gap_ + maze_region_;
    win_height_ = menu_height_ + gap_;

    //sensitivity_ = 4;   // 为了实现鼠标靠近按钮时,按钮变亮的效果
    
    maze_ = new Maze(maze_size_, maze_wall_size_);
}

UI::~UI()
{
    if (maze_ != nullptr)
    {
        delete maze_;
        maze_ = nullptr;
    }
    closegraph();    
}

void UI::Run()
{
    ExMessage message;
    while (true)
    {
        message = getmessage(EM_MOUSE | EM_KEY);
        OnEvent(message);
        Sleep(10);
    }
}

void UI::Draw()
{
    Init();
    
    // 绘制主窗体    
    initgraph(win_width_, win_height_/*, EW_SHOWCONSOLE*/);
    setbkcolor(WHITE);
    cleardevice();
    
    // 分割线
    setlinecolor(LIGHTGRAY);
    line(0, 0, win_width_, 0);
    line(menu_widith_, 0, menu_widith_, menu_height_);
    line(0, menu_height_, win_width_, menu_height_);

    // 左侧菜单区域 {0, 0, menu_widith_, menu_height_}
    settextcolor(RGB(253, 84, 78));
    outtextxy(refresh_x_ - gap_, refresh_y_ - gap_ / 2, _T("Refresh the maze map:"));
    ShowImage(img_btn_refresh_, WHITE, img_btn_refresh_.getwidth(),
        img_btn_refresh_.getheight(), refresh_x_, refresh_y_);
    outtextxy(execute_x_ - gap_, execute_y_ - gap_ / 2, _T("Search for paths:"));
    ShowImage(img_btn_execute_, WHITE, img_btn_execute_.getwidth(),
        img_btn_execute_.getheight(), execute_x_, execute_y_);
    

    // 右侧迷宫区域 {menu_widith_ + gap_, gap_, menu_widith_ + gap_ + maze_size_, gap_ + maze_size_}
    DrawMzae();

    // 底部状态区域 {0, menu_height_, win_width_, menu_height_ + gap_}
}

int UI::GetMazeSize()
{
    return maze_region_;
}

// 判断圆形是否有触发
bool IsTrigger(RECT rectangle, POINT point)
{
    if (PtInRect(&rectangle, point))
    {
        // 圆心坐标(前提是已知按钮)
        int radius = (rectangle.right - rectangle.left) / 2;
        int x = rectangle.left + radius;
        int y = rectangle.top + radius;
        int distance = (x - point.x) * (x - point.x) + (y - point.y) * (y - point.y);
        return (distance <= (radius * radius));
    }
    return false;
}


void UI::OnEvent(ExMessage msg)
{
    //setorigin(0, 23);
    POINT mouse = { msg.x,msg.y };                  // 鼠标当前坐标
    

    switch (msg.message)
    {
    case WM_LBUTTONDOWN:
    {
        // 地图刷新
        if (PtInRect(&rect_refresh_, mouse))
        {
            ShowImage(img_btn_refresh_light_, WHITE, img_btn_refresh_light_.getwidth(),
                img_btn_refresh_light_.getheight(), refresh_x_, refresh_y_);
            DrawMzae();
            is_show_path_ = !is_show_path_;
        }
        else if (PtInRect(&rect_execute_, mouse))
        {
            ShowImage(img_btn_execute_light_, WHITE, img_btn_execute_.getwidth(),
                img_btn_execute_.getheight(), execute_x_, execute_y_);
            is_show_path_ = !is_show_path_;

            auto start_time = std::chrono::steady_clock::now();
            DrawMzae(true);
            auto end_time = std::chrono::steady_clock::now();
            auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
            TCHAR tips[128] = { 0 };
            _stprintf_s(tips, _T(" The shortest paths: %d steps. The elapsed time is: %lld milliseconds."), shortest_paths_, elapsed_time);
            
            ShowTips(tips);

        }
                
        break;
    }
    case WM_LBUTTONUP:
    {        
        if (PtInRect(&rect_refresh_, mouse))
        {
            ShowImage(img_btn_refresh_, WHITE, img_btn_refresh_.getwidth(),
                img_btn_refresh_.getheight(), refresh_x_, refresh_y_);
        }
        else if (PtInRect(&rect_execute_, mouse))
        {
            ShowImage(img_btn_execute_, WHITE, img_btn_execute_.getwidth(),
                img_btn_execute_.getheight(), execute_x_, execute_y_);
        }
        break;
    }
    case WM_MOUSEMOVE:
    {
        break;
    }
    case  WM_KEYDOWN:
    {
        if (msg.vkcode == VK_ESCAPE)
        {
            closegraph();
            exit(0);
        }
        break;
    }
    default:
        break;
    }
}

// 为了更好地显示图片,先清除该位置上的原有内容再将图片背景设置为透明后,才显示图片
void UI::ShowImage(IMAGE image, COLORREF color, const int img_width, const int img_height, const int dst_x, const int dst_y)
{
    // 先清除掉原位置上的图片再放置,避免出现图片重影
    setfillcolor(color);
    setlinecolor(color);
    fillrectangle(dst_x, dst_y, dst_x + img_width, dst_y + img_height);

    // 将图片背景设置为透明并显示图片
    IMAGE mask(img_width, img_height);
    DWORD *p_memory_close = GetImageBuffer(&image);
    DWORD *p_memory_mask = GetImageBuffer(&mask);
    COLORREF mask_background = p_memory_close[0];
    for (int i = 0; i < img_width * img_height; ++i)
    {
        if (p_memory_close[i] <= 0x555555 && p_memory_close[i] >= 0)  // 0x555555 是深灰色
        {
            p_memory_mask[i] = WHITE;
        }
        else
        {
            p_memory_mask[i] = BLACK;
        }
    }
    BeginBatchDraw();
    putimage(dst_x, dst_y, &mask, SRCAND);
    putimage(dst_x, dst_y, &image, SRCPAINT);
    FlushBatchDraw();
    EndBatchDraw();
}

void UI::Init()
{
    loadimage(&img_btn_execute_, _T("PNG"), MAKEINTRESOURCE(IDB_EXECUTE));
    loadimage(&img_btn_execute_light_, _T("PNG"), MAKEINTRESOURCE(IDB_EXECUTE_LIGHT));
    loadimage(&img_btn_refresh_, _T("PNG"), MAKEINTRESOURCE(IDB_REFRESH));
    loadimage(&img_btn_refresh_light_, _T("PNG"), MAKEINTRESOURCE(IDB_REFRESH_LIGHT));
    

    refresh_x_ = menu_widith_ / 2 - img_btn_refresh_.getwidth() / 2;
    refresh_y_ = menu_height_ * 2 / 9;
    execute_x_ = menu_widith_ / 2 - img_btn_refresh_.getwidth() / 2;
    execute_y_ = menu_height_ * 4 / 9;

    rect_refresh_ = { refresh_x_, refresh_y_,
    menu_widith_ / 2 + img_btn_refresh_.getwidth() / 2, refresh_y_ + img_btn_refresh_.getheight() };
    /*rect_refresh_buff_ = { refresh_x_ + sensitivity_, refresh_y_ + sensitivity_,
    menu_widith_ / 2 + img_btn_refresh_.getwidth() / 2 + sensitivity_, refresh_y_ + img_btn_refresh_.getheight() + sensitivity_ };*/

    rect_execute_ = { execute_x_, execute_y_,
    menu_widith_ / 2 + img_btn_execute_.getwidth() / 2, execute_y_ + img_btn_execute_.getheight() };

}

void UI::DrawMzae(bool is_search_path /* = false */)
{
    // 将坐标原点设置到迷宫区域左上角
    setorigin(menu_widith_ + gap_, gap_);

    // 清空原来迷宫区域的内容
    setfillcolor(WHITE);
    fillrectangle(0, 0, maze_region_, maze_region_);
    
    if (is_search_path)
    {
        paths_ = maze_->SearchByDFS();
        shortest_paths_ = paths_.size();
    }
    else
    {
        // 生成新地图并绘制
        map_ = maze_->CreateByDFS();
    }

    // 绘制迷宫
    setlinecolor(DARKGRAY);
    setfillcolor(LIGHTGRAY);
    int tmp = 0;
    for (int i = 0; i < maze_size_; ++i)
    {
        for (int j = 0; j < maze_size_; ++j)
        {
            if (map_[i][j] == kTypeWall)
            {
                fillrectangle(j * maze_wall_size_, i * maze_wall_size_,
                    j * maze_wall_size_ + maze_wall_size_ - 1,
                    i * maze_wall_size_ + maze_wall_size_ - 1);
            }
        }
    }
    if (is_show_path_)
    {
        while (!paths_.empty())
        {
            auto path = paths_.top();
            setfillcolor(RGB(244, 96, 108));
            fillrectangle(path.x * maze_wall_size_, path.y * maze_wall_size_,
                path.x * maze_wall_size_ + maze_wall_size_ - 1,
                path.y * maze_wall_size_ + maze_wall_size_ - 1);
            paths_.pop();
        }
    }
    // 恢复原来的坐标原点
    setorigin(0, 0);
}

void UI::ShowTips(TCHAR *tips)
{
    // 底部状态区域 {0, menu_height_, win_width_, menu_height_ + gap_}
    // 先清空原有内容
    setfillcolor(WHITE);
    fillrectangle(0, menu_height_, win_width_, menu_height_ + gap_);

    // 再显示提示信息
    RECT show_region = { 2, menu_height_, win_width_, menu_height_ + gap_ };
    drawtext(tips, &show_region, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
}


}// namespace the_maze