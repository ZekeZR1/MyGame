#include "CEffect.h"



CEffect::CEffect()
{
	/*Effect
	manager->SetSpriteRenderer(renderer->CreateSpriteRenderer());
	manager->SetRibbonRenderer(renderer->CreateRibbonRenderer());
	manager->SetRingRenderer(renderer->CreateRingRenderer());
	manager->SetTrackRenderer(renderer->CreateTrackRenderer());
	manager->SetModelRenderer(renderer->CreateModelRenderer());

	manager->SetTextureLoader(renderer->CreateTextureLoader());
	manager->SetCoordinateSystem(Effekseer::CoordinateSystem::RH);
	*/
}


CEffect::~CEffect()
{
	/*Effect
	// �G�t�F�N�g��������܂��B�Đ����̏ꍇ�́A�Đ����I��������A�����I�ɉ������܂��B
	ES_SAFE_RELEASE(effect);
	// �G�t�F�N�g�Ǘ��p�C���X�^���X��j��
	manager->Destroy();
	// �`��p�C���X�^���X��j��
	renderer->Destroy();
	*/
}

void CEffect::Init() {
}

void CEffect::Update() {
	/*Effect
	if (g_pad[0].IsTrigger(enButtonA)) {
	//effect = Effekseer::Effect::Create(manager, filepath);
	handle = manager->Play(effect, 0.0f,0.0f,0.0f);
	}
	renderer->SetProjectionMatrix(::Effekseer::Matrix44);
	renderer->SetCameraMatrix(camera3d->GetViewMatrix());
	manager->AddLocation(handle, ::Effekseer::Vector3D);
	manager->Update();
	*/
}

void CEffect::Draw() {
	/*Effect
	renderer->BeginRendering();
	manager->Draw();
	renderer->EndRendering();
	*/
}