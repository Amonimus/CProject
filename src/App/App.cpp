#include "App.h"
#include "../DirectXEngine/D3DWindow/D3DWindow.cpp"
#include "../utils/Logger/Logger.cpp"

App::~App(){}

App::App(const wchar_t* lpWindowName, int nWidth, int nHeight, const wchar_t* iconPath, Color* bg_color) :
D3DWindow(lpWindowName, nWidth, nHeight, iconPath, bg_color) {}

// Events

void App::onCreate() {
    D3DWindow::onCreate();
}
void App::onUpdate() {
    D3DWindow::onUpdate();
}
void App::onDestroy() {
    D3DWindow::onDestroy();
}
