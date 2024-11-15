#pragma once
#include <Windows.h>

#include <iostream>
#include <string>
#include <fstream>

using std::cout, std::cin, std::endl;
using std::string, std::to_string;

class Window {
    protected:
        HWND m_hwnd;
        bool m_is_run;
    public:
        Window();
        ~Window();

        bool init(const wchar_t* lpWindowName, int nWidth, int nHeight, const wchar_t* icon_path);
        bool broadcast();
        bool release();
        bool isRun();

        // Events
        virtual void onCreate() = 0;
        virtual void onUpdate() = 0;
        virtual void onDestroy();
};