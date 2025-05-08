#pragma once
#include "DeviceContext.h"
#include "../SwapChain/SwapChain.cpp"

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context):m_device_context(device_context){}
DeviceContext::~DeviceContext(){}
void DeviceContext::clearRenderTargetColor(SwapChain* swap_chian, float red, float green, float blue, float alpha) {
    FLOAT clear_color[]= {red, green, blue, alpha};
    m_device_context->ClearRenderTargetView(swap_chian->m_render_taget_view, clear_color);
    m_device_context->OMSetRenderTargets(1, &swap_chian->m_render_taget_view, NULL);
}
void DeviceContext::setVertexBuffer(VertexBuffer *vertex_buffer) {
    UINT stride = vertex_buffer->m_vertex_size;
    UINT offset = 0;
    m_device_context->IASetVertexBuffers(0, 1, &vertex_buffer->m_buffer, &stride, &offset);
    m_device_context->IASetInputLayout(vertex_buffer->m_layout);
}
void DeviceContext::drawTriangleList(UINT vertex_count, UINT start_vertext_index) {
    m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_device_context->Draw(vertex_count, start_vertext_index);
}
void DeviceContext::drawTriangleStrip(UINT vertex_count, UINT start_vertext_index) {
    m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    m_device_context->Draw(vertex_count, start_vertext_index);
}
void DeviceContext::setViewportSize(UINT width, UINT height) {
    D3D11_VIEWPORT viewport = {};
    viewport.Width = width;
    viewport.Height = height;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    m_device_context->RSSetViewports(1, &viewport);
}
void DeviceContext::setVertextShader(VertexShader *vertex_shader) {
    m_device_context->VSSetShader(vertex_shader->m_vs, nullptr, 0);
}
void DeviceContext::setPixelShader(PixelShader *pixel_shader) {
    m_device_context->PSSetShader(pixel_shader->m_ps, nullptr, 0);
}
bool DeviceContext::release() {
    m_device_context->Release();
    delete this;
    return true;
}