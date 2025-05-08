#pragma once

#include "../DeviceContext/DeviceContext.h"

class VertexBuffer {
    public:
        VertexBuffer();
        ~VertexBuffer();
        bool load(void* list_vertices, UINT vertex_size, UINT list_size, void* shader_byte_code, UINT shader_byte_size);
        UINT getVertexListSize();
        bool release();
    private:
        UINT m_vertex_size;
        UINT m_list_size;
        ID3D11Buffer* m_buffer;
        ID3D11InputLayout* m_layout;
        friend class DeviceContext;
};