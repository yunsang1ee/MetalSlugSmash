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


using namespace ys;

BossScript::BossScript()
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
	
}

void BossScript::LateUpdate()
{
}

void BossScript::Render(HDC hDC)
{
}

void BossScript::OnCollisionEnter(Collider* other)
{
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
