#pragma once
#include "..\\MyEngine_source\\ysScene.h"
using namespace ys;

class prac : public Scene
{
public:
	prac();
	~prac();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hDc) override;
	GameObject* GetPlayer() { return player; }

private:
	GameObject* backBackground;
	GameObject* background;
	GameObject* player;
	std::vector<GameObject*> bulletPool;
	std::vector<GameObject*> Blocks;
	std::vector<GameObject*> enemys;
	GameObject* camera;
};


