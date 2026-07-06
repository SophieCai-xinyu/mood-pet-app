# 心光伴旅 Qt Demo

这是一个基于 Qt 6 的桌面演示样板，包含以下核心模块：

- 悬浮速记窗口（`InputWindow.h/cpp`，含闹钟提醒 UI）
- 宠物动画展示（`PetWidget.h/cpp`，4 态 GIF 动画 + emoji fallback + GIF 自适应尺寸）
- 本地加密数据存储（`DataManager.h/cpp`，随机密钥 + XOR + Base64 加密）
- 历史记录展示与检索（`HistoryWindow.h/cpp`）
- 系统托盘与备份恢复（`TrayManager.h/cpp`，QPainter 手绘爱心星光图标）

## 运行方式

1. 在 Qt 6 环境下打开 `demo1.pro`
2. 运行 qmake + make / build
3. 启动后可通过托盘菜单或主界面入口使用

## 已实现的功能

- 速记窗口支持单行快速输入和长文本记录，Enter 键保存
- 6 种情绪下拉选择：Neutral / Happy / Calm / Excited / Unhappy / Focused
- 提交记录后触发存储与宠物状态切换
- 数据以本地 `.ett` 文件方式保存，通过随机 XOR + Base64 加密
- 历史窗口支持按关键字搜索、时间段筛选（全部/今天/本周/本月）、查看/编辑/删除、导出 TXT
- 托盘菜单支持快速打开、数据备份、数据恢复、隐藏桌宠和退出
- 托盘双击直接查看今日记录
- 密码保护：SHA-256 哈希存储，首次访问历史记录时强制设置
- 闹钟提醒功能：可以勾选并设置精确到"年月日时分"的闹钟，到点后会强制置顶弹窗并联动桌宠状态
- 每日治愈文案：桌宠空闲时随机显示原创中文鼓励语（每日一条，避免与昨日重复）
- 跨平台全局热键：Windows 使用 `RegisterHotKey` 实现 `Ctrl+Alt+N`（速记）/ `Ctrl+Alt+P`（切换宠物）；macOS 使用 Carbon 框架实现 `Ctrl+Option+N` / `Ctrl+Option+P`，退出时自动释放
- 用户可以在 pet 文件夹中存放动图，支持 pet1~4.gif 和 pet_sleep.gif，实现个性化

## 代码结构

- `main.cpp`：入口、应用初始化、跨平台全局热键注册与释放
- `mainwindow.h/cpp`：模块整合、快捷入口、信号连接、密码验证、闹钟轮询
- `InputWindow.*`：悬浮输入窗口（含闹钟复选框和日期时间选择器）
- `PetWidget.*`：宠物状态显示与拖拽（含每日文案气泡和 GIF 自适应）
- `DataManager.*`：本地存储与加密逻辑（随机密钥持久化）
- `HistoryWindow.*`：历史记录检索与编辑
- `TrayManager.*`：托盘菜单与全局体验（含自定义 QPainter 图标和双击信号）
- `resources.qrc`：嵌入样式文件和 GIF 动画资源
- `style.qss`：窗口样式定义

## 备注

- 当前示例使用 Qt 标准组件 + GIF 动画资源模拟宠物状态，缺失时自动 fallback 为 emoji
- 窗口会自动匹配 GIF 原始尺寸，不再固定大小
- 首次设置密码后无法找回，请妥善保管；升级前建议通过托盘"数据备份"功能导出数据

Enjoy the demo!