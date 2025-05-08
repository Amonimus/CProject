#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include "../SwapChain/SwapChain.h"
#include "../VertexBuffer/VertexBuffer.h"
#include "../Shaders/VertexShader.h"
#include "../Shaders/PixelShader.h"

class DeviceContext{
    public:
        DeviceContext(ID3D11DeviceContext* device_context);
        ~DeviceContext();
        void clearRenderTargetColor(SwapChain* swap_chian, float red, float green, float blue, float alpha);
        void setVertexBuffer(VertexBuffer* vertex_buffer);
        void drawTriangleList(UINT vertex_count, UINT start_vertext_index);
        void drawTriangleStrip(UINT vertex_count, UINT start_vertext_index);
        void setViewportSize(UINT width, UINT height);
        void setVertextShader(VertexShader* vertex_shader);
        void setPixelShader(PixelShader* pixel_shader);
        bool release();
    private:
        ID3D11DeviceContext* m_device_context;
};