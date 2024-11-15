#pragma once
#include <string>

#include "Window.cpp"
#include "../Engine/GraphicsEngine.cpp"
#include "../../utils/utils.cpp"

class AppWindow : public Window {
    private:
        const wchar_t* lpWindowName = L"WindowName";
        int nWidth = 1024;
        int nHeight = 768;
        const wchar_t* iconPath = L"res/computer.ico";

    public:
        AppWindow();
        AppWindow(const wchar_t* lpWindowName, int nWidth, int nHeight, const wchar_t* iconPath);
        ~AppWindow();

        virtual void run();
        virtual void onCreate() override;
        virtual void onUpdate() override;
        virtual void onDestroy() override;
};