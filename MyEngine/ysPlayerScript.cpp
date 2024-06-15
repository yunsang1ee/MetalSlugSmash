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
				ownerAnimator->PlayAnimation(L"�÷��̾��������", false);
			else
				ownerAnimator->PlayAnimation(L"�÷��̾������", false);
			state = PlayerState::IdleJump;
			return;
		}
		if (InputManager::getKey(VK_LEFT))
		{
			attackDirection = kPi;
			GetOwner()->GetComponent<Transform>()->SetRotation(kPi);
			ownerAnimator->PlayAnimation(L"�÷��̾��̵���ü��");
			state = PlayerState::Move;
			return;
		}
		if (InputManager::getKey(VK_RIGHT))
		{
			attackDirection = 0.0f;
			GetOwner()->GetComponent<Transform>()->SetRotation(0);
			ownerAnimator->PlayAnimation(L"�÷��̾��̵���ü");
			state = PlayerState::Move;
			return;
		}
		if (InputManager::getKey(VK_OEM_PERIOD))
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"�÷��̾���ѽ���߻�ü��", false);
			else
				ownerAnimator->PlayAnimation(L"�÷��̾���ѽ���߻�ü", false);
			state = PlayerState::IdleAttack;
			return;
		}
		if (InputManager::getKey(VK_UP))
		{
			attackDirection = 3.0f * kPi / 2.0f;
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"�÷��̾�⺻������ü��");
			else
				ownerAnimator->PlayAnimation(L"�÷��̾�⺻������ü");
			state = PlayerState::LookUp;
			return;
		}
		if (InputManager::getKey(VK_OEM_2))
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"�÷��̾������ź��", false);
			else
				ownerAnimator->PlayAnimation(L"�÷��̾������ź", false);
			state = PlayerState::Grenade;
			return;
		}
		if (InputManager::getKey(VK_DOWN))
		{
			ownerAnimator->PlayAnimation(L"�÷��̾���Ⱥ���");
			state = PlayerState::Sit;
			return;
		}
	}

	void PlayerScript::idle_Jump()
	{
		if (InputManager::getKey(VK_OEM_PERIOD) && playerLowerBody->GetComponent<RigidBody>()->IsGround())
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"�÷��̾������ѽ���߻�ü��", false);
			else
				ownerAnimator->PlayAnimation(L"�÷��̾������ѽ���߻�ü", false);
			state = PlayerState::JumpAttack;
			return;
		}
		if (InputManager::getKey(VK_OEM_2))
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"�÷��̾���������ź��", false);
			else
				ownerAnimator->PlayAnimation(L"�÷��̾���������ź", false);
			state = PlayerState::JumpGrenade;
			return;
		}
		if (InputManager::getKey(VK_DOWN))
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"�÷��̾�⺻�ѾƷ���ü��");
			else
				ownerAnimator->PlayAnimation(L"�÷��̾�⺻�ѾƷ���ü");
			state = PlayerState::LookDown;
			return;
		}
		if (playerLowerBody->GetComponent<RigidBody>()->IsGround())
		{
			std::wstring animationName;

			animationName = L"�÷��̾��̵���ü";
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
				animationName = L"�÷��̾���⺻";
				state = PlayerState::Idle;
			}

			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(animationName + L"��");
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
				ownerAnimator->PlayAnimation(L"�÷��̾��̵�������", false);
			else
				ownerAnimator->PlayAnimation(L"�÷��̾��̵�����", false);
			state = PlayerState::MoveJump;
			return;
		}
		if (InputManager::getKey(VK_OEM_PERIOD))
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"�÷��̾���ѽ���߻�ü��", false);
			else
				ownerAnimator->PlayAnimation(L"�÷��̾���ѽ���߻�ü", false);
			state = PlayerState::IdleAttack;
			return;
		}
		if (InputManager::getKey(VK_UP))
		{
			attackDirection = 3.0f * kPi / 2.0f;
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"�÷��̾�⺻������ü��");
			else
				ownerAnimator->PlayAnimation(L"�÷��̾�⺻������ü");
			state = PlayerState::LookUp;
			return;
		}
		if (InputManager::getKey(VK_OEM_2))
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"�÷��̾������ź��", false);
			else
				ownerAnimator->PlayAnimation(L"�÷��̾������ź", false);
			state = PlayerState::Grenade;
			return;
		}
		if (InputManager::getKey(VK_DOWN))
		{
			ownerAnimator->PlayAnimation(L"�÷��̾���Ⱥ���");
			state = PlayerState::Sit;
			return;
		}


		if (InputManager::getKeyUp(VK_LEFT))
		{
			ownerAnimator->PlayAnimation(L"�÷��̾���⺻��", true);
			state = PlayerState::Idle;
			return;
		}
		if (InputManager::getKeyUp(VK_RIGHT))
		{
			ownerAnimator->PlayAnimation(L"�÷��̾���⺻", true);
			state = PlayerState::Idle;
			return;
		}
	}

	void PlayerScript::grenade()
	{
		if (ownerAnimator->IsComplete() && playerLowerBody->GetComponent<RigidBody>()->IsGround())
		{
			std::wstring animationName;
			animationName = L"�÷��̾��̵���ü";
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
				animationName = L"�÷��̾���⺻";
				state = PlayerState::Idle;
			}

			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(animationName + L"��");
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
				animationName = L"�÷��̾��̵���ü";
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
					animationName = L"�÷��̾���⺻";
					state = PlayerState::Idle;
				}

				if (ownerTransform->GetRotation() == kPi)
					ownerAnimator->PlayAnimation(animationName + L"��");
				else
					ownerAnimator->PlayAnimation(animationName);
			}
			else
			{
				animationName = L"�÷��̾��̵�����";
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
					animationName = L"�÷��̾������";
					state = PlayerState::IdleJump;
				}

				if (ownerTransform->GetRotation() == kPi)
					ownerAnimator->PlayAnimation(animationName + L"��", false);
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

			animationName = L"�÷��̾��̵���ü";
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
				animationName = L"�÷��̾���⺻";
				state = PlayerState::Idle;
			}

			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(animationName + L"��");
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
				ownerAnimator->PlayAnimation(L"�÷��̾�Ʒ��ѽ���߻�ü��", false);
			else
				ownerAnimator->PlayAnimation(L"�÷��̾�Ʒ��ѽ���߻�ü", false);
			state = PlayerState::LookDownAttack;
			return;
		}

		if (InputManager::getKeyUp(VK_DOWN) || playerLowerBody->GetComponent<RigidBody>()->IsGround())
		{
			std::wstring animationName;

			animationName = L"�÷��̾��̵���ü";
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
				animationName = L"�÷��̾���⺻";
				state = PlayerState::Idle;
			}
			
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(animationName + L"��");
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
					ownerAnimator->PlayAnimation(L"�÷��̾���ѽ���߻�ü��", false);
					attackDirection = kPi;
				}
				else
				{
					ownerAnimator->PlayAnimation(L"�÷��̾���ѽ���߻�ü", false);
					attackDirection = 0.0f;
				}
				state = PlayerState::IdleAttack;
			}
			else
			{
				if (ownerTransform->GetRotation() == kPi)
					ownerAnimator->PlayAnimation(L"�÷��̾�Ʒ��ѽ���߻�ü��", false);
				else
					ownerAnimator->PlayAnimation(L"�÷��̾�Ʒ��ѽ���߻�ü", false);
			}
		}
		else if (!playerLowerBody->GetComponent<RigidBody>()->IsGround())
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"�÷��̾��̵�������", false);
			else
				ownerAnimator->PlayAnimation(L"�÷��̾��̵�����", false);
			state = PlayerState::MoveJump;
		}
		else
		{
			std::wstring animationName;

			animationName = L"�÷��̾��̵���ü";
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
				animationName = L"�÷��̾���⺻";
				state = PlayerState::Idle;
			}

			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(animationName + L"��");
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
					ownerAnimator->PlayAnimation(L"�÷��̾������ѽ���߻�ü��", false);
					attackDirection = kPi;
				}
				else
				{
					ownerAnimator->PlayAnimation(L"�÷��̾������ѽ���߻�ü", false);
					attackDirection = 0.0f;
				}
				state = PlayerState::IdleAttack;
			}
			else
			{
				if (ownerTransform->GetRotation() == kPi)
					ownerAnimator->PlayAnimation(L"�÷��̾������ѽ���߻�ü��", false);
				else
					ownerAnimator->PlayAnimation(L"�÷��̾������ѽ���߻�ü", false);
			}
		}
		else if(!playerLowerBody->GetComponent<RigidBody>()->IsGround())
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"�÷��̾��̵�������", false);
			else
				ownerAnimator->PlayAnimation(L"�÷��̾��̵�����", false);
			state = PlayerState::MoveJump;
		}
		else
		{
			std::wstring animationName;

			animationName = L"�÷��̾��̵���ü";
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
				animationName = L"�÷��̾���⺻";
				state = PlayerState::Idle;
			}

			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(animationName + L"��");
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
				ownerAnimator->PlayAnimation(L"�÷��̾������ѽ���߻�ü��", false);
			else
				ownerAnimator->PlayAnimation(L"�÷��̾������ѽ���߻�ü", false);
			state = PlayerState::JumpAttack;
			return;
		}
		if (InputManager::getKey(VK_OEM_2))
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"�÷��̾������ź��", false);
			else
				ownerAnimator->PlayAnimation(L"�÷��̾������ź", false);
			state = PlayerState::JumpGrenade;
			return;
		}
		if (InputManager::getKey(VK_DOWN))
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"�÷��̾�⺻�ѾƷ���ü��");
			else
				ownerAnimator->PlayAnimation(L"�÷��̾�⺻�ѾƷ���ü");
			state = PlayerState::LookDown;
			return;
		}
		if (playerLowerBody->GetComponent<RigidBody>()->IsGround())
		{
			std::wstring animationName;

			animationName = L"�÷��̾��̵���ü";
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
				animationName = L"�÷��̾���⺻";
				state = PlayerState::Idle;
			}

			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(animationName + L"��");
			else
				ownerAnimator->PlayAnimation(animationName);
			return;
		}
	}
	void PlayerScript::idle_Attack()
	{
		//�����ִ� �������� �ѽ��
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
				ownerAnimator->PlayAnimation(L"�÷��̾���ѽ���߻�ü��", false);
			}
			else if (InputManager::getKey(VK_RIGHT))
			{
				attackDirection = 0.0f;
				ownerTransform->SetRotation(0);
				ownerAnimator->PlayAnimation(L"�÷��̾���ѽ���߻�ü", false);
			}
			else
			{
				if (ownerTransform->GetRotation() == kPi)
					ownerAnimator->PlayAnimation(L"�÷��̾���ѽ���߻�ü��", false);
				else
					ownerAnimator->PlayAnimation(L"�÷��̾���ѽ���߻�ü", false);
			}
		}
		else
		{
			std::wstring animationName;

			animationName = L"�÷��̾��̵���ü";
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
				animationName = L"�÷��̾���⺻";
				state = PlayerState::Idle;
			}

			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(animationName + L"��");
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
				ownerAnimator->PlayAnimation(L"�÷��̾����ѽ���߻�ü��", false);
			else
				ownerAnimator->PlayAnimation(L"�÷��̾����ѽ���߻�ü", false);
			state = PlayerState::LookUpAttack;
			return;
		}

		if (InputManager::getKeyUp(VK_UP))
		{
			std::wstring animationName;

			animationName = L"�÷��̾��̵���ü";
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
				animationName = L"�÷��̾���⺻";
				state = PlayerState::Idle;
			}

			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(animationName + L"��");
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
				ownerAnimator->PlayAnimation(L"�÷��̾����ѽ���߻�ü��", false);
			}
			else if (InputManager::getKey(VK_RIGHT))
			{
				attackDirection = 0.0f;
				ownerTransform->SetRotation(0);
				ownerAnimator->PlayAnimation(L"�÷��̾����ѽ���߻�ü", false);
			}
			else
			{
				if (ownerTransform->GetRotation() == kPi)
					ownerAnimator->PlayAnimation(L"�÷��̾����ѽ���߻�ü��", false);
				else
					ownerAnimator->PlayAnimation(L"�÷��̾����ѽ���߻�ü", false);
			}
		}
		else if (InputManager::getKey(VK_UP))
		{
			attackDirection = 3.0f * kPi / 2.0f;
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"�÷��̾�⺻������ü��");
			else
				ownerAnimator->PlayAnimation(L"�÷��̾�⺻������ü");
			state = PlayerState::LookUp;
		}
		else
		{
			std::wstring animationName;

			animationName = L"�÷��̾��̵���ü";
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
				animationName = L"�÷��̾���⺻";
				state = PlayerState::Idle;
			}

			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(animationName + L"��");
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
		bulletOffset = Vector2::Rotate(Vector2::Right, attackDirection) * 80 - Vector2(0, 30); //�ѱ��� ���̰� 80����
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
		sr->SetTexture(Resources::Find<graphics::Texture>(L"�Ѿ�png"));

		bullet->AddComponent<BulletScript>();
		auto cd = bullet->AddComponent<CircleCollider2D>();
		cd->SetSize(Vector2::One * 0.2f);

		const auto& aniName = ownerAnimator->GetActive()->getName();

		if (aniName == L"�÷��̾���ѽ���߻�ü")
		{
			count = 0;
		}
		else if(aniName == L"�÷��̾��������߻�ü")
		{
			count++;
			if (count == 5) count = 0;
		}
		else if(aniName == L"�÷��̾����������߻�ü")
		{
			auto bulletTwo = object::Instantiate<GameObject>(LayerType::Projectile
				, bulletPosition + Vector2::One * 10.0f * urd(engine));
			auto bulletTwoTr = bulletTwo->GetComponent<Transform>();
			bulletTwoTr->SetRotation(attackDirection);

			auto bulletTwoSr = bulletTwo->AddComponent<SpriteRenderer>();
			bulletTwoSr->SetTexture(Resources::Find<graphics::Texture>(L"�Ѿ�png"));

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
		if (type == L"����")
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"�÷��̾���ѽ���ü��", false);
			else
				ownerAnimator->PlayAnimation(L"�÷��̾���ѽ���ü", false);
		}
		else if (type == L"����")
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"�÷��̾������ѽ���ü��", false);
			else
				ownerAnimator->PlayAnimation(L"�÷��̾������ѽ���ü", false);
		}
		else if (type == L"����")
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"�÷��̾����ѽ���ü��", false);
			else
				ownerAnimator->PlayAnimation(L"�÷��̾����ѽ���ü", false);
		}
		else if (type == L"�Ʒ�")
		{
			if (ownerTransform->GetRotation() == kPi)
				ownerAnimator->PlayAnimation(L"�÷��̾�Ʒ��ѽ���ü��", false);
			else
				ownerAnimator->PlayAnimation(L"�÷��̾�Ʒ��ѽ���ü", false);
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