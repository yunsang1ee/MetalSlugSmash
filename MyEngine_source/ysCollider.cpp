#include "ysCollider.h"
#include "ysGameObject.h"

namespace ys
{
	bool Collider::activeRender{ false };
	UINT32 Collider::collisionID{ 1 };

	Collider::Collider(enums::ColliderType type) : Component(enums::ComponentType::Collider)
		, type(type), id(collisionID++), size(math::Vector2::One)
	{
	}
	Collider::~Collider()
	{
	}
	void Collider::Init()
	{
	}
	void Collider::Update()
	{
	}
	void Collider::LateUpdate()
	{
	}
	void Collider::Render(HDC hDC)
	{
	}
	void Collider::OnCollisionEnter(Collider* other)
	{
		auto sc = GetOwner()->GetComponent<Script>();
		sc->OnCollisionEnter(other);
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		auto sc = GetOwner()->GetComponent<Script>();
		sc->OnCollisionStay(other);
	}
	void Collider::OnCollisionExit(Collider* other)
	{
		auto sc = GetOwner()->GetComponent<Script>();
		sc->OnCollisionExit(other);
	}
}
