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
		void Render(HDC hDc) override;

		void OnEnter() override;
		void OnExit() override;

	private:
		GameObject* camera;
		GameObject* backBackground;
		GameObject* background;
		GameObject* player;
		std::vector<GameObject*> bulletPool;
	};
}