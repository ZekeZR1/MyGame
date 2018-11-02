#include "stdafx.h"
#include "CEffectEngine.h"

CEffectEngine::CEffectEngine()
{
	g_renderer = ::EffekseerRendererDX11::Renderer::Create(g_graphicsEngine->GetD3DDevice(), g_graphicsEngine->GetD3DDeviceContext(), 2000);
	// �G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
	g_manager = ::Effekseer::Manager::Create(2000);
	g_manager->SetCoordinateSystem(::Effekseer::CoordinateSystem::LH);
	// �`��p�C���X�^���X����`��@�\��ݒ�
	g_manager->SetSpriteRenderer(g_renderer->CreateSpriteRenderer());
	g_manager->SetRibbonRenderer(g_renderer->CreateRibbonRenderer());
	g_manager->SetRingRenderer(g_renderer->CreateRingRenderer());
	g_manager->SetTrackRenderer(g_renderer->CreateTrackRenderer());
	g_manager->SetModelRenderer(g_renderer->CreateModelRenderer());

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	g_manager->SetTextureLoader(g_renderer->CreateTextureLoader());
	g_manager->SetModelLoader(g_renderer->CreateModelLoader());
}


CEffectEngine::~CEffectEngine()
{
	// �G�t�F�N�g�̔j��
	ES_SAFE_RELEASE(g_effect);

	// ��ɃG�t�F�N�g�Ǘ��p�C���X�^���X��j��
	g_manager->Destroy();

	// ���ɕ`��p�C���X�^���X��j��
	g_renderer->Destroy();

}

void CEffectEngine::Init(const wchar_t* filepath) {
	g_effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)filepath);
}

void CEffectEngine::Play() {
	g_handle = g_manager->Play(g_effect, 0, 300, 0);
}

void CEffectEngine::Stop() {
	g_manager->StopEffect(g_handle);
}

void CEffectEngine::Update() {
	// ���_�ʒu���m��
	CVector3 pos = camera3d->GetPosition();
	g_position = ::Effekseer::Vector3D(pos.x, pos.y, pos.z);

	// �J�����s���ݒ�
	CVector3 tar = camera3d->GetTarget();
	/*
	g_renderer->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtLH(g_position, ::Effekseer::Vector3D(tar.x, tar.y, tar.z), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));
		*/
	g_renderer->SetCameraMatrix(camera3d->GetViewMatrix());

	// ���e�s���ݒ�
	/*
	g_renderer->SetProjectionMatrix(
		::Effekseer::Matrix44().PerspectiveFovLH(camera3d->GetViewAngle(), camera3d->GetAspect(), 0.1f, 50000.0f));
		*/
	g_renderer->SetProjectionMatrix(camera3d->GetProjectionMatrix());

	g_manager->SetScale(g_handle,100.f,100.f,100.f);
	g_manager->AddLocation(g_handle, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f));
	g_manager->Update();
}


void CEffectEngine::Draw() {
	g_renderer->BeginRendering();
	g_manager->Draw();
	g_renderer->EndRendering();
}