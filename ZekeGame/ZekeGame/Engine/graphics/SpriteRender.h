#pragma once
class SpriteRender : public GameObject
{
public:
	SpriteRender();
	~SpriteRender();
	bool Start() override;
	void Update() override;
	void PostRender() override;

	void Init(const wchar_t* texFilePath, float w, float h);

	void SetPosition(const CVector3& pos)
	{
		m_pos = pos;
	}

	const CVector3& GetPosition() const
	{
		return m_pos;
	}

	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}

	const CQuaternion& GetRotation() const
	{
		return m_rotation;
	}

	void SetPivot(const CVector2& pivot)
	{
		m_pivot = pivot;
	}

private:
	Sprite m_sprite;
	CVector3 m_pos = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();
	CVector2 m_pivot = Sprite::DEFAULT_PIVOT;
};

