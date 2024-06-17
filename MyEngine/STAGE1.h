#pragma once
#pragma once
#include "..\\MyEngine_source\\ysScene.h"

namespace ys
{
	class STAGE1 : public Scene
	{
	public:
		STAGE1();
		~STAGE1();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hDC, const int& index) override;
		virtual void Destroy();

		static GameObject* GetPlayer() { return player; }
		static GameObject* GetPlayerLow() { return PlayerLowerBody; }
		static GameObject* GetCamera() { return camera; }

		virtual void OnEnter() override; //title -> play scene (play init)
		virtual void OnExit() override;  //title -> play scene (title exit)
	private:
		void playerCreateAnimation();

	private:
		GameObject* backBackground;
		GameObject* background;
		static GameObject* player;
		static GameObject* PlayerLowerBody;
		std::vector<GameObject*> bulletPool;
		std::vector<GameObject*> Blocks;
		std::vector<GameObject*> Walls;
		std::vector<GameObject*> Enemys;
		static GameObject* camera;
	};
}

