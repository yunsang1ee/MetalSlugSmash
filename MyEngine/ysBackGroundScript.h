#pragma once
#include "ysScript.h"
namespace ys
{
	class BackGroundScript : public Script
	{
	public:
		BackGroundScript();
		~BackGroundScript();

		virtual void Init();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hDC);

		void SetParallax(const float& parallax) { this->parallax = parallax; }

	private:
		float parallax;

	};
}

