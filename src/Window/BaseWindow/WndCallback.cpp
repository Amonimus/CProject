#pragma once

#include <windowsx.h>
#include "BaseWindow.h"
#include "../../utils/Logger/Logger.cpp"

BaseWindow* window = nullptr;

wchar_t* getKeyName(const unsigned virtualKey){
    unsigned int scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);
    wchar_t* keyName = new wchar_t[16];
    GetKeyNameText(scanCode << 16, keyName, sizeof(keyName));
    return keyName;
}

struct vec2 {
    float x;
    float y;
};

vec2 getMousePosition(LPARAM lparam){
    vec2 position = {
        GET_X_LPARAM(lparam),
        GET_Y_LPARAM(lparam)
    };
    return position;
}

// Window events
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
    switch(msg){
        case WM_CREATE: {
            // Window is created
            logger.debug("Got WM_CREATE event");
            window->setHWND(hwnd);
            window->onCreate();
            break;
        }
        case WM_MOUSEMOVE: {
            // On mouse movement
            break;
        }
        case WM_LBUTTONDOWN: {
            // Left mouse button is detected
            vec2 mouse = getMousePosition(lparam);
            logger.debug("Got a LMB", mouse.x, mouse.y);
            break;
        }
        case WM_KEYDOWN: {
            // Keypress is detected
            wchar_t* key_name = getKeyName(wparam);
            logger.debug("Got a WM_KEYDOWN", key_name);
            if (wparam == VK_ESCAPE){
                DestroyWindow(hwnd);
            }
            delete[] key_name;
            break;
        }
        case WM_CLOSE: {
            // Window is closed
            logger.debug("Close button");
            if (MessageBox(hwnd, L"Are you sure you want to quit?", L"QUIT", MB_YESNO) == IDYES){
                DestroyWindow(hwnd);
            }
            break;
        }
        case WM_DESTROY: {
            // Window is destroyed
            logger.debug("Got WM_DESTROY event");
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