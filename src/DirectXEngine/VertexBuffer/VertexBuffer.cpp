#pragma once
#include "VertexBuffer.h"
#include "../GraphicsEngine/GraphicsEngine.h"

VertexBuffer::VertexBuffer():m_layout(0),m_buffer(0){}
VertexBuffer::~VertexBuffer(){}

bool VertexBuffer::load(void* list_vertices, UINT vertex_size, UINT list_size, void* shader_byte_code, UINT shader_byte_size) {

    // Refresh lists
    if(m_layout){
        m_layout->Release();
    }
    if(m_buffer){
        m_buffer->Release();
    }

    D3D11_BUFFER_DESC buff_desc = {};
    buff_desc.Usage = D3D11_USAGE_DEFAULT;
    buff_desc.ByteWidth = vertex_size * list_size;
    buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buff_desc.CPUAccessFlags = 0;
    buff_desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = list_vertices;

    m_vertex_size = vertex_size;
    m_list_size = list_size;

    if (FAILED(GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer))){
        logger.error("Failed to create graphics buffer");
        return false;
    }

    // Input attributes
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        //{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    UINT layout_size = ARRAYSIZE(layout);
    if (FAILED(GraphicsEngine::get()->m_d3d_device->CreateInputLayout(layout, layout_size, shader_byte_code, shader_byte_size, &m_layout))){
        logger.error("Failed to create input layout");
        return false;
    }

    return true;
}
UINT VertexBuffer::getVertexListSize() {
    return this->m_list_size;
}
bool VertexBuffer::release() {
    m_layout->Release();
    m_buffer->Release();
    delete this;
    return true;
}
