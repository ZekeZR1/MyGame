#pragma once
class TestScene : public GameObject
{
public:
	TestScene();
	~TestScene();
	bool Start() override;
	void Update() override;
	void Render() override;
private:
	SkinModel neko;
};

