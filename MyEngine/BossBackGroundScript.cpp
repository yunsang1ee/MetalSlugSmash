#include "BossBackGroundScript.h"
#include "YSapplication.h"
#include <ysTransform.h>
#include <ysInputManager.h>
#include <ysTimer.h>
#include <ysRenderer.h>
#include "STAGE1.h"
#include <ysRigidBody.h>

extern ys::Application app;
namespace ys
{
	BossBackGroundScript::BossBackGroundScript()
	{
	}
	BossBackGroundScript::~BossBackGroundScript()
	{
	}
	void BossBackGroundScript::Init()
	{
	}
	void BossBackGroundScript::Update()
	{
		SetParallax(fabsf(STAGE1::GetPlayerLow()->GetComponent<RigidBody>()->GetVelocity().x) / 3.0f);
		auto tr = GetOwner()->GetComponent<Transform>();
		if ((InputManager::getKey((BYTE)ys::Key::A) || InputManager::getKey(VK_LEFT)))
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x + Timer::getDeltaTime() * GetParallax(), position.y});
		}
		if ((InputManager::getKey((BYTE)ys::Key::D) || InputManager::getKey(VK_RIGHT)))
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x - Timer::getDeltaTime() * GetParallax(), position.y});
		}

		if (tr->GetPosition().x <= -(app.getScreenf().x))
		{
			tr->SetPosition(Vector2(app.getScreenf().x, 0.0f));
		}
	}
	void BossBackGroundScript::LateUpdate()
	{
	}
	void BossBackGroundScript::Render(HDC hDC)
	{
	}
	void BossBackGroundScript::OnCollisionEnter(Collider* other)
	{
	}
	void BossBackGroundScript::OnCollisionStay(Collider* other)
	{
	}
	void BossBackGroundScript::OnCollisionExit(Collider* other)
	{
	}
}