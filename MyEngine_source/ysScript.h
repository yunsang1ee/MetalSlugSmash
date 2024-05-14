#pragma once
#include "ysComponent.h"

namespace ys
{
	class Script : public Component
	{
	public:
		Script();
		~Script();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hDC) override;

	private:

	};

}
