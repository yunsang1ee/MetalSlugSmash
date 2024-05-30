#pragma once
#include <ysComponent.h>

namespace ys
{
	class RigidBody : public Component
	{
	public:
		RigidBody();
		~RigidBody();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hDC) override;

		void SetMass(const float& mass) { this->mass = mass; }
		void AddForce(const math::Vector2 force) { this->force = force; }

	private:
		float mass;
		float friction;

		math::Vector2 force;
		math::Vector2 accelation;
		math::Vector2 velocity;
		math::Vector2 gravity;
	};
}

