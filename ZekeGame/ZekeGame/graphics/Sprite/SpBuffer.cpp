#include "stdafx.h"
#include "SpBuffer.h"

void InitVertexBuffer(ID3D11Buffer*& vertexBuffer)
{
	SVertex vertex[4] = {
		{
			-0.5f,  -0.5f, 0.0f, 1.0f,
			0.0f, 1.0f
		},
		{
			0.5f, -0.5f, 0.0f, 1.0f,
			1.0f, 1.0f
		},
		{
			-0.5f,  0.5f, 0.0f, 1.0f,
			0.0f, 0.0f
		},
		{
			0.5f,  0.5f, 0.0f, 1.0f,
			1.0f, 0.0f
		},
	};
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));				
	bd.Usage = D3D11_USAGE_DEFAULT;				//バッファーで想定されている読み込みおよび書き込みの方法。
	bd.ByteWidth = sizeof(vertex);				//頂点バッファのサイズ。頂点のサイズ×頂点数となる。
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//これから作成するバッファが頂点バッファであることを指定する。

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertex;

	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &vertexBuffer);
}
void InitIndexBuffer(ID3D11Buffer*& indexBuffer)
{
	int index[6] = {
		0,1,2,		
		2,1,3		
	};
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));				
	bd.Usage = D3D11_USAGE_DEFAULT;				
												
	bd.ByteWidth = sizeof(index);				
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;		

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = index;

	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &indexBuffer);
}
void InitSamplerState(ID3D11SamplerState*& samplerState)
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &samplerState);
}