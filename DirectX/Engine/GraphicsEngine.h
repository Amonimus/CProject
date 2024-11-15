#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

// #include "SwapChain.h"

class GraphicsEngine {
    private:
        ID3D11Device* m_d3d_device;
        D3D_FEATURE_LEVEL m_feature_level;
        ID3D11DeviceContext* m_imm_context;
    public:
        GraphicsEngine();
        ~GraphicsEngine();
        bool init();
        bool release();
        static GraphicsEngine* get();
        // SwapChain* createSwapChain();
};