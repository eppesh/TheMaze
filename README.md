

[toc]

The Maze 是一款迷宫演示程序。

用以演示和应用DFS和BFS算法思路。

Authors: Sean (eppesh@163.com) 

[参考 @[T_eternity 的迷宫算法](https://www.cnblogs.com/teternity/p/MazeAlgorithm.html) ]

# Features

- 自动生成迷宫；
- 给定起点和终点，利用DFS算法找出最短路径；
- TODO：给定起点和终点，利用BFS算法找出最短路径；
- TODO：自动绘制完迷宫后，可以手动通过鼠标修改迷宫（可以创造多个通路来测试是否所产生的路径是最短路径）；
- TODO：利用其他算法生成迷宫、寻找最短路径；

# Documentation

相关文档可通过在线方式查看，或在源码目录下找到。

# Building

目前仅限于Windows平台。

利用`Visual Studio`直接打开源码中的工程文件`.sln`或`.vcxproj`进行编译运行即可；

开发相关：

- `C++`；
- `Visual Studio 2019`; 
- `EasyX 2021`; 

# Usage

- 自动生成迷宫：

  程序运行后会自动生成迷宫，目前只是按DFS方式实现。

- 刷新迷宫：

  点击左侧的“Refresh”按钮可以刷新迷宫。

- 查找最短路径：

  点击左侧的“Start”按钮可以查找当前迷宫的最短路径，并以红色标注出最短路径。

- 显示最短路径长度：

  查找完最短路径后，在底部会显示该最短路径的长度（迷宫中每个小方格记作1个单位）。

- 显示查找最短路径耗时：

  查找完最短路径后，在底部会显示查找最短路径耗时（以毫秒为单位显示，仅作参考）。

# Screenshots

![Pic](https://github.com/eppesh/TheMaze/blob/main/Screenshots.gif)



# Changelogs

- Updated 03/22/2022
  - 新增项目；
- Updated 03/27/2022
  - 完成生成并绘制迷宫，寻找最短路径等主要功能；
- Updated 03/28/2022
  - 完善当前功能；
  - 归档；

# Upcoming Changes

Some of the goals for 2022 are:

- 代码优化；
- 其他功能的实现；

# Postscripts

初衷主要是用于加强对DFS和BFS等算法思想的理解，用一个迷宫小程序作为演示。后续空闲了可能会再添加其他功能（如用其他算法生成迷宫/寻找最短路径）。

# 知识点

- `const int INF = 0x3f3f3f3f`;

  C++中表示无空大时常用`INF`来表示，可设置为上面所示。为何是`0x3f3f3f3f`而不是其他？

  1. `0x3f3f3f3f`的十进制是`1061109567`，也就是`10^9`级别的（和`0x7fffffff`一个数量级），而一般场合下的数据都是小于`10^9`的，所以**它可以作为无穷大使用**而不致出现数据大于无穷大的情形。

  2. 由于一般的数据都不会大于`10^9`，所以当我们把无穷大加上一个数据时，它并**不会溢出**（这就满足了“无穷大加一个有穷的数依然是无穷大”），事实上:

     `0x3f3f3f3f + 0x3f3f3f3f = 2122219134`，这非常大但却没有超过`32-bit int`的表示范围，所以`0x3f3f3f3f`还满足了我们“**无穷大加无穷大还是无穷大**”的需求。

  3. 将**一段内存设置为无穷大**时，只需：`memset(buff, 0x3f, sizeof(buff));`

     我们常用`memset(buff, 0 ,sizeof(buff))`来将内存/数组清0；但将某个数组全部赋值为无穷大时（例如解决图论问题时邻接矩阵的初始化），就不能使用`memset`函数而得自己写循环了，这是因为`memset`是按字节操作的，它能够对数组清零是因为`0`的每个字节都是`0`; 

     如果将无穷大设为`0x3f3f3f3f`，由于`0x3f3f3f3f`的每个字节都是`0x3f`，因此要把一段内存全部置为无穷大，只需要`memset(buff, 0x3f, sizeof(buff))`;

  参考：[CSDN - C++数组初始化&INF的设置](https://blog.csdn.net/ludan_xia/article/details/104818409/); 

- 利用**BFS**第一次走到终点时，这条路径就是最短路径。

  利用**BFS + 队列**寻找走出迷宫的最短路径过程：

  1. 从起点开始，将其加入队列，设置距离为0；
  2. 取出队首的位置点，把从这个位置点能够到达的所有位置点都加入队列（类似遍历树的某一层所有节点），并且让这些位置点的距离设为上一个位置点的距离加1；
  3. 循环步骤2，直到将终点添加到队列中，说明已经找到了路径。

  由于每次处理的位置点所对应的距离是**严格递增**的，因此一旦找到终点，当时的距离就是最短距离；

- 利用**DFS**寻找最短路径时，需要遍历出每一条路径后再取最小的；

- 所有关于EasyX中函数的使用必须在`initgraph()`之后；

- 初始化EasyX的窗体后，可以通过`setbkcolor()`设置默认的背景色，然后要使用`cleardevice()`来使之生效（否则背景色还是默认的黑色）。之后，可以为某个特定区域再设置自己的背景色（先`setlinecolr()`，再`setfillcolor()`，再`fillrectangle()`）。

  ```c++
  initgraph(800, 600);
  setbkcolor(RGB(229, 233, 236));
  cleardevice();
  ```

  
