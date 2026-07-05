# 修改日志 (CHANGELOG)

## 2026-07-01 — 功能对齐与优化 (v1.3)

### ✅ 代码质量

| # | 问题描述 | 涉及文件 | 修改内容 |
|---|---------|---------|---------|
| 14 | `InputWindow` 重复代码 | `InputWindow.cpp` | 合并 `createLayout()` 中两次 `setStyleSheet()` 为一次；删除 `applyTextStyle()` 中重复的 `setFont()` 调用 |
| 15 | macOS Carbon 热键泄漏 | `main.cpp` | 将 `hotKeyRefInput` / `hotKeyRefPet` 提升为文件作用域静态变量，在 `a.exec()` 返回后调用 `UnregisterEventHotKey` 释放 |

### ✅ 功能新增 / 设计对齐

| # | 功能描述 | 涉及文件 | 修改内容 |
|---|---------|---------|---------|
| 16 | 点击宠物打开速记窗口 | `PetWidget.h` `PetWidget.cpp` `mainwindow.cpp` | `PetWidget` 新增 `openInputRequested()` 信号，左键点击时同时发射 `petClicked()` 和 `openInputRequested()`；`MainWindow` 连接该信号到 `showInputWindow()`（保留原有气泡鼓励语） |
| 17 | 托盘双击查看今日记录 | `TrayManager.h` `TrayManager.cpp` `mainwindow.h` `mainwindow.cpp` `HistoryWindow.h` `HistoryWindow.cpp` | `TrayManager` 新增 `todayRecordsRequested()` 信号 + 监听 `QSystemTrayIcon::activated(DoubleClick)`；`HistoryWindow` 新增 `setTimeFilter()` 公开方法；`MainWindow` 新增 `showTodayRecords()`（先设置筛选"Today"→ 走已有密码验证流程） |
| 18 | 每日治愈文案 | `PetWidget.cpp` | 内置 20 条原创中文治愈文案（`kDailyQuotes` 静态数组）；`setStateIdle()` 中通过 `QSettings("dailyQuote/lastDate")` 判断每日首次，随机选取一条（避免与昨日重复），用现有气泡显示 3 秒 |
| 19 | 托盘图标使用系统默认计算机图标 | `TrayManager.cpp` `TrayManager.h` | 替换为 QPainter 程序化绘制的 32×32 爱心星光图标（蓝紫渐变圆角背景 + 白色爱心 + 金色星光），无需外部资源文件 |
| 20 | PetWidget 窗口偏小导致泡泡文案截断 | `PetWidget.cpp` | 窗口扩展为 150×195：上方 45px 透明区显示对话泡泡，下方 150×150 显示宠物 GIF；泡泡 `maxWidth=width-8` 以容纳最长文案"来，给自己一个微笑。" |

### 📋 修改文件总计

| 文件 | 类型 |
|------|------|
| `InputWindow.cpp` | 代码质量 |
| `main.cpp` | 资源泄漏修复 |
| `PetWidget.h` / `PetWidget.cpp` | 新增信号 + 每日文案 + 窗口尺寸调整 |
| `mainwindow.h` / `mainwindow.cpp` | 新增槽 + 信号连接 |
| `TrayManager.h` / `TrayManager.cpp` | 新增信号 + 托盘双击 + 托盘图标绘制 |
| `HistoryWindow.h` / `HistoryWindow.cpp` | 新增公开方法 |

---

## 2026-06-30 — P3 收尾批次 (v1.2)

### ✅ P3 - 已全部完成

| # | 问题描述 | 涉及文件 | 修改内容 |
|---|---------|---------|---------|
| 4 | 宠物状态方法空壳 | `PetWidget.cpp` | `setStateIdle()` 随机加载 pet1~4.gif；`setStateNormal()` 停止动画显示 emoji 😺；`setStateRecording()` 加载 pet2.gif；`setStateSuccess()` 加载 pet1.gif。GIF 缺失时 fallback 到对应 emoji（😴/✍️/🎉） |
| 13 | GIF 资源缺失 | `pet/` `resources.qrc` | 已补充 5 个 GIF：`pet1.gif`(13.7KB) `pet2.gif`(8.0KB) `pet3.gif`(15.6KB) `pet4.gif`(6.0KB) `pet_sleep.gif`(25.1KB)。`resources.qrc` 同步更新 |

