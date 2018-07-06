#include "stdafx.h"
#include "Sprite.h"
#include "SpBuffer.h"


Camera* g_camera2D = NULL;					//2Dカメラ。
Camera* g_camera3D = NULL;					//3Dカメラ。

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
void Sprite::Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, CVector2 pivot)
{
	CVector2 localPivot = pivot;
	localPivot.x -= 0.5f;
	localPivot.y -= 0.5f;
	localPivot.x *= -2.0f;
	localPivot.y *= -2.0f;
	CVector2 halfSize = m_size;
	halfSize.x *= 0.5f;
	halfSize.y *= 0.5f;
	CMatrix mPivotTrans;

	mPivotTrans.MakeTranslation(
		{ halfSize.x * localPivot.x, halfSize.y * localPivot.y, 0.0f }
	);
	CMatrix mTrans, mRot, mScale;
	mTrans.MakeTranslation(trans);
	mRot.MakeRotationFromQuaternion(rot);
	mScale.MakeScaling(scale);
	m_world.Mul(mPivotTrans, mScale);
	m_world.Mul(m_world, mRot);
	m_world.Mul(m_world, mTrans);
}
void Sprite::InitConstantBuffer()
{
	D3D11_BUFFER_DESC desc;

	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = (((sizeof(ConstantBuffer) - 1) / 16) + 1) * 16;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, NULL, &m_cb);
}

void Sprite::Init(const wchar_t* texFilePath, float w, float h)
{
	m_size.x = w;
	m_size.y = h;
	InitVertexBuffer(m_vertexBuffer, w, h);
	InitIndexBuffer(m_indexBuffer);
	InitSamplerState(m_samplerState);
	m_effect.Load("Assets/shader/sprite.fx");
	wchar_t filePath[256];
	swprintf_s(filePath, L"Resource/%s", texFilePath);
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(),	
		filePath,					
		0,                      
		D3D11_USAGE_DEFAULT,	
		D3D11_BIND_SHADER_RESOURCE,	
		0,						
		0,							
		false,					
		nullptr,				
		&m_texture				
									
	);

	InitConstantBuffer();
}
void Sprite::Draw()
{
	m_effect.BeginRender();
	unsigned int vertexSize = sizeof(SVertex);	
	unsigned int offset = 0;
	GraphicsEngine* ge = g_graphicsEngine;
	ge->GetD3DDeviceContext()->IASetVertexBuffers(	
		0,				
		1,			
		&m_vertexBuffer,	
		&vertexSize,	
		&offset				
	);
	ge->GetD3DDeviceContext()->IASetIndexBuffer(
		m_indexBuffer,			
		DXGI_FORMAT_R32_UINT,	
		0						
	);

	ge->GetD3DDeviceContext()->PSSetShaderResources(0, 1, &m_texture);
	ge->GetD3DDeviceContext()->PSSetSamplers(0, 1, &m_samplerState);
	ConstantBuffer cb;
	cb.WVP = m_world;
	cb.WVP.Mul(cb.WVP, g_camera2D->GetViewMatrix());
	cb.WVP.Mul(cb.WVP, g_camera2D->GetProjectionMatrix());
	ge->GetD3DDeviceContext()->UpdateSubresource(m_cb, 0, NULL, &cb, 0, 0);
	ge->GetD3DDeviceContext()->VSSetConstantBuffers(0, 1, &m_cb);
	ge->GetD3DDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ge->GetD3DDeviceContext()->DrawIndexed(	
		6,				
		0,			
		0				
	);
}