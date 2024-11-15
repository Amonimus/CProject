#include "AppWindow.h"

AppWindow::AppWindow() {}
AppWindow::AppWindow(const wchar_t* lpWindowName, int nWidth, int nHeight, const wchar_t* iconPath) {
    AppWindow::lpWindowName = lpWindowName;
    AppWindow::nWidth = nWidth;
    AppWindow::nHeight = nHeight;
    AppWindow::iconPath = iconPath;
}
AppWindow::~AppWindow() {}

void AppWindow::run() {
    
    if(init(AppWindow::lpWindowName, AppWindow::nWidth, AppWindow::nHeight, AppWindow::iconPath)) {
        while(isRun()){
            broadcast();
        }
    } else {
        print("Failed to Initialize!");
    }
}
void AppWindow::onCreate() {
    Window::onCreate();
    GraphicsEngine::get()->init();
}
void AppWindow::onUpdate() {}
void AppWindow::onDestroy() {
    Window::onDestroy();
    GraphicsEngine::get()->release();
}
