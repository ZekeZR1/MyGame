#include "stdafx.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "CTransform.h"

void GameObjectManager::Execute()
{
	ExecuteDeleteGameObjects();

	for (GameObjectList objList : m_gameObjectListArray) {
		for (GameObject* obj : objList) {
			obj->StartWrapper();
		}
	}
	for (GameObjectList objList : m_gameObjectListArray) {
		for (GameObject* obj : objList) {
			obj->PreUpdateWrapper();
		}
	}

	//g_graphicsEngine->GetPreRender().Update();
	for (GameObjectList objList : m_gameObjectListArray) {
		for (GameObject* obj : objList) {
			obj->UpdateWrapper();
		}
	}
	for (GameObjectList objList : m_gameObjectListArray) {
		for (GameObject* obj : objList) {
			obj->PostUpdateWrapper();
		}
	}

	//シーングラフを更新。
	//UpdateSceneGraph();
	//ライトを更新。
	//LightManager().Update();
	//エフェクトを更新。
	//g_graphicsEngine->GetEffectEngine().Update();

	//画面をクリア
	/*
	float ClearColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; //red,green,blue,alpha
	RenderTarget* renderTargets[] = {
		&g_graphicsEngine->GetMainRenderTarget()
	};
	*/
	/*
	//CRenderContext& renderContext = g_graphicsEngnine->GetRenderContext();
	auto renderContext = g_graphicsEngine->GetD3DDeviceContext();
	renderContext->OMSetRenderTargets(1,);
	renderContext->ClearRenderTargetView(0,ClearColor);
	renderContext->RSSetViewport(0.0f, 0.0f, (float)GraphicsEngine().GetFrameBufferWidth(), (float)GraphicsEngine().GetFrameBufferHeight());
	renderContext->RSSetState(RasterizerState::sceneRender);
	renderContext->OMSetDepthStencilState(DepthStencilState::SceneRender, 0);
	*/
	g_graphicsEngine->BegineRender();
	//プリレンダリング。
	//GraphicsEngine().GetPreRender().Render(renderContext);
	//BeginGPUEvent(L"enRenderStep_Render3DModelToScene");
	//レンダリングステップを3Dモデルの描画に。
	//renderContext.SetRenderStep(enRenderStep_Render3DModelToScene);

	//ライトの情報を転送転送。
	//LightManager().Render(renderContext);
	//影を落とすための情報を転送。
	//GraphicsEngine().GetShadowMap().SendShadowReceiveParamToGPU(renderContext);
	//GraphicsEngine().GetGBufferRender().SendGBufferParamToGPU(renderContext);

	for (GameObjectList objList : m_gameObjectListArray) {
		for (GameObject* obj : objList) {
			obj->PreRenderWrapper();
		}
	}

	for (GameObjectList objList : m_gameObjectListArray) {
		for (GameObject* obj : objList) {
			//obj->RenderWrapper(renderContext);
			obj->RenderWrapper();
		}
	}


	//EndGPUEvent();

	//ポストエフェクト。
	//GraphicsEngine().GetPostEffect().Render(renderContext);

	//2D的なものの描画。
	//BeginGPUEvent(L"enRenderStep_Render2DToScene");
	//float blendFactor[4] = { 0.0f };
	/*
	renderContext.OMSetBlendState(AlphaBlendState::trans, blendFactor, 0xFFFFFFFF);
	renderContext.RSSetState(RasterizerState::spriteRender);
	renderContext.OMSetDepthStencilState(DepthStencilState::spriteRender, 0);
	renderContext.SetRenderStep(enRenderStep_Render2DToScene);
	*/
	for (GameObjectList objList : m_gameObjectListArray) {
		for (GameObject* obj : objList) {
			//obj->PostRenderWrapper(renderContext);
			obj->PostRenderWrapper();
		}
	}
	//EndGPUEvent();
	g_graphicsEngine->EndRender();

}
void GameObjectManager::UpdateSceneGraph()
{
	//ワールド行列を更新。
	for (auto transform : m_childrenOfRootTransformList) {
		transform->UpdateWorldMatrixAll();
	}
}
void GameObjectManager::ExecuteDeleteGameObjects()
{
	int preBufferNo = m_currentDeleteObjectBufferNo;
	//バッファを切り替え。
	m_currentDeleteObjectBufferNo = 1 ^ m_currentDeleteObjectBufferNo;
	for (GameObjectList& goList : m_deleteObjectArray[preBufferNo]) {
		for (GameObject* go : goList) {
			GameObjectPrio prio = go->GetPriority();
			GameObjectList& goExecList = m_gameObjectListArray.at(prio);
			auto it = std::find(goExecList.begin(), goExecList.end(), go);
			if (it != goExecList.end()) {
				//削除リストから除外された。
				(*it)->m_isRegistDeadList = false;
				if ((*it)->IsNewFromGameObjectManager()) {
					delete (*it);
				}
			}
			goExecList.erase(it);
		}
		goList.clear();
	}
}
void GameObjectManager::Init(int gameObjectPrioMax)
{
	//assert(gameObjectPrioMax <= GAME_OBJECT_PRIO_MAX);// && "ゲームオブジェクトの優先度の最大数が大きすぎます。");
	assert(gameObjectPrioMax <= GAME_OBJECT_PRIO_MAX && "ゲームオブジェクトの優先度の最大数が大きすぎます。");
	m_gameObjectPriorityMax = static_cast<GameObjectPrio>(gameObjectPrioMax);
	m_gameObjectListArray.resize(gameObjectPrioMax);
	m_deleteObjectArray[0].resize(gameObjectPrioMax);
	m_deleteObjectArray[1].resize(gameObjectPrioMax);
}