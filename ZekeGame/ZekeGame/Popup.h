#pragma once
class Popup
{
public:
	Popup();
	~Popup();
	void Update();
	void Draw();
	void Notify(int type);
	bool isNotifying = false;
private:
	Sprite ms_notify;
	Sprite* m_sprite;
	CVector3 m_pos = CVector3::Zero();
	int mi_writing = 0;
	enum NotifyType {
		en_GotMaterial,
	};
	NotifyType en_type;
};

