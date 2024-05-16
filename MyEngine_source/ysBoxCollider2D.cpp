#include "ysBoxCollider2D.h"
#include "ysGameObject.h"
#include <ysTransform.h>
#include <ysRenderer.h>

namespace ys
{
	using namespace math;

	BoxCollider2D::BoxCollider2D() : Collider()
		, size(Vector2::Zero)
	{
	}
	BoxCollider2D::~BoxCollider2D()
	{
	}
	void BoxCollider2D::Init()
	{
	}
	void BoxCollider2D::Update()
	{
	}
	void BoxCollider2D::LateUpdate()
	{
	}
	void BoxCollider2D::Render(HDC hDC)
	{
		auto tr = GetOwner()->GetComponent<Transform>();
		auto positionedByCamera = renderer::mainCamera->CalculatPosition(tr->GetPosition());
		auto offset = GetOffset();
		auto brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		auto oldBrush = SelectObject(hDC, brush);
		auto pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		auto oldPen = SelectObject(hDC, pen);
			Rectangle(hDC, positionedByCamera.x + offset.x, positionedByCamera.y + offset.y
				, positionedByCamera.x + offset.x + 100, positionedByCamera.y + offset.y + 100);
		SelectObject(hDC, oldPen);
		SelectObject(hDC, oldBrush);
		DeleteObject(oldPen);
	}
}