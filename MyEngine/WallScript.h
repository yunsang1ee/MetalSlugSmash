#pragma once
#include "..\\MyEngine_source\\ysGameObject.h"
#include <ysScript.h>
using namespace ys;
class WallScript : public Script
{
public:
	WallScript();
	~WallScript();
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Destroy();

	virtual void OnCollisionEnter(Collider* other) override;
	virtual void OnCollisionStay(Collider* other) override;
	virtual void OnCollisionExit(Collider* other) override;

private:
	
};

