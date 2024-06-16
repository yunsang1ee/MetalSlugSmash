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

namespace ys
{
	BossBulletScript::BossBulletScript() : deathTime(6.0f), time(0.0f), damage(10)
	{
		auto rb = GetOwner()->AddComponent<RigidBody>();
		auto an = GetOwner()->AddComponent<Animator>();
		auto bd = GetOwner()->AddComponent<BoxCollider2D>();
		an->CrateAnimation(L"º¸½º_ÃÑ¾Ë", Resources::Find<graphics::Texture>(L"º¸½º_ÃÑ¾Ë")
			, Vector2(5, 0)
			, Vector2(65, 58)
			, Vector2(0, 0), 12, 0.1f);
		an->CrateAnimation(L"º¸½º_ÃÑ¾ËÆø¹ß", Resources::Find<graphics::Texture>(L"º¸½º_ÃÑ¾ËÆø¹ß")
			, Vector2(10, 0)
			, Vector2(50, 40)
			, Vector2(0, 0), 12, 0.1f);
	}

	BossBulletScript::~BossBulletScript()
	{
	}

	void BossBulletScript::Init()
	{
	}

	void BossBulletScript::Update()
	{
		auto tr = GetOwner()->GetComponent<Transform>();
		auto pos = tr->GetPosition();
		tr->SetPosition(Vector2(pos.x + 40, pos.y));
		time += Timer::getDeltaTime();
		if (time >= deathTime)
		{
			ys::object::Destroy(GetOwner());
		}
	}

	void BossBulletScript::LateUpdate()
	{
	}

	void BossBulletScript::Render(HDC hDC)
	{
	}

	void BossBulletScript::OnCollisionEnter(Collider* other)
	{
	}

	void BossBulletScript::OnCollisionStay(Collider* other)
	{
	}

	void BossBulletScript::OnCollisionExit(Collider* other)
	{
	}
}

