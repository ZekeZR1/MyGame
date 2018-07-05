#pragma once
#include "Effect.h"
class Sprite
{
public:
	Sprite();
	~Sprite();
	void Init(const wchar_t* texFilePath);
	void Draw();
	ID3D11Buffer*				m_vertexBuffer = NULL;	//���_�o�b�t�@�B
	ID3D11Buffer*				m_indexBuffer = NULL;	//�C���f�b�N�X�o�b�t�@�B
	Effect						m_effect;				//�G�t�F�N�g�B�C�ɂ��Ȃ��Ă悢�B
	ID3D11ShaderResourceView*	m_texture = NULL;		//�e�N�X�`���B
	ID3D11SamplerState*			m_samplerState = NULL;	//�T���v���X�e�[�g�B
	CVector3 m_position = CVector3::Zero();			//���W�B
	CQuaternion					m_rotation = CQuaternion::Identity();	
	CVector3					m_scale = CVector3::One();
	CMatrix						m_world = CMatrix::Identity();		
	CVector2					m_size = CVector2::Zero();				
	ID3D11Buffer*				m_cb = nullptr;						

};

