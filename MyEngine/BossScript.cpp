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
BossScript::BossScript() : HP(2000)
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

	timer += Timer::getDeltaTime();
	if (timer>=0.1)
	{
		Move();
		timer = 0;
	}
	
	if (timer>=1)
	{
		ShootBullet();
	}

	if (HP <= 0)
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
		pan->PlayAnimation(L"플레이어_죽음", false);
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
	auto tr = GetOwner()->GetComponent<Transform>();
	auto pos = tr->GetPosition();
	if (Right)
	{
		tr->SetPosition(Vector2(pos.x + 10,pos.y));
	}
	else {
		tr->SetPosition(Vector2(pos.x - 20, pos.y));
	}
	

}

void BossScript::ShootBullet()
{
	auto tr = GetOwner()->GetComponent<Transform>();
	auto pos = tr->GetPosition();
	auto bullet = object::Instantiate<GameObject>(LayerType::Projectile, Vector2{pos.x + 130 , pos.y + 300});
	bullet->AddComponent<BossBulletScript>();
}
