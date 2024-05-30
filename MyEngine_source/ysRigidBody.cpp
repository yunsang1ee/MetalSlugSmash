#include "ysRigidBody.h"
#include "ysGameObject.h"
#include "ysTransform.h"
#include "ysTimer.h"

namespace ys
{
	using namespace math;
	RigidBody::RigidBody() : Component(enums::ComponentType::RigidBody)
		, mass(0.0f)
		, friction(0.0f)
		, force(Vector2::Zero)
		, accelation(Vector2::Zero)
		, velocity(Vector2::Zero)
		, gravity(Vector2::Zero)
	{
	}

	RigidBody::~RigidBody()
	{
	}

	void RigidBody::Init()
	{
	}

	void RigidBody::Update()
	{
		if(mass != 0.0f)
			accelation = force / mass;
		velocity += accelation * Timer::getDeltaTime();

		if (velocity != Vector2::Zero)
		{
			Vector2 tickFriction = -velocity;
			tickFriction = tickFriction.nomalize() * friction * mass * Timer::getDeltaTime();
			if (velocity.scalar() <= tickFriction.scalar())
				velocity == Vector2::Zero;
			else
				velocity += tickFriction;
		}

		auto tr = GetOwner()->GetComponent<Transform>();
		Vector2 position = tr->GetPosition();
		position += velocity * Timer::getDeltaTime();
		tr->SetPosition(position);

		force = Vector2::Zero;
	}

	void RigidBody::LateUpdate()
	{
	}

	void RigidBody::Render(HDC hDC)
	{
	}
}