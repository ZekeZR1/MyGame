#pragma once
class ClearScene : public IScene
{
public:
	ClearScene();
	~ClearScene();
	void Update() override;
	void Draw() override;
private:
	Sprite m_sprite;
};

