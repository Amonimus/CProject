#pragma once
#include "BaseWindow.h"
#include "WndCallback.cpp"
#include "../../utils/Logger/Logger.cpp"

BaseWindow::BaseWindow() {}
BaseWindow::~BaseWindow() {}

bool BaseWindow::init(const wchar_t* lpWindowName, int nWidth, int nHeight, const wchar_t* icon_path) {
    // BaseWindow initialization
    logger.debug("Window init begin");
    WNDCLASSEX wc;
    wc.cbClsExtra = 0;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbWndExtra = 0;

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    loadIcon(&wc, icon_path);
    
    wc.hInstance = NULL;
    wc.lpszClassName = L"MyWindowClass";
    wc.lpszMenuName = L"";
    wc.lpfnWndProc = &WndProc;
    
    if(!::RegisterClassEx(&wc)){
        // If registration fails, cancel
        logger.error("Window registration failed!");
        return false;
    };

    if(!window){
        // if pointer isn't set, set to this class
        window = this;
    }

    // Window parameters
    int xPos = CW_USEDEFAULT;
    int yPos = CW_USEDEFAULT;
    DWORD dwExStyle = WS_EX_OVERLAPPEDWINDOW;
    DWORD dwStyle = WS_OVERLAPPEDWINDOW;
    HWND hWndParent = NULL;
    HMENU hMenu = NULL;
    HINSTANCE hInstance = NULL;
    LPVOID lpParam = NULL;

    // Create Window
    m_hwnd = ::CreateWindowEx(
        dwExStyle,
        wc.lpszClassName,
        (LPCWSTR)lpWindowName,
        dwStyle,
        xPos,
        yPos,
        nWidth,
        nHeight,
        hWndParent,
        hMenu,
        hInstance,
        lpParam
    );

    if(!m_hwnd){
        // If the creation fails, cancel
        logger.error("Window creation failed!");
        return false;
    }

    // Open Window after setup
    ::ShowWindow(m_hwnd, SW_SHOW);
    // Redraw Window
    ::UpdateWindow(m_hwnd);

    m_is_run = true;
    logger.debug("Window initialized successfully");
    return true;
}

void BaseWindow::loadIcon(WNDCLASSEX* wc, const wchar_t* icon_path){
    if(icon_path){
        wc->hIcon = (HICON) LoadImage(NULL, icon_path, IMAGE_ICON, 32, 32, LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_SHARED);
        wc->hIconSm = (HICON) LoadImage(NULL, icon_path, IMAGE_ICON, 16, 16, LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_SHARED);
    } else {
        wc->hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc->hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    }
}

void BaseWindow::setHWND(HWND hwnd) {
    this->m_hwnd = hwnd;
}

bool BaseWindow::isRun() {
    return m_is_run;
}

RECT BaseWindow::getClientWindowRect() {
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);
	return rc;
}

// Take system signals
bool BaseWindow::broadcast() {
    MSG msg;
    // Update graphics
    window->onUpdate();
    // Handle all system messages in queue
    while(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    // Minimal pause to avoid hanging
    Sleep(0);
    return true;
}

// Action on Window closure
bool BaseWindow::release() {
    if(!::DestroyWindow(m_hwnd)){
        // Something prevents from closing the Window
        logger.error("Window release failed!");
        return false;
    }
    logger.debug("Window is released");
    return true;
}

// Events

void BaseWindow::onCreate() {
    logger.debug("Window is created");
}
void BaseWindow::onUpdate() {}
void BaseWindow::onDestroy() {
    // Action on Window destructor
    m_is_run = false;
    logger.debug("Window is destroyed");
}