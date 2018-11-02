#include "stdafx.h"
#include "SkinModelRender.h"



SkinModelRender::SkinModelRender()
{
}


SkinModelRender::~SkinModelRender()
{
}


bool SkinModelRender::Start() {
	return true;
}

void SkinModelRender::Update() {
	m_skinModel.UpdateWorldMatrix(m_pos, m_rot, m_scale);
}

void SkinModelRender::Render() {
	m_skinModel.SetDirColor(m_dirCol);
	m_skinModel.SetDirLight(m_dirLight);
	m_skinModel.Draw();
	m_skinModel.SetDirColor(m_defCol);
	m_skinModel.SetDirLight(m_defDir);
}


void SkinModelRender::Init(const wchar_t* filePath,
	AnimationClip* animationClips,
	int numAnimationClips,
	EnFbxUpAxis fbxUpAxis){
	m_enFbxUpAxis = fbxUpAxis;
	m_skinModel.Init(filePath,m_enFbxUpAxis);
	InitAnimation(animationClips, numAnimationClips);
}

void SkinModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips) {
	m_animationClips = animationClips;
	m_numAnimationClips = numAnimationClips;
	if (m_animationClips != nullptr) {
		m_animation.Init(m_skinModel, m_animationClips, m_numAnimationClips);
	}
}