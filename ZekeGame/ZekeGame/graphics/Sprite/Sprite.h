#pragma once
#include "Effect.h"
class Sprite
{
public:
	Sprite();
	~Sprite();
	void Init(const wchar_t* texFilePath);
	void Draw();
	ID3D11Buffer*				m_vertexBuffer = NULL;	//頂点バッファ。
	ID3D11Buffer*				m_indexBuffer = NULL;	//インデックスバッファ。
	Effect						m_effect;				//エフェクト。気にしなくてよい。
	ID3D11ShaderResourceView*	m_texture = NULL;		//テクスチャ。
	ID3D11SamplerState*			m_samplerState = NULL;	//サンプラステート。
	CVector3 m_position = CVector3::Zero();			//座標。
	CQuaternion					m_rotation = CQuaternion::Identity();	
	CVector3					m_scale = CVector3::One();
	CMatrix						m_world = CMatrix::Identity();		
	CVector2					m_size = CVector2::Zero();				
	ID3D11Buffer*				m_cb = nullptr;						

};