---

## 2026-06-27 — 问题修复批次 (v1.1)

### ✅ P0 - 已修复（严重问题）

| # | 问题描述 | 涉及文件 | 修改内容 |
|---|---------|---------|---------|
| 1 | 重复代码 | `main.cpp` | 删除第 36 行重复的 `a.setQuitOnLastWindowClosed(false)` |
| 2 | 内存泄漏 | `mainwindow.cpp` | `m_inputWindow` / `m_petWidget` / `m_historyWindow` 创建时传入 `this` 作为 parent，由 Qt 父子机制自动管理生命周期 |
| 3 | 样式表被覆盖 | `mainwindow.cpp` | `applyTextColorToUi()` 改为完整重建样式表（保留原基础样式 + 注入用户颜色），不再丢失背景渐变等样式 |
| 7 | Windows 全局热键无效 | `main.cpp` `mainwindow.h` `mainwindow.cpp` | **Windows**: 用 `RegisterHotKey` + `nativeEvent()` 实现系统级 `Ctrl+Alt+N`（唤起速记）/ `Ctrl+Alt+P`（切换宠物）<br>**macOS**: Carbon 框架新增 `Ctrl+Option+P` 切换宠物热键，原有 `Ctrl+Option+N` 保留 |

### ✅ P1 - 已修复（应当修复）

| # | 问题描述 | 涉及文件 | 修改内容 |
|---|---------|---------|---------|
| 5 | 快捷键不更新按钮 | `mainwindow.cpp` | `togglePetVisibility()` 末尾同步更新 `m_togglePetButton` 文本，无论通过按钮点击还是热键触发均保持一致 |
| 6 | 样式设置范围错误 | `InputWindow.cpp` | `loadStyleSheet()` 中 `qApp->setStyleSheet()` → `this->setStyleSheet()`，仅影响 InputWindow 自身 |

### ✅ P2 - 已修复（建议修复）

| # | 问题描述 | 涉及文件 | 修改内容 |
|---|---------|---------|---------|
| 8 | 密码明文存储 | `mainwindow.cpp` | 密码改用 `QCryptographicHash::Sha256` 哈希后存储；存储键名从 `security/password` 改为 `security/passwordHash`（注意：旧明文密码无法自动迁移，首次打开需重新设置） |
| 9 | 弱加密 | `DataManager.h` `DataManager.cpp` | 移除硬编码密钥 `"hearttravel-demo-key-2026"`；改为首次运行时随机生成 32 字节密钥并持久化到 `QSettings("security/encKey")`，后续从 QSettings 读取 |
| 10 | 无效重写 | `PetWidget.cpp` | 删除 `mouseDoubleClickEvent()` 空重写 |
| 11 | 风格不一致 | `TrayManager.cpp` | `onShowHistory()` 通过信号路由（因需密码保护，设计合理），已添加注释说明 |
| 12 | 返回值未检查 | `PetWidget.cpp` | `loadLocalMovie()` 调用处检查返回值，失败时 fallback 到 emoji 文字显示 |

### 📋 新增文件

| 文件 | 说明 |
|------|------|
| `CHANGELOG.md` | 本修改日志文件 |

### 📋 关键技术变更

#### 跨平台全局热键方案对比

| 平台 | 实现 | 热键 1 | 热键 2 |
|------|------|--------|--------|
| Windows | `RegisterHotKey` + `nativeEvent(WM_HOTKEY)` | `Ctrl+Alt+N` → 速记窗口 | `Ctrl+Alt+P` → 切换宠物 |
| macOS | Carbon `RegisterEventHotKey` | `Ctrl+Option+N` → 速记窗口 | `Ctrl+Option+P` → 切换宠物 |

#### 加密方案变更

```
旧方案: XOR(key="hearttravel-demo-key-2026") → Base64 → 写入 .ett
新方案: XOR(key=随机32字节,存QSettings) → Base64 → 写入 .ett
```

#### 密码存储变更

```
旧方案: s.setValue("security/password", "明文密码")
新方案: s.setValue("security/passwordHash", SHA256("密码").toHex())
```

### ⚠️ 迁移注意事项

