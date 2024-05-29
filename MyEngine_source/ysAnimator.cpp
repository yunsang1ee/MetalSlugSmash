#include "ysAnimator.h"

namespace ys
{
	Animator::Animator() : Component(ComponentType::Animator), animations{}, activeAnimation{ nullptr }, isLoop(false)
	{
	}
	Animator::~Animator()
	{
	}
	void Animator::Init()
	{
	}
	void Animator::Update()
	{
		if (activeAnimation)
		{
			activeAnimation->Upadate();
			if (activeAnimation->IsComplete() && isLoop)
			{
				activeAnimation->Reset();
			}
		}
	}
	void Animator::LateUpdate()
	{
	}
	void Animator::Render(HDC hDC)
	{
		if (activeAnimation)
			activeAnimation->Render(hDC);
	}
	void Animator::CrateAnimation(const std::wstring& name, graphics::Texture* spriteSheet
		, const math::Vector2& leftTop, const math::Vector2& size, const math::Vector2& offset
		, const UINT lenth, const float duration)
	{
		Animation* animation{ nullptr };
		animation = FindAnimation(name);
		if (animation != nullptr)
			return;

		animation = new Animation();
		animation->CrateAnimation(name, spriteSheet
			, leftTop, size, offset, lenth, duration);
		animation->SetAnimatior(this);
		animations.insert(std::make_pair(name, animation));
	}
	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		auto iter = animations.find(name);
		if (iter == animations.end())
			return nullptr;

		return iter->second;
	}
	void Animator::PlayAnimation(const std::wstring& name, const bool loop)
	{
		Animation* animation = FindAnimation(name);
		if (animation == nullptr)
			return;

		activeAnimation = animation;
		activeAnimation->Reset();
		isLoop = loop;
	}
}