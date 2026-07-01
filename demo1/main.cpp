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

    if (g_mainWindow) {
        if (hotKeyID.id == 1) {
            g_mainWindow->showInputWindow();
            return noErr;
        }
        if (hotKeyID.id == 2) {
            g_mainWindow->togglePetVisibility();
            return noErr;
        }
    }
    return CallNextEventHandler(nextHandler, event);
}
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("ConTroL_Group");
    a.setApplicationName("HeartlightCompanion");

    a.setQuitOnLastWindowClosed(false);

    MainWindow w;
    g_mainWindow = &w;

#ifdef Q_OS_MAC
    EventTypeSpec eventType = { kEventClassKeyboard, kEventHotKeyPressed };
    InstallApplicationEventHandler(&globalHotkeyHandler, 1, &eventType, nullptr, nullptr);

    // Ctrl+Option+N -> open quick note
    EventHotKeyID hotKeyInput;
    hotKeyInput.signature = 'HLHK';
    hotKeyInput.id = 1;
    static EventHotKeyRef hotKeyRefInput = nullptr;
    RegisterEventHotKey(kVK_ANSI_N, controlKey | optionKey, hotKeyInput, GetApplicationEventTarget(), 0, &hotKeyRefInput);

    // Ctrl+Option+P -> toggle pet visibility
    EventHotKeyID hotKeyPet;
    hotKeyPet.signature = 'HLHK';
    hotKeyPet.id = 2;
    static EventHotKeyRef hotKeyRefPet = nullptr;
    RegisterEventHotKey(kVK_ANSI_P, controlKey | optionKey, hotKeyPet, GetApplicationEventTarget(), 0, &hotKeyRefPet);
#endif

    w.show();

    const int ret = a.exec();

#ifdef Q_OS_MAC
    if (hotKeyRefInput) {
        UnregisterEventHotKey(hotKeyRefInput);
    }
    if (hotKeyRefPet) {
        UnregisterEventHotKey(hotKeyRefPet);
    }
#endif

    return ret;
}
