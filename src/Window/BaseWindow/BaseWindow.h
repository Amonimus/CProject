#pragma once
#ifndef UNICODE
#define UNICODE
#define UNICODE_WAS_UNDEFINED
#endif

#include <Windows.h>

#ifdef UNICODE_WAS_UNDEFINED
#undef UNICODE
#endif

class BaseWindow {
    public:
        BaseWindow();
        ~BaseWindow();

        bool init(const wchar_t* lpWindowName, int nWidth, int nHeight, const wchar_t* icon_path);
        void loadIcon(WNDCLASSEX* wc, const wchar_t* icon_path);

        // Setter to set Window's HWND
        void setHWND(HWND hwnd);
        // Getter to see if Window is running
        bool isRun();
        // Getter to return Window's RECT
        RECT getClientWindowRect();

        bool broadcast();
        bool release();

        // Events

        virtual void onCreate() = 0;
        virtual void onUpdate() = 0;
        virtual void onDestroy();
    protected:
        HWND m_hwnd;
        bool m_is_run;
};