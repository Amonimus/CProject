#pragma once
#include "PixelShader.h"
#include "../GraphicsEngine/GraphicsEngine.cpp"
#include "../../utils/Logger/Logger.cpp"

PixelShader::PixelShader(){}
PixelShader::~PixelShader(){}

bool PixelShader::init(const void* shader_byte_code, size_t byte_code_size){
    if(FAILED(GraphicsEngine::get()->m_d3d_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps))){
        logger.error("Failed to create PixelShader");
        return false;
    }
    logger.error("Created PixelShader");
    return true;
}
void PixelShader::release(){
    m_ps->Release();
    delete this;
}