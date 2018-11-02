#include "stdafx.h"
#include "CEffectEngine.h"

CEffectEngine::CEffectEngine()
{
	g_renderer = ::EffekseerRendererDX11::Renderer::Create(g_graphicsEngine->GetD3DDevice(), g_graphicsEngine->GetD3DDeviceContext(), 2000);
	// エフェクト管理用インスタンスの生成
	g_manager = ::Effekseer::Manager::Create(2000);
	g_manager->SetCoordinateSystem(::Effekseer::CoordinateSystem::LH);
	// 描画用インスタンスから描画機能を設定
	g_manager->SetSpriteRenderer(g_renderer->CreateSpriteRenderer());
	g_manager->SetRibbonRenderer(g_renderer->CreateRibbonRenderer());
	g_manager->SetRingRenderer(g_renderer->CreateRingRenderer());
	g_manager->SetTrackRenderer(g_renderer->CreateTrackRenderer());
	g_manager->SetModelRenderer(g_renderer->CreateModelRenderer());

	// 描画用インスタンスからテクスチャの読込機能を設定
	// 独自拡張可能、現在はファイルから読み込んでいる。
	g_manager->SetTextureLoader(g_renderer->CreateTextureLoader());
	g_manager->SetModelLoader(g_renderer->CreateModelLoader());
}


CEffectEngine::~CEffectEngine()
{
	// エフェクトの破棄
	ES_SAFE_RELEASE(g_effect);

	// 先にエフェクト管理用インスタンスを破棄
	g_manager->Destroy();

	// 次に描画用インスタンスを破棄
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
	// 視点位置を確定
	CVector3 pos = camera3d->GetPosition();
	g_position = ::Effekseer::Vector3D(pos.x, pos.y, pos.z);

	// カメラ行列を設定
	CVector3 tar = camera3d->GetTarget();
	/*
	g_renderer->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtLH(g_position, ::Effekseer::Vector3D(tar.x, tar.y, tar.z), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));
		*/
	g_renderer->SetCameraMatrix(camera3d->GetViewMatrix());

	// 投影行列を設定
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