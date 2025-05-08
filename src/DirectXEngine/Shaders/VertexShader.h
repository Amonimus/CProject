#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include "../GraphicsEngine/GraphicsEngine.h"
#include "../DeviceContext/DeviceContext.h"

class VertexShader{
    public:
        VertexShader();
        ~VertexShader();
        bool init(const void* shader_byte_code, size_t byte_code_size);
        void release();
    private:
        ID3D11VertexShader* m_vs;

        friend class GraphicsEngine;
        friend class DeviceContext;
};