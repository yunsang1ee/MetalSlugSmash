#pragma once
#include "..\\MyEngine_source\\ysScene.h"
namespace ys
{
	class BossScene : public Scene
	{

	public:
		BossScene();
		~BossScene();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hDC, const int& index) override;
		virtual void Destroy();

		

		virtual void OnEnter() override; //title -> play scene (play init)
		virtual void OnExit() override;  //title -> play scene (title exit)
	private:

		GameObject* boss;
		GameObject* backBackground;
		GameObject* background;
		GameObject* player;
		GameObject* PlayerLowerBody;
		std::vector<GameObject*> bulletPool;
		std::vector<GameObject*> Blocks;
		std::vector<GameObject*> Walls;
		GameObject* camera;

		


	};
}

