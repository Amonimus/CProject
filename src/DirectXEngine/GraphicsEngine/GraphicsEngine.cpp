#pragma once
#include "GraphicsEngine.h"
#include "../SwapChain/SwapChain.cpp"
#include "../DeviceContext/DeviceContext.cpp"
#include "../VertexBuffer/VertexBuffer.cpp"
#include "../Shaders/VertexShader.cpp"
#include "../Shaders/PixelShader.cpp"
#include "../../utils/Logger/Logger.cpp"

GraphicsEngine::GraphicsEngine(){}
GraphicsEngine::~GraphicsEngine(){}

bool GraphicsEngine::init() {
    logger.debug("DirectX init begin");
    D3D_DRIVER_TYPE driver_types[] = {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    D3D_FEATURE_LEVEL feature_levels[] = {
        D3D_FEATURE_LEVEL_11_0
    };
    HRESULT d3d_create_res = 0;
    UINT device_flag = D3D11_CREATE_DEVICE_SINGLETHREADED;
    device_flag |= D3D11_CREATE_DEVICE_DEBUG;

    logger.debug("DirectX is building D3D");
    for (UINT driver_type_index = 0; driver_type_index < ARRAYSIZE(driver_types); ){
        d3d_create_res = D3D11CreateDevice(
            NULL, 
            driver_types[driver_type_index], 
            NULL, 
            device_flag,
            feature_levels,
            ARRAYSIZE(feature_levels),
            D3D11_SDK_VERSION,
            &m_d3d_device,
            &m_feature_level,
            &m_imm_context
        );
        if (SUCCEEDED(d3d_create_res)){
            // If any D3D Device is registered, others aren't needed
            logger.error("DirectX got device");
            break;
        }
        ++driver_type_index;
    }
    if (FAILED(d3d_create_res)){
        logger.error("DirectX failed to create");
        return false;
    }

    logger.debug("DirectX is picking adapters");
    m_imm_device_context = new DeviceContext(m_imm_context);
    m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
    m_dxgi_device->GetParent(__uuidof(IDXGIAdapter),(void**)&m_dxgi_adapter);
    m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory),(void**)&m_dxgi_factory);

    logger.debug("DirectX is initialized");
    return true;
}

GraphicsEngine* GraphicsEngine::get() {
    // Prevents secondary initialization at runtime
    static GraphicsEngine engine;
    return &engine;
}

SwapChain* GraphicsEngine::createSwapChain() {
    return new SwapChain();
}

DeviceContext* GraphicsEngine::getImmediateDeviceContext() {
    return this->m_imm_device_context;
}

VertexBuffer* GraphicsEngine::createVertexBuffer() {
    return new VertexBuffer();
}

bool GraphicsEngine::createShaders() {
    ID3DBlob* errblob = nullptr;
    HRESULT result_vs = D3DCompileFromFile(L"res/Shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", 0, 0, &m_vsblob, &errblob);
    logger.debug("D3DCompile", result_vs);
    HRESULT result_ps = D3DCompileFromFile(L"res/Shader.fx", nullptr, nullptr, "psmain", "ps_5_0", 0, 0, &m_psblob, &errblob);
    logger.debug("D3DCompile", result_ps);
    m_d3d_device->CreateVertexShader(m_vsblob->GetBufferPointer(), m_vsblob->GetBufferSize(), nullptr, &m_vs);
    m_d3d_device->CreatePixelShader(m_psblob->GetBufferPointer(), m_psblob->GetBufferSize(), nullptr, &m_ps);
    return true;
}

bool GraphicsEngine::setShaders() {
    m_imm_context->VSSetShader(m_vs, nullptr, 0);
    m_imm_context->PSSetShader(m_ps, nullptr, 0);
    return true;
}

void GraphicsEngine::getShaderBufferAndSize(void** bytecode, size_t* size) {
    *bytecode = this->m_vsblob->GetBufferPointer();
    *size = (UINT)this->m_vsblob->GetBufferSize();
}

VertexShader* GraphicsEngine::createVertexShader(const void* shader_byte_code, size_t byte_code_size) {
    VertexShader* vs = new VertexShader();
    if (!vs->init(shader_byte_code, byte_code_size)){
        vs->release();
        return nullptr;
    }
    return vs;
}

bool GraphicsEngine::compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_size, size_t* byte_code_size) {
    ID3DBlob* error_blob = nullptr;
    if (FAILED(::D3DCompileFromFile(file_name, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry_point_name, "vs_5_0", 0, 0, &m_vsblob, &error_blob))){
        logger.error("VertexShader failed to compile");
        if(error_blob){
            error_blob->Release();
        }
        return false;
    }

    *shader_byte_size = m_vsblob->GetBufferPointer();
    *byte_code_size = m_vsblob->GetBufferSize();

    return true;
}

PixelShader* GraphicsEngine::createPixelShader(const void *shader_byte_code, size_t byte_code_size) {
    PixelShader* ps = new PixelShader();
    if (!ps->init(shader_byte_code, byte_code_size)){
        ps->release();
        return nullptr;
    }
    return ps;
}

bool GraphicsEngine::compilePixelShader(const wchar_t *file_name, const char *entry_point_name, void **shader_byte_size, size_t *byte_code_size) {
    ID3DBlob* error_blob = nullptr;
    if (FAILED(::D3DCompileFromFile(file_name, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry_point_name, "ps_5_0", 0, 0, &m_psblob, &error_blob))){
        logger.error("PixelShader failed to compile");
        if(error_blob){
            error_blob->Release();
        }
        return false;
    }

    *shader_byte_size = m_psblob->GetBufferPointer();
    *byte_code_size = m_psblob->GetBufferSize();

    return true;
}

void GraphicsEngine::releaseCompiledShader() {
    if(m_blob){
        m_blob->Release();
    }
}
bool GraphicsEngine::release() {
    m_dxgi_device->Release();
    m_dxgi_adapter->Release();
    m_dxgi_factory->Release();
    m_imm_device_context->release();
    m_d3d_device->Release();
    logger.debug("DirectX is released");
    return true;
}