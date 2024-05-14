#pragma once
#include <ysComponent.h>
#include <ysGameObject.h>

namespace ys
{
	class Camera : public Component
	{
	public:
		Camera();
		~Camera();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hDC) override;

		Vector2 CalculatPosition(const Vector2& position) { return position - lookPosition; }
		void SetTarget(const GameObject* taraget) { this->target = target; }
		void ClearTarget() { target = nullptr; }
	private:
		Vector2 distance;
		Vector2 resolution;
		Vector2 lookPosition;//카메라의 중앙 (rect left, top) + (resolution / 2)

		GameObject* target;
	};
}

