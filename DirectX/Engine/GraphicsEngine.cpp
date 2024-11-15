#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine(){}
GraphicsEngine::~GraphicsEngine(){}

bool GraphicsEngine::init() {
    D3D_DRIVER_TYPE driver_types[] = {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    D3D_FEATURE_LEVEL feature_levels[] = {
        D3D_FEATURE_LEVEL_11_0
    };
    HRESULT d3d_create_res = 0;
    D3D11_CREATE_DEVICE_FLAG device_flag = D3D11_CREATE_DEVICE_SINGLETHREADED;
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
            break;
        }
        ++driver_type_index;
    }
    if (FAILED(d3d_create_res)){
        return false;
    }
    return true;
}

bool GraphicsEngine::release() {
    m_imm_context->Release();
    m_d3d_device->Release();
    return true;
}

GraphicsEngine *GraphicsEngine::get() {
    // Prevents secondary initialization at runtime
    static GraphicsEngine engine;
    return &engine;
}
