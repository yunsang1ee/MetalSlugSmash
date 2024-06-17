#include "BossSfxScript.h"
#include"ysGameObject.h"
#include"ysTransform.h"
#include "BossScript.h"
#include <ysAnimator.h>
#include <ysObject.h>
BossSfxScript::BossSfxScript()
{
}

BossSfxScript::~BossSfxScript()
{
}

void BossSfxScript::Init()
{
}

void BossSfxScript::Update()
{
	if(boss->IsActive())
	{
		auto bossPos = boss->GetComponent<Transform>()->GetPosition();
		GetOwner()->GetComponent<Transform>()->SetPosition(bossPos);
	}
	else
	{
		object::Destroy(GetOwner());
	}
}

void BossSfxScript::LateUpdate()
{
}

void BossSfxScript::Render(HDC hDC)
{
}

void BossSfxScript::OnCollisionEnter(Collider* other)
{
}

void BossSfxScript::OnCollisionStay(Collider* other)
{
}

void BossSfxScript::OnCollisionExit(Collider* other)
{
}
