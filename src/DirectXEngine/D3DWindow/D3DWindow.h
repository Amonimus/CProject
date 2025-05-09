#pragma once
#include <string>

#include "../../Window/BaseWindow/BaseWindow.h"
#include "../../Base/Color/Color.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../VertexBuffer/VertexBuffer.h"
#include "../Shaders/VertexShader.h"
#include "../Shaders/PixelShader.h"

class D3DWindow : public BaseWindow {
    public:
        D3DWindow(const wchar_t* lpWindowName, int nWidth, int nHeight, const wchar_t* iconPath, Color* bg_color);
        ~D3DWindow();

        virtual void run();
        virtual void onCreate() override;
        virtual void onUpdate() override;
        virtual void onDestroy() override;

    protected:
        // Window title
        const wchar_t* lpWindowName;
        // Window width
        int nWidth;
        // Window height
        int nHeight;
        // Icon path
        const wchar_t* iconPath;
        // Background render color
        Color* m_bg_color;

    private:
        SwapChain* m_sc;
        VertexBuffer* m_vb;
        VertexShader* m_vs;
        PixelShader* m_ps;
};