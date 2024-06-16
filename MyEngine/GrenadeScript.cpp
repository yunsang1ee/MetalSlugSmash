#include "GrenadeScript.h"
#include <ysObject.h>
#include <ysGameObject.h>
#include <ysRigidBody.h>
#include <ysTransform.h>
#include <ysBoxCollider2D.h>
#include <ysAnimator.h>
#include <ysResources.h>

namespace ys
{
	GrenadeScript::GrenadeScript() : force(800.0f)
	{
	}
	GrenadeScript::~GrenadeScript()
	{
	}
	void GrenadeScript::Init()
	{
	}
	void GrenadeScript::Update()
	{
		if(GetOwner()->GetLayerType() == LayerType::Projectile)
		{
			auto rb = GetOwner()->GetComponent<RigidBody>();
			if(rb->IsGround())
			{
				if (force >= 400.0f)
				{
					force = force / 2.0f;
					auto tr = GetOwner()->GetComponent<Transform>();
					rb->SetVelocity(Vector2::Rotate(Vector2::Right ,tr->GetRotation()) * 800.0f + Vector2::Up * force);
				}
				else
					boom();
			}
		}
		else if(GetOwner()->GetComponent<Animator>()->IsComplete())
		{
			object::Destroy(GetOwner());
		}
	}
	void GrenadeScript::LateUpdate()
	{
	}
	void GrenadeScript::Render(HDC hDC)
	{
	}
	void GrenadeScript::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == LayerType::Enemy
			&& GetOwner()->GetLayerType() == LayerType::Projectile)
		{
				boom();
		}
	}
	void GrenadeScript::OnCollisionStay(Collider* other)
	{
	}
	void GrenadeScript::OnCollisionExit(Collider* other)
	{
	}
	void GrenadeScript::boom()
	{
		GetOwner()->SetLayerType(LayerType::Boom);
		auto cd = GetOwner()->GetComponent<BoxCollider2D>();
		cd->SetOffset(Vector2(-110.0f, -440.0f));
		cd->SetSize(Vector2(2.2f, 4.4f));

		auto rb = GetOwner()->GetComponent<RigidBody>();
		rb->SetVelocity(Vector2::Zero);
		rb->SetGravity(Vector2::Zero);

		auto an = GetOwner()->GetComponent<Animator>();
		an->PlayAnimation(L"¼ö·ùÅºÆø¹ß", false);
	}
}