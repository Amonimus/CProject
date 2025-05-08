#pragma once

#include "../DirectXEngine/D3DWindow/D3DWindow.h"

class App : public D3DWindow {
    public:
        ~App();
        App(const wchar_t* lpWindowName, int nWidth, int nHeight, const wchar_t* iconPath, Color* bg_color);

        void onCreate();
        void onUpdate();
        void onDestroy();
};