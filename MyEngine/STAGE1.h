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
	};
}

