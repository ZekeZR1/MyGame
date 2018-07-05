#include "stdafx.h"
#include "Sprite.h"
#include "SpBuffer.h"
#include "graphics\GraphicsEngine.h"
Sprite::Sprite()
{

}


Sprite::~Sprite()
{
	if (m_vertexBuffer != NULL) {
		m_vertexBuffer->Release();
	}
	if (m_indexBuffer != NULL) {
		m_indexBuffer->Release();
	}
	if (m_samplerState != NULL) {
		m_samplerState->Release();
	}
	if (m_texture != NULL) {
		m_texture->Release();
	}
}
void Sprite::Init(const wchar_t* texFilePath)
{

	InitVertexBuffer(m_vertexBuffer);
	InitIndexBuffer(m_indexBuffer);
	InitSamplerState(m_samplerState);
	m_effect.Load("Assets/shader/primitive.fx");
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(),				
		texFilePath,				
		0,                          
		D3D11_USAGE_DEFAULT,		
		D3D11_BIND_SHADER_RESOURCE,	
		0,							
		0,				
		false,						
		nullptr,					
		&m_texture					
	);
}
void Sprite::Draw()
{
	m_effect.BeginRender();
	unsigned int vertexSize = sizeof(SVertex);	
	unsigned int offset = 0;
	g_graphicsEngine->GetD3DDeviceContext()->IASetVertexBuffers(	
		0,					
		1,				
		&m_vertexBuffer,	
		&vertexSize,		
		&offset			
	);
	g_graphicsEngine->GetD3DDeviceContext()->IASetIndexBuffer(	
		m_indexBuffer,			
		DXGI_FORMAT_R32_UINT,	
								
		0					
	);

	g_graphicsEngine->GetD3DDeviceContext()->PSSetShaderResources(0, 1, &m_texture);
	g_graphicsEngine->GetD3DDeviceContext()->PSSetSamplers(0, 1, &m_samplerState);

	g_graphicsEngine->GetD3DDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	g_graphicsEngine->GetD3DDeviceContext()->DrawIndexed(	
		6,			
		0,				
		0				
	);
}