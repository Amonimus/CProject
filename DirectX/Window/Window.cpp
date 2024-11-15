#ifndef UNICODE
#define UNICODE
#endif
#include "Window.h"
#include "WndCallback.cpp"

Window::Window() {}
Window::~Window() {}

bool Window::init(const wchar_t* lpWindowName, int nWidth, int nHeight, const wchar_t* icon_path) {
    // Window initialization
    WNDCLASSEX wc;
    wc.cbClsExtra = 0;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    if(icon_path){
        wc.hIcon = (HICON) LoadImage(NULL, icon_path, IMAGE_ICON, 32, 32, LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_SHARED);
        wc.hIconSm = (HICON) LoadImage(NULL, icon_path, IMAGE_ICON, 16, 16, LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_SHARED);
    } else {
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    }
        
    wc.hInstance = NULL;
    wc.lpszClassName = L"MyWindowClass";
    wc.lpszMenuName = L"";
    wc.lpfnWndProc = &WndProc;
    
    if(!::RegisterClassEx(&wc)){
        // If registration fails, cancel
        print("Window registration failed!");
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
        print("Window creation failed!");
        return false;
    }

    // Open Window after setup
    ::ShowWindow(m_hwnd, SW_SHOW);
    // Redraw Window
    ::UpdateWindow(m_hwnd);

    m_is_run = true;
    return true;
}

bool Window::broadcast() {
    // Take system signals
    MSG msg;
    while(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
        // Handle all system messages in queue
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    // Update graphics
    window->onUpdate();
    // Minimal pause to avoid hanging
    Sleep(0);
    return true;
}

bool Window::release() {
    // Action on Window closure
    if(!::DestroyWindow(m_hwnd)){
        // Something prevents from closing the Window
        return false;
    }

    return true;
}

void Window::onCreate() {}

bool Window::isRun() {
    // Getter to see if Window is running
    return m_is_run;
}

void Window::onDestroy() {
    // Action on Window destructor
    print("Window is destroyed");
    m_is_run = false;
}

RECT Window::getClientWindowRect() {
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);
	return rc;
}