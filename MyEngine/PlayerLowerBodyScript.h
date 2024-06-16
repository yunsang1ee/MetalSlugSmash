#pragma once
#include "ysScript.h"
#include"ysAnimator.h"
using namespace ys;
class PlayerLowerBodyScript : public Script
{
public:
	enum class PlayerState
	{
		Idle, Move, Sit, SitShoot, Slide, Attack, Damaged, Lookup, Jump, IdleJump, MoveJump
	};

public:
	PlayerLowerBodyScript();
	~PlayerLowerBodyScript();

	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;

	void SetPlayerChest(GameObject* playerChest) { this->playerChest = playerChest; }
	GameObject* GetPlayerChest() { return playerChest; }
	PlayerState GetState() { return state; }

	virtual void OnCollisionEnter(class Collider* other) override;
	virtual void OnCollisionStay(class Collider* other) override;
	virtual void OnCollisionExit(class Collider* other) override;
	void NextSitAnimation();
	void Revival();

private:
	void idle();
	void move();
	void sit();
	void jump();
	void idleJump();
	void moveJump();
	void lookUp();
	void lookUpMove();
	void slide();
	void attack();
	void damaged();
	
private:
	math::Vector2 Direction;
	GameObject* playerChest;
	PlayerState state;
	float speed;
	Animator* an;
};

