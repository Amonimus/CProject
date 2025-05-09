#pragma once
#include <d3d11.h>

#include "../GraphicsEngine/GraphicsEngine.h"

class DeviceContext;

class SwapChain {
    public:
        SwapChain();
        ~SwapChain();
        bool init(HWND hwnd, UINT width, UINT height);
        bool present(bool vsync);
        bool release();
    private:
        IDXGISwapChain* m_sc;
        ID3D11RenderTargetView* m_rtv;
        friend class DeviceContext;
};