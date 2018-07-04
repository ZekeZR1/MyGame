#pragma once

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	void InitDirectX(HWND hwnd);
	void Release();
	ID3D11Device* GetD3DDevice() {
		return m_pd3dDevice;
	}
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	void BegineRender();
	void EndRender();
private:
	ID3D11Device* m_pd3dDevice = NULL;
	ID3D11DeviceContext* m_pd3dDeviceContext = NULL;
	D3D_FEATURE_LEVEL m_featureLevel;
	IDXGISwapChain* m_pSwapChain = NULL;
	ID3D11RenderTargetView* m_backBuffer = NULL;
	ID3D11RasterizerState* m_rasterizerState = NULL;
	ID3D11Texture2D* m_depthStencil = NULL;
	ID3D11DepthStencilView* m_depthStencilView = NULL;
};

extern GraphicsEngine* g_graphicsEngine;