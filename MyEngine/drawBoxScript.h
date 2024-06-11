#pragma once
#include "ysScript.h"
#include "ysGameObject.h"
using namespace ys;
class drawBoxScript : public Script
{
public:
	drawBoxScript();
	~drawBoxScript();

	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	void Release();

	std::vector<GameObject*> GetPlatform() { return platform; }

private:
	std::vector<GameObject*> platform;
	Vector2 lt;
	Vector2 rb;
};

