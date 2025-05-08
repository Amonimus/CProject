#pragma once
#include "VertexShader.h"
#include "../GraphicsEngine/GraphicsEngine.cpp"
#include "../../utils/Logger/Logger.cpp"

VertexShader::VertexShader(){}
VertexShader::~VertexShader(){}

bool VertexShader::init(const void* shader_byte_code, size_t byte_code_size){
    if(FAILED(GraphicsEngine::get()->m_d3d_device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs))){
        logger.error("Failed to create VertexShader");
        return false;
    }
    logger.error("Created VertexShader");
    return true;
}
void VertexShader::release(){
    m_vs->Release();
    delete this;
}