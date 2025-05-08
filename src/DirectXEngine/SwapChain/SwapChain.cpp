#pragma once
#include "SwapChain.h"
#include "../../utils/Logger/Logger.cpp"

SwapChain::SwapChain(){}
SwapChain::~SwapChain(){}

bool SwapChain::init(HWND hwnd, UINT width, UINT height) {
	// Initialize SwapChain for a window
    logger.debug("Initializing DXGI Swap Chain");
	ID3D11Device* device = GraphicsEngine::get()->m_d3d_device;

	DXGI_SWAP_CHAIN_DESC desc = {0};
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	// Create the swap chain for the window indicated by HWND parameter
    logger.debug("Creating Swap Chain");
	HRESULT hr = GraphicsEngine::get()->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);
	if (FAILED(hr))	{
        logger.error("Failed to create SwapChain");
	 	return false;
	}

	// Get the back buffer color and create its render target view
    logger.debug("Creating texture buffer");
	ID3D11Texture2D* buffer = NULL;
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
	if (FAILED(hr))	{
        logger.error("Failed to create SwapChain Buffer");
	 	return false;
	}

    logger.debug("Creating render target view");
	hr = device->CreateRenderTargetView(buffer, NULL, &m_render_taget_view);
	buffer->Release();
	if (FAILED(hr))	{
        logger.error("Failed to create SwapChain Render");
	 	return false;
	}

	return true;
}

bool SwapChain::present(bool vsync) {
	m_swap_chain->Present(vsync, 0);
    return true;
}

bool SwapChain::release() {
	// Release the SwapChain
 	m_swap_chain->Release();
 	delete this;
 	return true;
}