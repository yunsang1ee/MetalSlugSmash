#pragma once
#include "ysScript.h"

namespace ys
{
	class GrenadeScript : public Script
	{
	public:
		GrenadeScript();
		~GrenadeScript();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hDC) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		void boom();

	private:
		float force;
	};
}

