#include "mainwindow.h"

#include <QApplication>
#ifdef Q_OS_MAC
# include <Carbon/Carbon.h>
#endif

static MainWindow *g_mainWindow = nullptr;

#ifdef Q_OS_MAC
static pascal OSStatus globalHotkeyHandler(EventHandlerCallRef nextHandler, EventRef event, void * /*userData*/)
{
    EventHotKeyID hotKeyID;
    if (GetEventParameter(event, kEventParamDirectObject, typeEventHotKeyID, nullptr, sizeof(hotKeyID), nullptr, &hotKeyID) != noErr) {
        return CallNextEventHandler(nextHandler, event);
    }

    if (hotKeyID.id == 1 && g_mainWindow) {
        g_mainWindow->showInputWindow();
        return noErr;
    }
    return CallNextEventHandler(nextHandler, event);
}
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    MainWindow w;
    g_mainWindow = &w;

#ifdef Q_OS_MAC
    EventTypeSpec eventType = { kEventClassKeyboard, kEventHotKeyPressed };
    InstallApplicationEventHandler(&globalHotkeyHandler, 1, &eventType, nullptr, nullptr);

    EventHotKeyID hotKeyID;
    hotKeyID.signature = 'HLHK';
    hotKeyID.id = 1;
    EventHotKeyRef hotKeyRef = nullptr;
    RegisterEventHotKey(kVK_ANSI_N, controlKey | optionKey, hotKeyID, GetApplicationEventTarget(), 0, &hotKeyRef);
#endif

    w.show();

    return a.exec();
}
