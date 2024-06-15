#pragma once
#include <ysComponent.h>

namespace ys
{
	class AudioListener : public Component
	{
	public:
		AudioListener();
		~AudioListener();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hDC) override;

	private:
	};

}
