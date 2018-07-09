#pragma once
#include "Effect.h"
class Sprite
{
public:
	Sprite();
	~Sprite();

	void Init(const wchar_t* texFilePath, float w, float h);
	
	void Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, CVector2 pivot = { 0.5f, 0.5f });

	void Draw();
	struct ConstantBuffer {
		CMatrix WVP;		
	};
	ID3D11Buffer*				m_vertexBuffer = NULL;
	ID3D11Buffer*				m_indexBuffer = NULL;					
	Effect						m_effect;					
	ID3D11ShaderResourceView*	m_texture = NULL;
	ID3D11SamplerState*			m_samplerState = NULL;				
	CVector3					m_position = CVector3::Zero();			
	CQuaternion					m_rotation = CQuaternion::Identity();	
	CVector3					m_scale = CVector3::One();
	CMatrix						m_world = CMatrix::Identity();			
	CVector2					m_size = CVector2::Zero();			
	ID3D11Buffer*				m_cb = nullptr;							
private:
	void InitConstantBuffer();
};

