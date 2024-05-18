#pragma once
#include "ysScript.h"
#include "ysGameObject.h"

namespace ys
{
	class CameraScript : public Script
	{
	public:
		CameraScript();
		~CameraScript();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hDC) override;

		void SetTarget(GameObject* target) { this->target = target; }
		void SetOffset(const Vector2& offset) { this->offset = offset; }

	private:
		GameObject* target;
		Vector2 offset;
	};
}


