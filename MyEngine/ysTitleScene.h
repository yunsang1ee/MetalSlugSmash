#pragma once
#include "..\\MyEngine_source\\ysScene.h"

namespace ys
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		~TitleScene();

		void Init() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hDc) override;
	private:

	};
}