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
	bd.Usage = D3D11_USAGE_DEFAULT;				//�o�b�t�@�[�őz�肳��Ă���ǂݍ��݂���я������݂̕��@�B
	bd.ByteWidth = sizeof(vertex);				//���_�o�b�t�@�̃T�C�Y�B���_�̃T�C�Y�~���_���ƂȂ�B
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//���ꂩ��쐬����o�b�t�@�����_�o�b�t�@�ł��邱�Ƃ��w�肷��B

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertex;

	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &vertexBuffer);
}
void InitIndexBuffer(ID3D11Buffer*& indexBuffer)
{
	int index[6] = {
		0,1,2,		//�O�p�`���
		2,1,3		//�O�p�`���
	};
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));				//�\���̂�0�ŏ���������B
	bd.Usage = D3D11_USAGE_DEFAULT;				//�o�b�t�@�[�őz�肳��Ă���ǂݍ��݂���я������݂̕��@�B
												//��肠������D3D11_USAGE_DEFAULT�ł悢�B
	bd.ByteWidth = sizeof(index);				//�C���f�b�N�X�o�b�t�@�̃T�C�Y�B
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;		//���ꂩ��쐬����o�b�t�@���C���f�b�N�X�o�b�t�@�ł��邱�Ƃ��w�肷��B

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