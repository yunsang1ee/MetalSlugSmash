#pragma once
#include <ysScript.h>

namespace ys
{
	class EnemyScript : public Script
	{
	public:
		EnemyScript();
		~EnemyScript();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hDC) override;

	private:
		int animation = 0;
		float timer = 0;
	};
}

