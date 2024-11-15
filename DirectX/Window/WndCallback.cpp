#pragma once

#include "Window.h"

Window* window = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
    // Window events
    switch(msg){
        case WM_CREATE: {
            window->onCreate();
            break;
        }
        case WM_DESTROY: {
            window->onDestroy();
            // Send a terminate request to the system
            ::PostQuitMessage(0);
            break;
        }
        default: {
            // Unhandled Window event
            return ::DefWindowProcW(hwnd, msg, wparam, lparam);
        }
    }
    return 0;
}