1. **密码重置**: 旧配置中 `security/password` 存储的明文密码在新版本中失效，用户首次访问历史记录时将被提示重新设置密码
2. **加密密钥**: 如果已有旧的 `.ett` 数据文件（用硬编码密钥加密），新版本会使用新的随机密钥，无法解密旧文件。建议在升级前导出 TXT 备份
3. **GIF 资源**: 应用可正常运行（fallback 显示 emoji），但要宠物动画正常工作需在 `pet/` 目录放置对应 GIF 文件

---

## 2026-07-06 — final 版本融合 (v1.4)

### 🔀 融合背景

对比 `final/`（协作者版本）和 `demo1/`（本版本）两个 Qt 项目后，取两个版本的最优特性进行融合。融合原则：**安全性和用户体验以 demo1 为准，吸取 final 独有的闹钟和 GIF 自适应功能**。

### ✅ 融合项

| # | 融合来源 | 功能描述 | 涉及文件 | 融合内容 |
|---|---------|---------|---------|---------|
| 21 | final | 闹钟提醒系统 | `DataManager.h` `DataManager.cpp` `InputWindow.h` `InputWindow.cpp` `mainwindow.h` `mainwindow.cpp` | `Record` 结构体新增 `hasAlarm`/`alarmTime` 字段并支持 JSON 序列化；`InputWindow` 新增闹钟 UI（QCheckBox + QDateTimeEdit），窗口从 420×320 扩至 420×360；`mainwindow` 新增 `ActiveAlarm` 结构体 + `checkAlarms()` 每秒轮询 + 到点强制置顶弹窗，联动宠物状态设为 "Focused" |
| 22 | final | GIF 自适应尺寸 | `PetWidget.cpp` | 在构造函数中新增 `QMovie::frameChanged` 信号监听，GIF 加载后自动匹配其原始尺寸（含上方 45px 气泡区），窗口不再固定为 150×195 |

### ✅ demo1 保留优势（不受融合影响）

| 维度 | 保留的 demo1 实现 |
|------|------------------|
| 密码安全 | SHA-256 哈希 + `security/passwordHash`（非明文） |
| 加密密钥 | 随机 32 字节 + QSettings 持久化（非硬编码） |
| Windows 热键 | `RegisterHotKey` + `nativeEvent(WM_HOTKEY)` 系统级双热键 |
| macOS 热键 | Carbon 框架双热键 (`Ctrl+Option+N` / `Ctrl+Option+P`) + `UnregisterEventHotKey` 资源释放 |
| 宠物状态动画 | 4 态完整实现（Idle/Recording/Success/Normal）+ emoji fallback |
| 每日治愈文案 | 20 条原创中文 + 每日随机 + 避重复逻辑 |
| 点击宠物→速记 | `openInputRequested` 信号保留 |
| 托盘图标 | QPainter 手绘 32×32 爱心星光图标 |
| 托盘双击 | `todayRecordsRequested` 信号 + `showTodayRecords` + `setTimeFilter` |
| 样式表作用域 | `this->setStyleSheet`（非全局 `qApp->setStyleSheet`） |
| 代码规范 | 无重复 `setFont` 调用、parent 管理、返回值检查 |

### 📋 本次修改文件总计

| 文件 | 类型 |
|------|------|
| `DataManager.h` | 新增闹钟字段 |
| `DataManager.cpp` | 闹钟字段 JSON 序列化 |
| `InputWindow.h` | 新增闹钟 UI 成员变量 |
| `InputWindow.cpp` | 新增闹钟 UI 布局 + 保存/清空逻辑 + 窗口扩容 |
| `PetWidget.cpp` | 新增 GIF 自适应尺寸 (`frameChanged` 监听) |
| `mainwindow.h` | 新增 `ActiveAlarm` + `m_alarmTimer` + `checkAlarms` |
| `mainwindow.cpp` | 新增闹钟轮询 + 记录保存时登记闹钟 |

### ⚠️ 迁移注意事项

4. **闹钟数据**: 旧 `.ett` 数据文件中记录的 `hasAlarm`/`alarmTime` 字段缺失时，`jsonToRecord()` 使用默认值 `false`，兼容旧数据。新产生的闹钟记录会正常序列化并持久化。
5. **窗口尺寸**: 首次打开 InputWindow 时窗口为 420×360（比旧版高 40px 以容纳闹钟行），不影响已有功能。
6. **GIF 尺寸**: 现在窗口会自动匹配 GIF 原始尺寸。若 GIF 尺寸异常（0×0），窗口保持默认 150×195。
