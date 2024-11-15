#pragma once
#include <string>

#include "Window.cpp"
#include "../Engine/GraphicsEngine.cpp"

class AppWindow : public Window {
    private:
        const wchar_t* lpWindowName;
        int nWidth;
        int nHeight;
        const wchar_t* iconPath;

    public:
        AppWindow();
        AppWindow(const wchar_t* lpWindowName, int nWidth, int nHeight, const wchar_t* iconPath);
        ~AppWindow();

        virtual void run();
        virtual void onCreate() override;
        virtual void onUpdate() override;
        virtual void onDestroy() override;
};