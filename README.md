# AStar · 寻路算法与可视化实验

一个基于 C++ 和 HGE 1.81 的 Windows 寻路实验项目。把多种搜索算法放在同一套网格地图中，观察搜索过程、最终路径、路径代价和运行耗时。

代码保留于 2013 年，适合阅读早期寻路实现和不同开放列表组织方式。界面中的计时是演示数据，不是经过严格控制的性能基准。

## 包含的算法

- A*：基础版本、二叉堆版本、插入排序版本，以及插入排序结合二分查找的版本。
- Dijkstra。
- BFS、DFS，以及名为 `BFS_Priority` 的优先队列实验实现。
- 公共网格、节点和二叉堆辅助代码。

地图包含无障碍、一般障碍、不同移动消耗、内凹障碍和迷宫等情形。程序可以选择多种算法，在窗口中绘制搜索记录和路径。

## 代码入口

```text
algorithm_test/algorithm_test.sln    # Visual Studio 解决方案
algorithm_test/algorithm_test/
├── main.cpp                        # 程序入口
├── Application.cpp / .h            # 配置、地图生成、运行和显示
├── AStar*.cpp / .h                 # A* 的不同实现
├── Dijkstra.cpp / .h
├── BFS*.cpp / .h
├── DFS.cpp / .h
├── BinaryHeap.h                    # 二叉堆
└── utily.cpp / .h                  # 公共节点和算法辅助逻辑
hge/hge181/                         # HGE 头文件、库和运行时文件
```

## 构建与运行准备

1. 在 Windows 下打开 `algorithm_test/algorithm_test.sln`。解决方案使用 Visual Studio 2010 格式，提供 `Debug|Win32` 和 `Release|Win32` 配置。
2. 检查 HGE 的头文件和库路径。Debug 使用仓库内的相对路径；Release 仍写着原开发环境的 `D:\hge181`，需要改为实际路径。
3. 链接依赖为 `hge.lib` 和 `hgehelp.lib`。运行时需要能找到仓库中的 `hge.dll`、`bass.dll`。
4. 程序会从工作目录读取 `font1.fnt`，但仓库没有收录该字体及其配套纹理，需要自行补齐兼容的 HGE 字体资源。

使用新版 Visual Studio 时可能还需处理旧工具链与预编译库的兼容问题。本次文档整理没有重新编译或运行程序。

## 配置与操作

程序从工作目录中的 `config.ini` 读取设置，具体字段以 `Application::readIni()` 为准：

- `[Start]`、`[End]`：起点和终点的 `x`、`y`。
- `[Situation]` 的 `map`：地图类型，`0` 至 `4` 依次对应上述五类地图。
- `[Algorithm]`：用 `0` 或 `1` 关闭或启用算法。字段包括 `Dijktra`、`Astar`、`Astar_BinaryHeap`、`Astar_InsertSort`、`Astar_InsertSort_BinarySearch`、`BFS`、`BFS_Priority`、`DFS`。其中 `Dijktra` 是代码中的实际拼写。

仓库没有附带 `config.ini`。没有配置时会使用代码默认值，起点和终点默认都为 `(0, 0)`；要观察有效寻路过程，应先设置地图内可通行、彼此不同的起终点。

- `Enter`：重新执行当前配置下的搜索。
- `Esc`：退出。

窗口布局和地图尺寸采用固定值，同时启用过多算法可能超出可见区域。各实现属于学习实验，使用前应自行检查正确性及适用条件；第三方 HGE 文件保留其原有声明。
