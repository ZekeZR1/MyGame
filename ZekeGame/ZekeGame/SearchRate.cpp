#include "stdafx.h"
#include "SearchRate.h"
#include "Item/Item.h"


SearchRate::SearchRate()
{
	//Frame
	m_frame.Init(L"sprite/SearchRateFrame.dds", 700.0f, 500.0f);
	m_framePos.x -= 300.0f;
	m_framePos.y += 160.0f;
	m_frame.Update(m_framePos, CQuaternion::Identity(),CVector3::One(), { 0.5f, 0.5f });
	//Air
	ms_rateAir.Init(L"sprite/rateGaugeAir.dds", 300.0f, 30.0f);
	m_airPos.x -= 590.0f;
	m_airPos.y += 290.0f;
	ms_rateAir.Update(m_airPos, CQuaternion::Identity(), CVector3::One(), { 0.0f, 0.0f });
	ms_frameAir.Init(L"sprite/RateGaugeFrame.dds", 300.0f, 30.0f);
	ms_frameAir.Update(m_airPos, m_rot, CVector3::One(), { 0.0f, 0.0f });
	//Ground
	ms_rateGround.Init(L"sprite/rateGaugeGround.dds", 300.0f, 30.0f);
	m_groundPos.x -= 590.0f;
	m_groundPos.y += 245.0f;
	ms_rateGround.Update(m_groundPos, CQuaternion::Identity(), CVector3::One(), { 0.0f, 0.0f });
	ms_frameGround.Init(L"sprite/RateGaugeFrame.dds", 300.0f, 30.0f);
	ms_frameGround.Update(m_groundPos, m_rot, CVector3::One(), { 0.0f, 0.0f });
	//Material
	ms_rateMaterial.Init(L"sprite/rateGaugeMaterial.dds", 300.0f, 30.0f);
	m_materialPos.x -= 590.0f;
	m_materialPos.y += 200.0f;
	ms_rateMaterial.Update(m_materialPos, CQuaternion::Identity(), CVector3::One(), { 0.0f, 0.0f });
	ms_frameMaterial.Init(L"sprite/RateGaugeFrame.dds", 300.0f, 30.0f);
	ms_frameMaterial.Update(m_materialPos, m_rot, CVector3::One(), { 0.0f, 0.0f });
}

SearchRate::~SearchRate()
{
}

void SearchRate::Update() {
	GaugeUpdate();
	m_neko++;
	if (m_neko == 10) {
		m_rateAir += m_searchingWindmill;
		m_neko = 0;
	}
	//m_searchRate += m_searchingBase;
}

void SearchRate::DrawSprite() {
	m_frame.Draw();
	ms_frameAir.Draw();
	ms_rateAir.Draw();
	ms_frameGround.Draw();
	ms_rateGround.Draw();
	ms_frameMaterial.Draw();
	ms_rateMaterial.Draw();
}

void SearchRate::addGroundRate() {
	m_groundSearchingTime++;
	if (m_groundSearchingTime == 10) {
		m_rateGround += 2;
		m_groundSearchingTime = 0;
	}
}

void SearchRate::addMaterialRate() {
		m_rateMaterial += 50;
}

void SearchRate::addSearchRate(Item::EnItem item) {
	switch (item) {
	case Item::en_BASE:
		m_searchingBase++;
		break;
	case Item::en_MINING:
		m_rateGround += 10;
		break;
	case Item::en_WINDMILL:
		m_searchingWindmill += 1;
		break;
	}
}

void SearchRate::ClearCheck() {
	if (m_airScale.x >= 1.0f &&
		m_groundScale.x >= 1.0f &&
		m_materialScale.x >= 1.0f) {
		isAllMax = true;
	}
}

void SearchRate::GaugeUpdate() {
	//Air
	float x = (float)m_rateAir;
	x /= 100.0f;
	m_airScale.x = (x >= 1.0f) ? 1.0f : x;
	ms_rateAir.Update(m_airPos, m_rot, m_airScale, { 0.0f,0.0f });
	//Ground
	x = (float)m_rateGround;
	x /= 100.0f;
	m_groundScale.x = (x > 1.0f) ? 1.0f : x;
	ms_rateGround.Update(m_groundPos, m_rot, m_groundScale, { 0.0f,0.0f });
	//Material
	x = (float)m_rateMaterial;
	x /= 100.0f;
	m_materialScale.x = (x > 1.0f) ? 1.0f : x;
	ms_rateMaterial.Update(m_materialPos, m_rot, m_materialScale, { 0.0f,0.0f });

	ClearCheck();
}