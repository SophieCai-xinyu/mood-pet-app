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