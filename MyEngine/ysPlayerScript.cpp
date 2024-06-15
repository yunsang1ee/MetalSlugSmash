#include "ysPlayerScript.h"
#include "ysGameObject.h"
#include "ysTimer.h"
#include "ysInputManager.h"
#include <ysTransform.h>
#include <ysObject.h>
#include "ysPlayer.h"
#include "YSapplication.h"
#include <ysSpriteRenderer.h>
#include <ysResources.h>
#include "ysEnemyScript.h"
#include "BulletScript.h"
#include <ysBoxCollider2D.h>
#include <ysRenderer.h>
#include <ysRigidBody.h>
#include <ysCircleCollider2D.h>
#include <ysCollisionManager.h>
#include "STAGE1.h"
#include<random>
#include<ysAnimator.h>
#include<ysAnimation.h>
#include"PlayerLowerBodyScript.h"
#include"ysSoundManager.h"
extern ys::Application app;

namespace ys
{
	PlayerScript::PlayerScript() : count(0)
	{
		
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Init()
	{

	}

	void PlayerScript::Update()
	{
		if (!ownerAnimator)
			ownerAnimator = GetOwner()->GetComponent<Animator>();
		if (!ownerTransform)
			ownerTransform = GetOwner()->GetComponent<Transform>();

		if (count != 0 && ownerAnimator->GetActive()->IsComplete())
			ShootBullet();

		ownerTransform->SetPosition({ playerLowerBody->GetComponent<Transform>()->GetPosition().x, playerLowerBody->GetComponent<Transform>()->GetPosition().y-20 });
		switch (state)
		{
		case PlayerScript::PlayerState::Idle:
			idle();
			break;
		case PlayerScript::PlayerState::IdleJump:
			idle_Jump();
			break;
		case PlayerScript::PlayerState::Move:
			move();
			break;
		case PlayerScript::PlayerState::Grenade:
			grenade();
			break;
		case PlayerScript::PlayerState::JumpGrenade:
			jump_Grenade();
			break;
		case PlayerScript::PlayerState::Sit:
			sit();
			break;
		case PlayerScript::PlayerState::LookDown:
			lookDown();
			break;
		case PlayerScript::PlayerState::LookDownAttack:
			lookDown_Attack();
			break;
		case PlayerScript::PlayerState::JumpAttack:
			jump_Attack();
			break;
		case PlayerScript::PlayerState::MoveJump:
			move_Jump();
			break;
		case PlayerScript::PlayerState::IdleAttack:
			idle_Attack();
			break;
		case PlayerScript::PlayerState::LookUp:
			lookUp();
			break;
		case PlayerScript::PlayerState::LookUpAttack:
			lookUp_Attack();
			break;
		default:
			break;
		}

	}

	void PlayerScript::idle()
	{
		if (InputManager::getKey(VK_OEM_COMMA))
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어가만점프좌", false);
			else
				ownerAnimator->PlayAnimation(L"플레이어가만점프", false);
			state = PlayerState::IdleJump;
			return;
		}
		if (InputManager::getKey(VK_LEFT))
		{
			attackDirection = kPi;
			GetOwner()->GetComponent<Transform>()->SetRotation(kPi);
			ownerAnimator->PlayAnimation(L"플레이어이동상체좌");
			state = PlayerState::Move;
			return;
		}
		if (InputManager::getKey(VK_RIGHT))
		{
			attackDirection = 0.0f;
			GetOwner()->GetComponent<Transform>()->SetRotation(0);
			ownerAnimator->PlayAnimation(L"플레이어이동상체");
			state = PlayerState::Move;
			return;
		}
		if (InputManager::getKey(VK_OEM_PERIOD))
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어가만총쏘는중상체좌", false);
			else
				ownerAnimator->PlayAnimation(L"플레이어가만총쏘는중상체", false);
			state = PlayerState::IdleAttack;
			return;
		}
		if (InputManager::getKey(VK_UP))
		{
			attackDirection = 3.0f * kPi / 2.0f;
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어기본총위상체좌");
			else
				ownerAnimator->PlayAnimation(L"플레이어기본총위상체");
			state = PlayerState::LookUp;
			return;
		}
		if (InputManager::getKey(VK_OEM_2))
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어가만수류탄좌", false);
			else
				ownerAnimator->PlayAnimation(L"플레이어가만수류탄", false);
			state = PlayerState::Grenade;
			return;
		}
		if (InputManager::getKey(VK_DOWN))
		{
			ownerAnimator->PlayAnimation(L"플레이어가만안보임");
			state = PlayerState::Sit;
			return;
		}
	}

	void PlayerScript::idle_Jump()
	{
		if (InputManager::getKey(VK_OEM_PERIOD) && playerLowerBody->GetComponent<RigidBody>()->IsGround())
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어점프총쏘는중상체좌", false);
			else
				ownerAnimator->PlayAnimation(L"플레이어점프총쏘는중상체", false);
			state = PlayerState::JumpAttack;
			return;
		}
		if (InputManager::getKey(VK_OEM_2))
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어점프수류탄좌", false);
			else
				ownerAnimator->PlayAnimation(L"플레이어점프수류탄", false);
			state = PlayerState::JumpGrenade;
			return;
		}
		if (InputManager::getKey(VK_DOWN))
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어기본총아래상체좌");
			else
				ownerAnimator->PlayAnimation(L"플레이어기본총아래상체");
			state = PlayerState::LookDown;
			return;
		}
		if (playerLowerBody->GetComponent<RigidBody>()->IsGround())
		{
			std::wstring animationName;

			animationName = L"플레이어이동상체";
			state = PlayerState::Move;
			if (InputManager::getKey(VK_LEFT))
			{
				attackDirection = kPi;
				ownerTransform->SetRotation(kPi);
			}
			else if (InputManager::getKey(VK_RIGHT))
			{
				attackDirection = 0.0f;
				ownerTransform->SetRotation(0);
			}
			else
			{
				animationName = L"플레이어가만기본";
				state = PlayerState::Idle;
			}

			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(animationName + L"좌");
			else
				ownerAnimator->PlayAnimation(animationName);
			return;
		}
	}

	void PlayerScript::move()
	{
		if (InputManager::getKey(VK_OEM_COMMA))
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어이동점프좌", false);
			else
				ownerAnimator->PlayAnimation(L"플레이어이동점프", false);
			state = PlayerState::MoveJump;
			return;
		}
		if (InputManager::getKey(VK_OEM_PERIOD))
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어가만총쏘는중상체좌", false);
			else
				ownerAnimator->PlayAnimation(L"플레이어가만총쏘는중상체", false);
			state = PlayerState::IdleAttack;
			return;
		}
		if (InputManager::getKey(VK_UP))
		{
			attackDirection = 3.0f * kPi / 2.0f;
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어기본총위상체좌");
			else
				ownerAnimator->PlayAnimation(L"플레이어기본총위상체");
			state = PlayerState::LookUp;
			return;
		}
		if (InputManager::getKey(VK_OEM_2))
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어가만수류탄좌", false);
			else
				ownerAnimator->PlayAnimation(L"플레이어가만수류탄", false);
			state = PlayerState::Grenade;
			return;
		}
		if (InputManager::getKey(VK_DOWN))
		{
			ownerAnimator->PlayAnimation(L"플레이어가만안보임");
			state = PlayerState::Sit;
			return;
		}


		if (InputManager::getKeyUp(VK_LEFT))
		{
			ownerAnimator->PlayAnimation(L"플레이어가만기본좌", true);
			state = PlayerState::Idle;
			return;
		}
		if (InputManager::getKeyUp(VK_RIGHT))
		{
			ownerAnimator->PlayAnimation(L"플레이어가만기본", true);
			state = PlayerState::Idle;
			return;
		}
	}

	void PlayerScript::grenade()
	{
		if (ownerAnimator->IsComplete() && playerLowerBody->GetComponent<RigidBody>()->IsGround())
		{
			std::wstring animationName;
			animationName = L"플레이어이동상체";
			state = PlayerState::Move;
			if (InputManager::getKey(VK_LEFT))
			{
				attackDirection = kPi;
				ownerTransform->SetRotation(kPi);
			}
			else if (InputManager::getKey(VK_RIGHT))
			{
				attackDirection = 0.0f;
				ownerTransform->SetRotation(0);
			}
			else
			{
				animationName = L"플레이어가만기본";
				state = PlayerState::Idle;
			}

			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(animationName + L"좌");
			else
				ownerAnimator->PlayAnimation(animationName);
		}
	}

	void PlayerScript::jump_Grenade()
	{
		if (ownerAnimator->IsComplete())
		{
			std::wstring animationName;
			if (playerLowerBody->GetComponent<RigidBody>()->IsGround())
			{
				animationName = L"플레이어이동상체";
				state = PlayerState::Move;
				if (InputManager::getKey(VK_LEFT))
				{
					attackDirection = kPi;
					ownerTransform->SetRotation(kPi);
				}
				else if (InputManager::getKey(VK_RIGHT))
				{
					attackDirection = 0.0f;
					ownerTransform->SetRotation(0);
				}
				else
				{
					animationName = L"플레이어가만기본";
					state = PlayerState::Idle;
				}

				if (ownerTransform->GetRotation() == kPi)
					ownerAnimator->PlayAnimation(animationName + L"좌");
				else
					ownerAnimator->PlayAnimation(animationName);
			}
			else
			{
				animationName = L"플레이어이동점프";
				state = PlayerState::MoveJump;
				if (InputManager::getKey(VK_LEFT))
				{
					attackDirection = kPi;
					ownerTransform->SetRotation(kPi);
				}
				else if (InputManager::getKey(VK_RIGHT))
				{
					attackDirection = 0.0f;
					ownerTransform->SetRotation(0);
				}
				else
				{
					animationName = L"플레이어가만점프";
					state = PlayerState::IdleJump;
				}

				if (ownerTransform->GetRotation() == kPi)
					ownerAnimator->PlayAnimation(animationName + L"좌", false);
				else
					ownerAnimator->PlayAnimation(animationName, false);
			}
		}
	}

	void PlayerScript::sit()
	{
		if (InputManager::getKeyUp(VK_DOWN))
		{
			std::wstring animationName;

			animationName = L"플레이어이동상체";
			state = PlayerState::Move;
			if (InputManager::getKey(VK_LEFT))
			{
				attackDirection = kPi;
				ownerTransform->SetRotation(kPi);
			}
			else if (InputManager::getKey(VK_RIGHT))
			{
				attackDirection = 0.0f;
				ownerTransform->SetRotation(0);
			}
			else
			{
				animationName = L"플레이어가만기본";
				state = PlayerState::Idle;
			}

			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(animationName + L"좌");
			else
				ownerAnimator->PlayAnimation(animationName);
			return;
		}
	}

	void PlayerScript::lookDown()
	{
		if (InputManager::getKey(VK_OEM_PERIOD))
		{
			attackDirection = kPi / 2.0f;
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어아래총쏘는중상체좌", false);
			else
				ownerAnimator->PlayAnimation(L"플레이어아래총쏘는중상체", false);
			state = PlayerState::LookDownAttack;
			return;
		}

		if (InputManager::getKeyUp(VK_DOWN) || playerLowerBody->GetComponent<RigidBody>()->IsGround())
		{
			std::wstring animationName;

			animationName = L"플레이어이동상체";
			state = PlayerState::Move;
			if (InputManager::getKey(VK_LEFT))
			{
				attackDirection = kPi;
				ownerTransform->SetRotation(kPi);
			}
			else if (InputManager::getKey(VK_RIGHT))
			{
				attackDirection = 0.0f;
				ownerTransform->SetRotation(0);
			}
			else
			{
				animationName = L"플레이어가만기본";
				state = PlayerState::Idle;
			}
			
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(animationName + L"좌");
			else
				ownerAnimator->PlayAnimation(animationName);
			return;
		}
	}

	void PlayerScript::lookDown_Attack()
	{
		if (!ownerAnimator->IsComplete())
			return;
		if (InputManager::getKey(VK_OEM_PERIOD))
		{
			if (playerLowerBody->GetComponent<RigidBody>()->IsGround())
			{
				if (ownerTransform->GetRotation() == kPi)
				{
					ownerAnimator->PlayAnimation(L"플레이어가만총쏘는중상체좌", false);
					attackDirection = kPi;
				}
				else
				{
					ownerAnimator->PlayAnimation(L"플레이어가만총쏘는중상체", false);
					attackDirection = 0.0f;
				}
				state = PlayerState::IdleAttack;
			}
			else
			{
				if (ownerTransform->GetRotation() == kPi)
					ownerAnimator->PlayAnimation(L"플레이어아래총쏘는중상체좌", false);
				else
					ownerAnimator->PlayAnimation(L"플레이어아래총쏘는중상체", false);
			}
		}
		else if (!playerLowerBody->GetComponent<RigidBody>()->IsGround())
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어이동점프좌", false);
			else
				ownerAnimator->PlayAnimation(L"플레이어이동점프", false);
			state = PlayerState::MoveJump;
		}
		else
		{
			std::wstring animationName;

			animationName = L"플레이어이동상체";
			state = PlayerState::Move;
			if (InputManager::getKey(VK_LEFT))
			{
				attackDirection = kPi;
				ownerTransform->SetRotation(kPi);
			}
			else if (InputManager::getKey(VK_RIGHT))
			{
				attackDirection = 0.0f;
				ownerTransform->SetRotation(0);
			}
			else
			{
				animationName = L"플레이어가만기본";
				state = PlayerState::Idle;
			}

			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(animationName + L"좌");
			else
				ownerAnimator->PlayAnimation(animationName);
			return;
		}
	}

	void PlayerScript::jump_Attack()
	{
		if (!ownerAnimator->IsComplete())
			return;
		if (InputManager::getKey(VK_OEM_PERIOD))
		{
			if (InputManager::getKey(VK_UP))
			{
				attackDirection = kPi / 2.0f;
				state = PlayerState::LookUpAttack;
			}
			else if (playerLowerBody->GetComponent<RigidBody>()->IsGround())
			{
				if (ownerTransform->GetRotation() == kPi)
				{
					ownerAnimator->PlayAnimation(L"플레이어점프총쏘는중상체좌", false);
					attackDirection = kPi;
				}
				else
				{
					ownerAnimator->PlayAnimation(L"플레이어점프총쏘는중상체", false);
					attackDirection = 0.0f;
				}
				state = PlayerState::IdleAttack;
			}
			else
			{
				if (ownerTransform->GetRotation() == kPi)
					ownerAnimator->PlayAnimation(L"플레이어점프총쏘는중상체좌", false);
				else
					ownerAnimator->PlayAnimation(L"플레이어점프총쏘는중상체", false);
			}
		}
		else if(!playerLowerBody->GetComponent<RigidBody>()->IsGround())
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어이동점프좌", false);
			else
				ownerAnimator->PlayAnimation(L"플레이어이동점프", false);
			state = PlayerState::MoveJump;
		}
		else
		{
			std::wstring animationName;

			animationName = L"플레이어이동상체";
			state = PlayerState::Move;
			if (InputManager::getKey(VK_LEFT))
			{
				attackDirection = kPi;
				ownerTransform->SetRotation(kPi);
			}
			else if (InputManager::getKey(VK_RIGHT))
			{
				attackDirection = 0.0f;
				ownerTransform->SetRotation(0);
			}
			else
			{
				animationName = L"플레이어가만기본";
				state = PlayerState::Idle;
			}

			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(animationName + L"좌");
			else
				ownerAnimator->PlayAnimation(animationName);
			return;
		}
	}

	void PlayerScript::move_Jump()
	{
		if (InputManager::getKey(VK_OEM_PERIOD))
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어점프총쏘는중상체좌", false);
			else
				ownerAnimator->PlayAnimation(L"플레이어점프총쏘는중상체", false);
			state = PlayerState::JumpAttack;
			return;
		}
		if (InputManager::getKey(VK_OEM_2))
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어가만수류탄좌", false);
			else
				ownerAnimator->PlayAnimation(L"플레이어가만수류탄", false);
			state = PlayerState::JumpGrenade;
			return;
		}
		if (InputManager::getKey(VK_DOWN))
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어기본총아래상체좌");
			else
				ownerAnimator->PlayAnimation(L"플레이어기본총아래상체");
			state = PlayerState::LookDown;
			return;
		}
		if (playerLowerBody->GetComponent<RigidBody>()->IsGround())
		{
			std::wstring animationName;

			animationName = L"플레이어이동상체";
			state = PlayerState::Move;
			if (InputManager::getKey(VK_LEFT))
			{
				attackDirection = kPi;
				ownerTransform->SetRotation(kPi);
			}
			else if (InputManager::getKey(VK_RIGHT))
			{
				attackDirection = 0.0f;
				ownerTransform->SetRotation(0);
			}
			else
			{
				animationName = L"플레이어가만기본";
				state = PlayerState::Idle;
			}

			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(animationName + L"좌");
			else
				ownerAnimator->PlayAnimation(animationName);
			return;
		}
	}
	void PlayerScript::idle_Attack()
	{
		//보고있는 방향으로 총쏘기
		if (!ownerAnimator->IsComplete())
			return;
		if (InputManager::getKey(VK_OEM_PERIOD))
		{
			if (InputManager::getKey(VK_UP))
			{
				attackDirection = kPi / 2.0f;
				state = PlayerState::LookUpAttack;
			}
			else if (InputManager::getKey(VK_LEFT))
			{
				attackDirection = kPi;
				ownerTransform->SetRotation(kPi);
				ownerAnimator->PlayAnimation(L"플레이어가만총쏘는중상체좌", false);
			}
			else if (InputManager::getKey(VK_RIGHT))
			{
				attackDirection = 0.0f;
				ownerTransform->SetRotation(0);
				ownerAnimator->PlayAnimation(L"플레이어가만총쏘는중상체", false);
			}
			else
			{
				if (ownerTransform->GetRotation() == kPi)
					ownerAnimator->PlayAnimation(L"플레이어가만총쏘는중상체좌", false);
				else
					ownerAnimator->PlayAnimation(L"플레이어가만총쏘는중상체", false);
			}
		}
		else
		{
			std::wstring animationName;

			animationName = L"플레이어이동상체";
			state = PlayerState::Move;
			if (InputManager::getKey(VK_LEFT))
			{
				attackDirection = kPi;
				ownerTransform->SetRotation(kPi);
			}
			else if (InputManager::getKey(VK_RIGHT))
			{
				attackDirection = 0.0f;
				ownerTransform->SetRotation(0);
			}
			else
			{
				animationName = L"플레이어가만기본";
				state = PlayerState::Idle;
			}

			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(animationName + L"좌");
			else
				ownerAnimator->PlayAnimation(animationName);
			return;
		}
	}

	void PlayerScript::lookUp()
	{
		if (InputManager::getKey(VK_OEM_PERIOD))
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어위총쏘는중상체좌", false);
			else
				ownerAnimator->PlayAnimation(L"플레이어위총쏘는중상체", false);
			state = PlayerState::LookUpAttack;
			return;
		}

		if (InputManager::getKeyUp(VK_UP))
		{
			std::wstring animationName;

			animationName = L"플레이어이동상체";
			state = PlayerState::Move;
			if (InputManager::getKey(VK_LEFT))
			{
				attackDirection = kPi;
				ownerTransform->SetRotation(kPi);
			}
			else if (InputManager::getKey(VK_RIGHT))
			{
				attackDirection = 0.0f;
				ownerTransform->SetRotation(0);
			}
			else
			{
				animationName = L"플레이어가만기본";
				state = PlayerState::Idle;
			}

			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(animationName + L"좌");
			else
				ownerAnimator->PlayAnimation(animationName);
			return;
		}
	}

	void PlayerScript::lookUp_Attack()
	{
		if (!ownerAnimator->IsComplete())
			return;
		if (InputManager::getKey(VK_OEM_PERIOD))
		{
			if (InputManager::getKey(VK_LEFT))
			{
				attackDirection = kPi;
				ownerTransform->SetRotation(kPi);
				ownerAnimator->PlayAnimation(L"플레이어위총쏘는중상체좌", false);
			}
			else if (InputManager::getKey(VK_RIGHT))
			{
				attackDirection = 0.0f;
				ownerTransform->SetRotation(0);
				ownerAnimator->PlayAnimation(L"플레이어위총쏘는중상체", false);
			}
			else
			{
				if (ownerTransform->GetRotation() == kPi)
					ownerAnimator->PlayAnimation(L"플레이어위총쏘는중상체좌", false);
				else
					ownerAnimator->PlayAnimation(L"플레이어위총쏘는중상체", false);
			}
		}
		else if (InputManager::getKey(VK_UP))
		{
			attackDirection = 3.0f * kPi / 2.0f;
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어기본총위상체좌");
			else
				ownerAnimator->PlayAnimation(L"플레이어기본총위상체");
			state = PlayerState::LookUp;
		}
		else
		{
			std::wstring animationName;

			animationName = L"플레이어이동상체";
			state = PlayerState::Move;
			if (InputManager::getKey(VK_LEFT))
			{
				attackDirection = kPi;
				ownerTransform->SetRotation(kPi);
			}
			else if (InputManager::getKey(VK_RIGHT))
			{
				attackDirection = 0.0f;
				ownerTransform->SetRotation(0);
			}
			else
			{
				animationName = L"플레이어가만기본";
				state = PlayerState::Idle;
			}

			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(animationName + L"좌");
			else
				ownerAnimator->PlayAnimation(animationName);
		}
	}

	void PlayerScript::LateUpdate()
	{
	}

	void PlayerScript::Render(HDC hDC)
	{
	}

	void PlayerScript::ShootBullet()
	{
		bulletOffset = Vector2::Rotate(Vector2::Right, attackDirection) * 80 - Vector2(0, 30); //총까지 길이가 80정도
		Vector2 bulletPosition = ownerTransform->GetPosition() + bulletOffset;
		//Vector2 mousePosition =
		//	app.getmousePosition(); //+ Vector2(position.x - app.getScreen().x / 2, position.y - app.getScreen().y / 2);

		std::random_device rd;
		std::mt19937 engine(rd());
		std::uniform_real_distribution<> urd(-1.0, 1.0);
		auto bullet = object::Instantiate<GameObject>(LayerType::Projectile
			, bulletPosition + Vector2::One * 8.0f * urd(engine));

		//Vector2 dest = (mousePosition - bulletStartPos).nomalize();
		/*float degree = acosf(Vector2::Dot(Vector2::Right, direction));
		if (Vector2::Cross(Vector2::Right, direction) < 0)
			degree = 2 * math::kPi - degree;*/
		auto bulletTr = bullet->GetComponent<Transform>();
		bulletTr->SetRotation(attackDirection);

		auto sr = bullet->AddComponent<SpriteRenderer>();
		sr->SetTexture(Resources::Find<graphics::Texture>(L"총알png"));

		bullet->AddComponent<BulletScript>();
		auto cd = bullet->AddComponent<CircleCollider2D>();
		cd->SetSize(Vector2::One * 0.2f);

		const auto& aniName = ownerAnimator->GetActive()->getName();

		if (aniName == L"플레이어가만총쏘는중상체")
		{
			count = 0;
		}
		else if(aniName == L"플레이어가만헤비쏘는중상체")
		{
			count++;
			if (count == 5) count = 0;
		}
		else if(aniName == L"플레이어가만쌍헤비쏘는중상체")
		{
			auto bulletTwo = object::Instantiate<GameObject>(LayerType::Projectile
				, bulletPosition + Vector2::One * 10.0f * urd(engine));
			auto bulletTwoTr = bulletTwo->GetComponent<Transform>();
			bulletTwoTr->SetRotation(attackDirection);

			auto bulletTwoSr = bulletTwo->AddComponent<SpriteRenderer>();
			bulletTwoSr->SetTexture(Resources::Find<graphics::Texture>(L"총알png"));

			bulletTwo->AddComponent<BulletScript>();
			auto bulletTwoCd = bulletTwo->AddComponent<CircleCollider2D>();
			bulletTwoCd->SetSize(Vector2::One * 0.2f);
			count++;
			if (count == 5) count = 0;
		}
	}

	void PlayerScript::ThrowGrenade()
	{

	}

	void PlayerScript::ShootEnd()
	{
		if (InputManager::getKey(VK_OEM_PERIOD))
			return;

		const auto& aniName = ownerAnimator->GetActive()->getName();
		auto type = aniName.substr(4, 2);
		if (type == L"가만")
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어가만총쏘기상체좌", false);
			else
				ownerAnimator->PlayAnimation(L"플레이어가만총쏘기상체", false);
		}
		else if (type == L"점프")
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어점프총쏘기상체좌", false);
			else
				ownerAnimator->PlayAnimation(L"플레이어점프총쏘기상체", false);
		}
		else if (type == L"위총")
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어위총쏘기상체좌", false);
			else
				ownerAnimator->PlayAnimation(L"플레이어위총쏘기상체", false);
		}
		else if (type == L"아래")
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"플레이어아래총쏘기상체좌", false);
			else
				ownerAnimator->PlayAnimation(L"플레이어아래총쏘기상체", false);
		}
	}

	void PlayerScript::OnCollisionEnter(Collider* other)
	{
		
	}

	void PlayerScript::OnCollisionStay(Collider* other)
	{
		
	}

	void PlayerScript::OnCollisionExit(Collider* other)
	{

	}
}