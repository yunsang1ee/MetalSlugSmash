#include "BossBulletScript.h"
#include "ysScript.h"
#include "ysGameObject.h"
#include "ysTransform.h"
#include "ysCollider.h"
#include "ysRigidBody.h"
#include "ysTimer.h"
#include <ysAnimator.h>
#include "ysResources.h"
#include "ysObject.h"
#include <ysBoxCollider2D.h>
#include <ysCircleCollider2D.h>
#include "PlayerLowerBodyScript.h"

namespace ys
{
	BossBulletScript::BossBulletScript() : deathTime(6.0f), time(0.0f), damage(10)
	{
	}

	BossBulletScript::~BossBulletScript()
	{
	}

	void BossBulletScript::Init()
	{
	}

	void BossBulletScript::Update()
	{
		if (GetOwner()->GetLayerType() == LayerType::Projectile)
		{
			auto rb = GetOwner()->GetComponent<RigidBody>();
			if (rb->IsGround())
			{
				boom();
			}
		}
		else if (GetOwner()->GetComponent<Animator>()->IsComplete())
		{
			object::Destroy(GetOwner());
		}

		/*auto tr = GetOwner()->GetComponent<Transform>();
		auto pos = tr->GetPosition();
		tr->SetPosition(Vector2(pos.x + 40, pos.y));
		time += Timer::getDeltaTime();
		if (time >= deathTime)
		{
			ys::object::Destroy(GetOwner());
		}*/
	}

	void BossBulletScript::LateUpdate()
	{
	}

	void BossBulletScript::Render(HDC hDC)
	{
	}

	void BossBulletScript::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == LayerType::PlayerLowerBody
			|| other->GetOwner()->GetLayerType() == LayerType::Block)
		{
			boom();
		}
	}

	void BossBulletScript::OnCollisionStay(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == enums::LayerType::PlayerLowerBody)
		{
			auto playerLower = other->GetOwner();
			auto ps = playerLower->GetComponent<PlayerLowerBodyScript>();
			ps->GetPlayerChest()->SetActive(false);
			ps->SetState(PlayerLowerBodyScript::PlayerState::Death);
			auto pan = playerLower->GetComponent<Animator>();
			pan->PlayAnimation(L"ÇÃ·¹ÀÌ¾î_Á×À½", false);
		}
	}

	void BossBulletScript::OnCollisionExit(Collider* other)
	{
	}
	void BossBulletScript::boom()
	{
		GetOwner()->SetLayerType(LayerType::Particle);
		auto cd = GetOwner()->GetComponent<CircleCollider2D>();
		cd->SetOffset(Vector2(-85.0f, -50.0f));
		cd->SetSize(Vector2(1.2f, 1.2f));

		auto rb = GetOwner()->GetComponent<RigidBody>();
		rb->SetVelocity(Vector2::Zero);
		rb->SetGravity(Vector2::Zero);

		auto an = GetOwner()->GetComponent<Animator>();
		an->PlayAnimation(L"º¸½º_ÃÑ¾ËÆø¹ß", false);
	}
}