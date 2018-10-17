#include "stdafx.h"
#include "CEffect.h"

using namespace Effekseer;

CEffect::CEffect()
{
	// �`��p�C���X�^���X�̐���
	g_renderer = ::EffekseerRendererDX11::Renderer::Create(g_graphicsEngine->GetD3DDevice(), g_graphicsEngine->GetD3DDeviceContext(), 2000);

	// �G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
	g_manager = ::Effekseer::Manager::Create(2000);

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

	// ���_�ʒu���m��
	g_position = ::Effekseer::Vector3D(10.0f, 5.0f, 20.0f);

	// ���e�s���ݒ�
	g_renderer->SetProjectionMatrix(
		::Effekseer::Matrix44().PerspectiveFovRH(90.0f / 180.0f * 3.14f, 1280.0f / 720.0f, 1.0f, 50.0f));

	// �J�����s���ݒ�
	g_renderer->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtRH(g_position, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));
}


CEffect::~CEffect()
{
	// �G�t�F�N�g�̔j��
	ES_SAFE_RELEASE(g_effect);

	// ��ɃG�t�F�N�g�Ǘ��p�C���X�^���X��j��
	g_manager->Destroy();

	// ���ɕ`��p�C���X�^���X��j��
	g_renderer->Destroy();
}

void CEffect::Init() {
	g_effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"test.efk");

}

void CEffect::Play() {
	g_handle = g_manager->Play(g_effect, 0, 0, 0);
}

void CEffect::Stop() {
	g_manager->StopEffect(g_handle);
}

void CEffect::Update() {
	g_manager->AddLocation(g_handle, ::Effekseer::Vector3D(0.2f, 0.0f, 0.0f));
	g_manager->Update();
}

void CEffect::Draw() {
	g_renderer->BeginRendering();
	g_manager->Draw();
	g_renderer->EndRendering();
}