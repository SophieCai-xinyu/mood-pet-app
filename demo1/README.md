# 心光伴旅 (Heartlight Companion)

灵感速记 & 桌宠陪伴应用，基于 Qt 6。

## 核心模块

- **悬浮速记窗口** (`InputWindow.h/cpp`) — 无边框悬浮输入，支持心情选择、闹钟提醒
- **宠物动画展示** (`PetWidget.h/cpp`) — 4 态 GIF 动画 + emoji fallback + 每日治愈文案气泡 + GIF 自适应尺寸
- **本地加密存储** (`DataManager.h/cpp`) — XOR + Base64 加密，首次运行随机生成 32 字节密钥持久化到 QSettings
- **历史记录检索** (`HistoryWindow.h/cpp`) — 关键字搜索、时间段筛选（全部/今天/本周/本月）、查看/编辑/删除、导出 TXT
- **系统托盘管理** (`TrayManager.h/cpp`) — QPainter 手绘爱心星光图标、双击查看今日记录、数据备份/恢复
- **密码保护** (`mainwindow.cpp`) — SHA-256 哈希存储，首次访问历史记录时强制设置

## 运行方式

1. 在 Qt 6 环境下打开 `demo1.pro`
2. 运行 qmake + make / build
3. 启动后通过主界面按钮或托盘菜单使用

## 功能特性

- 速记窗口支持单行快速输入和长文本记录，Enter 键保存
- 6 种心情下拉选择：Neutral / Happy / Calm / Excited / Unhappy / Focused
- 提交记录后触发宠物成功动画 + 1.8 秒后恢复空闲
- **闹钟提醒**：勾选"Remind Me (Alarm)"并设置精确到分钟的时间，到点强制置顶弹窗
- 数据以本地 `.ett` 加密文件保存，密钥随机生成并存于 QSettings
- 历史窗口支持搜索、筛选、编辑、删除、导出 TXT
- **密码保护**：SHA-256 哈希存储，杜绝明文密码
- 托盘菜单：快速打开速记、历史记录、数据备份/恢复、隐藏桌宠、退出
- **托盘双击**：直接查看今日记录（走密码验证流程）
- **每日治愈文案**：桌宠空闲时自动显示随机原创中文鼓励语（每日一条，三日不重复）

## 跨平台全局热键

| 平台 | 热键 1 | 热键 2 |
|------|--------|--------|
| Windows | `Ctrl+Alt+N` → 速记窗口 | `Ctrl+Alt+P` → 切换宠物 |
| macOS | `Ctrl+Option+N` → 速记窗口 | `Ctrl+Option+P` → 切换宠物 |

- Windows 使用 `RegisterHotKey` + `nativeEvent(WM_HOTKEY)` 系统级热键
- macOS 使用 Carbon `RegisterEventHotKey`，退出时自动 `UnregisterEventHotKey` 释放

## 代码结构

| 文件 | 说明 |
|------|------|
| `main.cpp` | 入口、应用初始化、跨平台全局热键注册与释放 |
| `mainwindow.h/cpp` | 模块整合、按钮入口、信号连接、密码验证、闹钟轮询 |
| `InputWindow.*` | 悬浮输入窗口（含闹钟 UI） |
| `PetWidget.*` | 宠物状态显示、拖拽、GIF 自适应、每日文案 |
| `DataManager.*` | 本地加密存储与解密、记录搜索与 CRUD |
| `HistoryWindow.*` | 历史记录检索、编辑、导出 |
| `TrayManager.*` | 托盘菜单、自定义图标、双击信号 |
| `resources.qrc` | 嵌入样式文件和 GIF 动画资源 |
| `style.qss` | 窗口样式定义 |

## 安全设计

- **密码**: 使用 `QCryptographicHash::Sha256` 哈希存储键名 `security/passwordHash`，非明文
- **加密密钥**: 首次运行时生成随机 32 字节密钥，Base64 编码后存入 `QSettings("security/encKey")`，非硬编码
- **数据加密**: XOR 流加密 + Base64 编码写入 `.ett` 文件

## 宠物动画

在 `pet/` 目录放置以下 GIF 文件可实现完整动画体验（缺失时 fallback 为 emoji）：

- `pet1.gif` — 成功/空闲时随机加载
- `pet2.gif` — 记录输入中
- `pet3.gif` — 空闲时随机加载
- `pet4.gif` — 空闲时随机加载
- `pet_sleep.gif` — 负面心情时显示

## 备注

- 当前使用 Qt 标准组件 + GIF 动画资源模拟宠物状态
- 窗口自动匹配 GIF 原始尺寸，不再固定为 150×195
- 首次设置密码后无法找回，请妥善保管
- 升级前建议通过托盘"数据备份"功能导出 `.ett` 文件