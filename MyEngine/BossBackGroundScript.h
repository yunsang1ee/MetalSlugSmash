#pragma once
#include "ysBackGroundScript.h"

namespace ys
{
	class BossBackGroundScript : public BackGroundScript
	{
	public:
		BossBackGroundScript();
		~BossBackGroundScript();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hDC) override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
	};
}

