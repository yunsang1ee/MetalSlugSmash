#pragma once
#include <ysComponent.h>
#include <ysAnimation.h>

namespace ys
{
	class Animator : public Component
	{
	public:
		Animator();
		~Animator();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hDC) override;

		void CrateAnimation(const std::wstring& name, graphics::Texture* spriteSheet
			, const math::Vector2& leftTop, const math::Vector2& size, const math::Vector2& offset
			, const UINT lenth, const float duration);

		Animation* FindAnimation(const std::wstring& name);
		Animation* GetActive() { return activeAnimation; }
		void PlayAnimation(const std::wstring& name, const bool loop = true);

	private:
		std::map<std::wstring, Animation*> animations;
		Animation* activeAnimation;
		bool isLoop;
	};

} 