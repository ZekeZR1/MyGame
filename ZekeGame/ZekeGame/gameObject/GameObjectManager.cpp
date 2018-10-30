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

	//�V�[���O���t���X�V�B
	//UpdateSceneGraph();
	//���C�g���X�V�B
	//LightManager().Update();
	//�G�t�F�N�g���X�V�B
	//g_graphicsEngine->GetEffectEngine().Update();

	//��ʂ��N���A
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
	//�v�������_�����O�B
	//GraphicsEngine().GetPreRender().Render(renderContext);
	//BeginGPUEvent(L"enRenderStep_Render3DModelToScene");
	//�����_�����O�X�e�b�v��3D���f���̕`��ɁB
	//renderContext.SetRenderStep(enRenderStep_Render3DModelToScene);

	//���C�g�̏���]���]���B
	//LightManager().Render(renderContext);
	//�e�𗎂Ƃ����߂̏���]���B
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

	//�|�X�g�G�t�F�N�g�B
	//GraphicsEngine().GetPostEffect().Render(renderContext);

	//2D�I�Ȃ��̂̕`��B
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
	//���[���h�s����X�V�B
	for (auto transform : m_childrenOfRootTransformList) {
		transform->UpdateWorldMatrixAll();
	}
}
void GameObjectManager::ExecuteDeleteGameObjects()
{
	int preBufferNo = m_currentDeleteObjectBufferNo;
	//�o�b�t�@��؂�ւ��B
	m_currentDeleteObjectBufferNo = 1 ^ m_currentDeleteObjectBufferNo;
	for (GameObjectList& goList : m_deleteObjectArray[preBufferNo]) {
		for (GameObject* go : goList) {
			GameObjectPrio prio = go->GetPriority();
			GameObjectList& goExecList = m_gameObjectListArray.at(prio);
			auto it = std::find(goExecList.begin(), goExecList.end(), go);
			if (it != goExecList.end()) {
				//�폜���X�g���珜�O���ꂽ�B
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
	//assert(gameObjectPrioMax <= GAME_OBJECT_PRIO_MAX);// && "�Q�[���I�u�W�F�N�g�̗D��x�̍ő吔���傫�����܂��B");
	assert(gameObjectPrioMax <= GAME_OBJECT_PRIO_MAX && "�Q�[���I�u�W�F�N�g�̗D��x�̍ő吔���傫�����܂��B");
	m_gameObjectPriorityMax = static_cast<GameObjectPrio>(gameObjectPrioMax);
	m_gameObjectListArray.resize(gameObjectPrioMax);
	m_deleteObjectArray[0].resize(gameObjectPrioMax);
	m_deleteObjectArray[1].resize(gameObjectPrioMax);
}