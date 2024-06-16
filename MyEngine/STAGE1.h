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

		GameObject* GetPlayer() { return player; }

		virtual void OnEnter() override; //title -> play scene (play init)
		virtual void OnExit() override;  //title -> play scene (title exit)
	private:
		void playerCreateAnimation();

	private:
		GameObject* backBackground;
		GameObject* background;
		GameObject* player;
		GameObject* PlayerLowerBody;
		std::vector<GameObject*> bulletPool;
		std::vector<GameObject*> Blocks;
		GameObject* camera;
	};
}

