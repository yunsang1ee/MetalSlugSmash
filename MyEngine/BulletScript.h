#pragma once
#include <ysScript.h>

namespace ys
{
	class BulletScript : public Script
	{
	public:
		BulletScript();
		~BulletScript();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hDC) override;

	private:
		float deathTime;
		float time;
	};
}

