#include "StartScript.h"
#include <ysGameObject.h>
#include <ysObject.h>
#include <ysTransform.h>
#include <YSapplication.h>

extern ys::Application app;
namespace ys
{
	StartScript::StartScript()
	{
	}
	StartScript::~StartScript()
	{
	}
	void StartScript::Init()
	{
	}
	void StartScript::Update()
	{
		if (GetOwner()->GetComponent<Transform>()->GetPosition().x < app.getScreenf().x)
			object::Destroy(GetOwner());
	}
	void StartScript::LateUpdate()
	{
	}
	void StartScript::Render(HDC hDC)
	{
	}
	void StartScript::OnCollisionEnter(Collider* other)
	{
	}
	void StartScript::OnCollisionStay(Collider* other)
	{
	}
	void StartScript::OnCollisionExit(Collider* other)
	{
	}
}