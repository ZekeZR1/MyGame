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
	// エフェクトを解放します。再生中の場合は、再生が終了した後、自動的に解放されます。
	ES_SAFE_RELEASE(effect);
	// エフェクト管理用インスタンスを破棄
	manager->Destroy();
	// 描画用インスタンスを破棄
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