# 心光伴旅 Demo 项目提案

## 项目定位

基于 Qt 6.5.3 设计的桌面极速记录与像素宠物陪伴工具，核心目标是：

- 悬浮速记、快速存档
- 本地加密保存，数据更安全
- 像素宠物陪伴，状态可视化
- 历史检索、导出、备份

## 模块分工表

| 成员 | 负责模块 | 核心代码文件 | 完整功能 | 对外信号 | 对外公开接口 |
|---|---|---|---|---|---|
| A | 悬浮速记窗口模块 | `InputWindow.h/cpp` | 1. 悬浮半透明速记窗口<br>2. 单行 / 长文本输入<br>3. 5 种心情速选<br>4. 窗口拖拽、隐藏<br>5. 记录提交与清空 | `recordSaved()`<br>`windowShowed()`<br>`windowHided()` | `showInputWindow()`<br>`hideInputWindow()` |
| B | 像素宠物动画模块 | `PetWidget.h/cpp` | 1. 状态显示切换<br>2. idle / normal / recording / success<br>3. 宠物拖拽移动<br>4. 记录行为触发反馈 | `petClicked()` | `setStateNormal()`<br>`setStateHappy()`<br>`setStateIdle()` |
| C | 数据存储 + 全局整合模块 | `DataManager.h/cpp`<br>`HistoryWindow.h/cpp`<br>`TrayManager.h/cpp`<br>`mainwindow.h/cpp` | 1. 本地 JSON 加密存储 (.ett)<br>2. 增删改查与全文检索<br>3. 历史记录展示<br>4. 系统托盘 + 快捷入口<br>5. 模块信号槽整合 | `recordsChanged()` | `load()`<br>`save()`<br>`exportToTxt()` |

## 已实现功能

- 悬浮速记窗口：单行/长文本输入、心情选择、拖拽、隐藏
- 宠物窗口：透明浮层、状态切换、点击/拖拽
- 数据存储：本地 `.ett` 加密文件、保存/读取、备份/恢复
- 历史检索：模糊搜索、时间筛选、查看/编辑/删除、TXT 导出
- 系统托盘：快速打开、隐藏、备份、恢复、退出

## 运行说明

- 打开 `demo1.pro`
- 使用 Qt 6 环境进行构建
- 运行后，主窗口、托盘、宠物窗口将自动可用
- `Ctrl+Alt+N` 可快速唤起速记窗口（演示快捷键）

## 说明

当前 Demo 已提供完整模块样例，后续可进一步补充：

- GIF 动画资源替换 `PetWidget` 状态显示
- 平台级全局快捷键支持
- 开机启动与回忆模式定时弹窗
- 更丰富的 UI 交互与外观设计
