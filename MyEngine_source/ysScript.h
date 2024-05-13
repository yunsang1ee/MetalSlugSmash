#pragma once
#include "ysComponent.h"

namespace ys
{
	class Script : public Component
	{
	public:
		Script();
		~Script();

		virtual void Init();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hDC);

	private:

	};

}
