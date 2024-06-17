#pragma once
#include "ysScript.h"
namespace ys
{
    class BlockConstructorScript : public Script
    {
	public:
		BlockConstructorScript();
		~BlockConstructorScript();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hDC) override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		std::vector<GameObject*> blocks;
    };
}

