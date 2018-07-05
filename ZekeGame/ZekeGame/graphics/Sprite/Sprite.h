#pragma once
#include "Effect.h"
class Sprite
{
public:
	Sprite();
	~Sprite();
	void Init(const wchar_t* texFilePath);
	void Draw();
	ID3D11Buffer*				m_vertexBuffer = NULL;	
	ID3D11Buffer*				m_indexBuffer = NULL;
	Effect						m_effect;				
	ID3D11ShaderResourceView*	m_texture = NULL;	
	ID3D11SamplerState*			m_samplerState = NULL;	
	CVector3 m_position = CVector3::Zero();			
	CQuaternion					m_rotation = CQuaternion::Identity();	
	CVector3					m_scale = CVector3::One();
	CMatrix						m_world = CMatrix::Identity();		
	CVector2					m_size = CVector2::Zero();				
	ID3D11Buffer*				m_cb = nullptr;						

};

