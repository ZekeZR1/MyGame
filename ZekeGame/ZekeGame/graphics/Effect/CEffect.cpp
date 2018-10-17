#include "stdafx.h"
#include "CEffect.h"

using namespace Effekseer;

CEffect::CEffect()
{
	// 描画用インスタンスの生成
	g_renderer = ::EffekseerRendererDX11::Renderer::Create(g_graphicsEngine->GetD3DDevice(), g_graphicsEngine->GetD3DDeviceContext(), 2000);

	// エフェクト管理用インスタンスの生成
	g_manager = ::Effekseer::Manager::Create(2000);

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

	// 視点位置を確定
	g_position = ::Effekseer::Vector3D(10.0f, 5.0f, 20.0f);

	// 投影行列を設定
	g_renderer->SetProjectionMatrix(
		::Effekseer::Matrix44().PerspectiveFovRH(90.0f / 180.0f * 3.14f, 1280.0f / 720.0f, 1.0f, 50.0f));

	// カメラ行列を設定
	g_renderer->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtRH(g_position, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));
}


CEffect::~CEffect()
{
	// エフェクトの破棄
	ES_SAFE_RELEASE(g_effect);

	// 先にエフェクト管理用インスタンスを破棄
	g_manager->Destroy();

	// 次に描画用インスタンスを破棄
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