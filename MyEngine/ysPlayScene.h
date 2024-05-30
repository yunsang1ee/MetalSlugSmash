#pragma once
#include "..\\MyEngine_source\\ysScene.h"

namespace ys
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		~PlayScene();

		void Init() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hDc, const int& index) override;

		void OnEnter() override;
		void OnExit() override;

		GameObject* GetPlayer() { return player; }

	private:
		GameObject* backBackground;
		GameObject* background;
		GameObject* player;
		std::vector<GameObject*> bulletPool;
	};
}