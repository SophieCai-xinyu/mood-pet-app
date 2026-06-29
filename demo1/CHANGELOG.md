# 修改日志 (CHANGELOG)

## 2026-06-27 — 问题修复批次 (v1.1)

### ✅ P0 - 已修复（严重问题）

| # | 问题描述 | 涉及文件 | 修改内容 |
|---|---------|---------|---------|
| 1 | 重复代码 | `main.cpp` | 删除第 36 行重复的 `a.setQuitOnLastWindowClosed(false)` |
| 2 | 内存泄漏 | `mainwindow.cpp` | `m_inputWindow` / `m_petWidget` / `m_historyWindow` 创建时传入 `this` 作为 parent，由 Qt 父子机制自动管理生命周期 |
| 3 | 样式表被覆盖 | `mainwindow.cpp` | `applyTextColorToUi()` 改为完整重建样式表（保留原基础样式 + 注入用户颜色），不再丢失背景渐变等样式 |
| 4 | 宠物状态方法空壳 | `PetWidget.cpp` | ⚠️ **TODO** — 标记了注释，等补充 GIF 宠物资源后再实现具体动画效果 |
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

### ⚠️ P3 - 未完成（待后续处理）

| # | 问题描述 | 状态 | 待办内容 |
|---|---------|------|---------|
| 4 | 宠物状态方法空壳 | ⏳ TODO | `setStateIdle()` / `setStateNormal()` / `setStateRecording()` / `setStateSuccess()` 目前为空。计划：不同状态加载对应 GIF（如 idle → `pet_idle.gif`，recording → `pet_recording.gif`，success → `pet_happy.gif`）。见 `PetWidget.cpp` 内 TODO 注释 |
| 13 | GIF 资源缺失 | ⏳ TODO | `pet/` 目录及以下文件待补充：`pet1.gif` `pet2.gif` `pet3.gif` `pet4.gif` `pet_sleep.gif`（共 5 个）。当前 fallback 为 emoji 文字 😺 |

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
