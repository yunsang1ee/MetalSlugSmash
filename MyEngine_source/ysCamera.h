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

		void SetMinMax(const Vector2& minPosition, const Vector2& maxPosition) 
		{
			this->minPosition = minPosition;
			this->maxPosition = maxPosition;
		}
		Vector2 CalculatPosition(const Vector2& position) { return position - distance; }
		Vector2 GetLookPosition() const { return lookPosition; }
		void SetTarget(GameObject* target) { this->target = target; }
		bool isXmin() const { return xMin; }
		bool isXmax() const { return xMax; }
		bool isYmin() const { return yMin; }
		bool isYmax() const { return yMax; }

	private:
		Vector2 distance;
		Vector2 resolution;
		Vector2 lookPosition;//ī�޶��� �߾� (rect left, top) + (resolution / 2)

		Vector2 minPosition;//ī�޶� �»�� ����
		Vector2 maxPosition;//ī�޶� ���ϴ� ����

		bool xMin;
		bool xMax;
		bool yMin;
		bool yMax;

		GameObject* target;
	};
}

