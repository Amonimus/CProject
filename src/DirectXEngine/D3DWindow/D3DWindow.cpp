#pragma once
#include "D3DWindow.h"
#include "../../Window/BaseWindow/BaseWindow.cpp"
#include "../GraphicsEngine/GraphicsEngine.cpp"
#include "../../utils/Logger/Logger.cpp"

struct vec3 {
    float x, y, z;
};
struct vertex {
    vec3 position;
    //vec3 color;
};

D3DWindow::D3DWindow(const wchar_t* lpWindowName, int nWidth, int nHeight, const wchar_t* iconPath, Color* bg_color) {
    this->lpWindowName = lpWindowName;
    this->nWidth = nWidth;
    this->nHeight = nHeight;
    this->iconPath = iconPath;
    this->m_bg_color = bg_color;
    logger.debug("App is constructed");
}
D3DWindow::~D3DWindow() {
    logger.debug("App is destroyed");
}

void D3DWindow::run() {
    if(init(this->lpWindowName, this->nWidth, this->nHeight, this->iconPath)) {
        logger.debug("App is initialized and is listening");
        while(isRun()){
            broadcast();
        }
        logger.debug("App is no longer listening");
    } else {
        logger.error("Failed to Initialize!");
    }
}

// Event: On Window creation
void D3DWindow::onCreate() {
    BaseWindow::onCreate();
    GraphicsEngine::get()->init();

    m_sc = GraphicsEngine::get()->createSwapChain();
    RECT rc = this->getClientWindowRect();
    m_sc->init(this->m_hwnd, rc.right-rc.left, rc.bottom-rc.top);

    vertex vertex_list[] = {
        {-0.5f, -0.5f, 0.0f},
        {0.0f, 0.5f, 0.0f},
        {0.5f, -0.5f, 0.0f},
        //{0.5f, 0.5f, 0.0f},
    };
    m_vb = GraphicsEngine::get()->createVertexBuffer();
    UINT list_size = ARRAYSIZE(vertex_list);

    void* shader_byte_code = nullptr;
    size_t shader_size = 0;
    GraphicsEngine::get()->createShaders();
    GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &shader_size);

    GraphicsEngine::get()->compileVertexShader(L"res/Shader.fx", "vsmain", &shader_byte_code, &shader_size);
    m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, shader_size);
    m_vb->load(vertex_list, sizeof(vertex_list), list_size, shader_byte_code, shader_size);
    GraphicsEngine::get()->releaseCompiledShader();

    GraphicsEngine::get()->compilePixelShader(L"res/Shader.fx", "psmain", &shader_byte_code, &shader_size);
    m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, shader_size);
    GraphicsEngine::get()->releaseCompiledShader();
}
// Event: On Window update
void D3DWindow::onUpdate() {
    BaseWindow::onUpdate();
    // Clears render areas
    GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(
        this->m_sc,
        this->m_bg_color->red,
        this->m_bg_color->green,
        this->m_bg_color->blue,
        this->m_bg_color->alpha
    );
    // Set viewport as draw target
    RECT rc = this->getClientWindowRect();
    GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right-rc.left, rc.bottom-rc.top);
    // Set shaders
    GraphicsEngine::get()->setShaders();
    //GraphicsEngine::get()->getImmediateDeviceContext()->setVertextShader(m_vs);
    //GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);
    // Set draw buffer
    GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
    // Draw the figure
    GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getVertexListSize(), 0);
    GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getVertexListSize(), 0);
    m_sc->present(false);
}
// Event: On Window destruction
void D3DWindow::onDestroy() {
    BaseWindow::onDestroy();
    m_vb->release();
    m_vs->release();
    m_ps->release();
    m_sc->release();
    GraphicsEngine::get()->release();
}
