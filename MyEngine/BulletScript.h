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

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void SetDamage(const unsigned int& damage) { this->damage = damage; }
		unsigned int getDamage() const { return damage; }

	private:
		float deathTime;
		float time;
		unsigned int damage;
	};
}

