#pragma once
#include "ysComponent.h"
namespace ys
{
	class Collider : public Component
	{
	public:
		Collider();
		~Collider();

		virtual void Init();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hDC);

		math::Vector2 GetOffset() { return offset; }
		void SetOffset(const math::Vector2& offset) { this->offset = offset; }

	private:
		math::Vector2 offset;
	};
}

