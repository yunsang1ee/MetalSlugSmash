#include "BossScript.h"
#include"ysGameObject.h"
#include"ysTransform.h"
#include"ysCollider.h"
#include"ysRigidBody.h"
#include"ysSceneManager.h"
#include"ysScene.h"
#include"ysObject.h"
#include"ysCircleCollider2D.h"
#include"ysBoxCollider2D.h"

#include"ysTimer.h"
#include"ysCollisionManager.h"
#include"ysAnimator.h"
#include "BossBulletScript.h"
#include "BulletScript.h"
#include "PlayerLowerBodyScript.h"
#include "YSapplication.h"
#include <ysSpriteRenderer.h>
#include <ysResources.h>


using namespace ys;

extern ys::Application app;
BossScript::BossScript() : HP(2000), shootTimer(2.5f), deathTimer(1.5f), Right(false)
{
}

BossScript::~BossScript()
{
}

void BossScript::Init()
{
}

void BossScript::Update()
{
	auto tr = GetOwner()->GetComponent<Transform>();
	auto pos = tr->GetPosition();
	if (pos.x <= -200)
	{
		Right = true;
	}
	else if (pos.x >= 150)
	{
		Right = false;
	}


	if(deathTimer == 1.5f)
	{
		shootTimer -= Timer::getDeltaTime();

		if (shootTimer <= 0.0f)
		{
			ShootBullet();
			shootTimer = 2.5f;
		}
		else
		{
			Move();
		}

		if (HP <= 0)
		{
			GetOwner()->GetComponent<Animator>()->PlayAnimation(L"º¸½º_Á×À½", false);
			auto cd = GetOwner()->GetComponent<BoxCollider2D>();
			cd->SetSize(Vector2::Zero);
			deathTimer -= Timer::getDeltaTime();
		}
	}
	else
	{
		deathTimer -= Timer::getDeltaTime();
		if (deathTimer <= 0.0f)
		{
			auto start = object::Instantiate<GameObject>(LayerType::UI
				, Vector2(app.getScreenf().x + 100.0f, app.getScreenf().y / 4.0f));

			auto sr = start->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"MISSION_1_COMPLTE"));
			sr->SetSizeByScreen(Vector2(288.0f, 64.0f) * 3.0f);
			sr->SetOffset(Vector2(253.0f, 66.0f), Vector2(158.0f, 171.0f));
			auto rb = start->AddComponent<RigidBody>();
			rb->SetGravity(Vector2::Zero);
			rb->SetFriction(0.0f);
			rb->SetVelocity(Vector2::Left * 600.0f);
			object::Destroy(GetOwner());
		}
	}
}

void BossScript::LateUpdate()
{
}

void BossScript::Render(HDC hDC)
{
}

void BossScript::OnCollisionEnter(Collider* other)
{
	if (other->GetOwner()->GetLayerType() == LayerType::PlayerLowerBody)
	{
		auto playerLower = other->GetOwner();
		auto ps = playerLower->GetComponent<PlayerLowerBodyScript>();
		ps->GetPlayerChest()->SetActive(false);
		ps->SetState(PlayerLowerBodyScript::PlayerState::Death);
		auto pan = playerLower->GetComponent<Animator>();
		pan->PlayAnimation(L"ÇÃ·¹ÀÌ¾î_Á×À½", false);
	}
	else if (other->GetOwner()->GetLayerType() == LayerType::Projectile)
	{
		int damage = other->GetOwner()->GetComponent<BulletScript>()->getDamage();
		HP -= damage;
	}
	else if (other->GetOwner()->GetLayerType() == enums::LayerType::Boom)
	{
		HP -= 101;
	}
}

void BossScript::OnCollisionStay(Collider* other)
{
}

void BossScript::OnCollisionExit(Collider* other)
{
}

void BossScript::Move()
{
	auto rb = GetOwner()->GetComponent<RigidBody>();
	if (Right)
	{
		rb->SetVelocity(Vector2::Right * 100);
		//tr->SetPosition(Vector2(pos.x + 10,pos.y));
	}
	else {
		rb->SetVelocity(Vector2::Left * 200);
		//tr->SetPosition(Vector2(pos.x - 20, pos.y));
	}
}

void BossScript::ShootBullet()
{
	auto ownTr = GetOwner()->GetComponent<Transform>();
	auto ownRb = GetOwner()->GetComponent<RigidBody>();
	auto pos = ownTr->GetPosition();

	for(int i = 1; i <= 2; ++i)
	{
		auto bullet = object::Instantiate<GameObject>(LayerType::EnemyProjectile, Vector2{ pos.x + (i * 230) , pos.y });
		auto rb = bullet->AddComponent<RigidBody>();
		rb->SetVelocity(Vector2(400.0f, -400.0f));
		auto cd = bullet->AddComponent<CircleCollider2D>();
		cd->SetOffset(Vector2(-55.0f, -48.0f));
		cd->SetSize(Vector2(1.06f, 1.06f));
		auto an = bullet->AddComponent<Animator>();
		an->CrateAnimation(L"º¸½º_ÃÑ¾Ë", Resources::Find<graphics::Texture>(L"º¸½º_ÃÑ¾Ë")
			, Vector2(10.0f, 0)
			, Vector2(130.0f, 106.0f)
			, Vector2(-65.0f, -58.0f), 4, 0.1f);
		an->CrateAnimation(L"º¸½º_ÃÑ¾ËÆø¹ß", Resources::Find<graphics::Texture>(L"º¸½º_ÃÑ¾ËÆø¹ß")
			, Vector2(30.0f, 0)
			, Vector2(189.0f, 120.0f)
			, Vector2(-95.0f, -60.0f), 18, 0.02f);
		an->PlayAnimation(L"º¸½º_ÃÑ¾Ë");
		bullet->AddComponent<BossBulletScript>();
	}
}