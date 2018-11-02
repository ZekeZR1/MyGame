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

	//g_graphicsEngine->GetEffectEngine().Update();

	g_graphicsEngine->BegineRender();

	for (GameObjectList objList : m_gameObjectListArray) {
		for (GameObject* obj : objList) {
			obj->PreRenderWrapper();
		}
	}

	for (GameObjectList objList : m_gameObjectListArray) {
		for (GameObject* obj : objList) {
			obj->RenderWrapper();
		}
	}


	for (GameObjectList objList : m_gameObjectListArray) {
		for (GameObject* obj : objList) {
			obj->PostRenderWrapper();
		}
	}
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
	assert(gameObjectPrioMax <= GAME_OBJECT_PRIO_MAX && "ゲームオブジェクトの優先度の最大数が大きすぎます。");
	m_gameObjectPriorityMax = static_cast<GameObjectPrio>(gameObjectPrioMax);
	m_gameObjectListArray.resize(gameObjectPrioMax);
	m_deleteObjectArray[0].resize(gameObjectPrioMax);
	m_deleteObjectArray[1].resize(gameObjectPrioMax);
}