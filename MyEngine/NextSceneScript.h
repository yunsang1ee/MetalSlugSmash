#pragma once
#include <ysScript.h>
namespace ys
{
	class NextSceneScript : public Script
	{
	public:
		NextSceneScript();
		~NextSceneScript();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hDC) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		GameObject* start;
		bool isNext;
	};
}

