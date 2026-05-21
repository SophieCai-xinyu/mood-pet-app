# 心光伴旅 Qt Demo

这是一个基于 Qt 6 的桌面演示样板，包含以下核心模块：

- 悬浮速记窗口（`InputWindow.h/cpp`, `style.qss`）
- 像素宠物动画展示（`PetWidget.h/cpp`）
- 本地加密数据存储（`DataManager.h/cpp`）
- 历史记录展示与检索（`HistoryWindow.h/cpp`）
- 系统托盘与备份恢复（`TrayManager.h/cpp`）

## 运行方式

1. 在 Qt 6 环境下打开 `demo1.pro`
2. 运行 qmake + make / build
3. 启动后可通过托盘菜单或主界面入口使用

## 已实现的功能

- 速记窗口支持单行快速输入和长文本记录
- 通过情绪下拉框调整记录心情
- 提交记录后触发存储与宠物状态切换
- 数据以本地 `.ett` 文件方式保存，并通过简单 XOR + Base64 加密
- 历史窗口支持按关键字搜索、时间段筛选、查看/编辑/删除
- 托盘菜单支持快速打开、数据备份、数据恢复、隐藏和退出

## 代码结构

- `main.cpp`：入口、应用初始化
- `mainwindow.h/cpp`：模块整合、快捷入口、信号连接
- `InputWindow.*`：悬浮输入窗口
- `PetWidget.*`：宠物状态显示与拖拽
- `DataManager.*`：本地存储与加密逻辑
- `HistoryWindow.*`：历史记录检索与编辑
- `TrayManager.*`：托盘菜单与全局体验
- `resources.qrc`：嵌入样式文件
- `style.qss`：窗口样式定义

## 备注

- 当前示例使用 Qt 标准组件模拟像素宠物状态，实际生产可替换为 GIF 动画资源
- 全局快捷键演示可使用 `Ctrl+Alt+N`，若需支持系统级全局快捷键，可接入 `QHotkey` 或平台原生 API

Enjoy the demo!
