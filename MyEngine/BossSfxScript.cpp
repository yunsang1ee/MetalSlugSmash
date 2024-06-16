#include "BossSfxScript.h"
#include"ysGameObject.h"
#include"ysTransform.h"
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
	auto bossPos = boss->GetComponent<Transform>()->GetPosition();
	GetOwner()->GetComponent<Transform>()->SetPosition(bossPos);
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
