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
#include<ysCircleCollider2D.h>
#include <ysCollisionManager.h>
#include "STAGE1.h"
#include<random>
#include<ysAnimator.h>
#include<ysAnimation.h>
#include"PlayerLowerBodyScript.h"

extern ys::Application app;

namespace ys
{
	PlayerScript::PlayerScript() :  coolTime(0), count(0)
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
		if (coolTime >= 0)
			coolTime -= Timer::getDeltaTime();
		else
			coolTime = 0.0f;


		switch (state)
		{
		case PlayerScript::PlayerState::Idle:
			idle();
			break;
		case PlayerScript::PlayerState::Move:
			move();
			break;
		case PlayerState::Attack:
			attack();
			break;
		case PlayerState::Sit:
			sit();
			break;
		case PlayerState::Lookup:
			lookup();
			break;
		default:
			break;
		}
		

		auto tr = GetOwner()->GetComponent<Transform>();
		auto an = GetOwner()->GetComponent<Animator>();

		tr->SetPosition({ PlayerLowerBody->GetComponent<Transform>()->GetPosition().x, PlayerLowerBody->GetComponent<Transform>()->GetPosition().y-20 });
		
		
	}
	void PlayerScript::idle()
	{
		auto an = GetOwner()->GetComponent<Animator>();
		auto tr = GetOwner()->GetComponent<Transform>();
		
		if (InputManager::getKey(VK_LEFT))
		{
			state = PlayerState::Move;
			an->PlayAnimation(L"�÷��̾����̵���ü");
			tr->SetRotation(kPi);
		}
		if (InputManager::getKey(VK_RIGHT))
		{
			state = PlayerState::Move;
			an->PlayAnimation(L"�÷��̾���̵���ü");
			tr->SetRotation(kPi);
		}
		if (InputManager::getKeyDown(VK_SPACE))
		{
			state = PlayerState::Attack;
		}
	}
	void PlayerScript::move()
	{
		auto an = GetOwner()->GetComponent<Animator>();
		auto tr = GetOwner()->GetComponent<Transform>();
		if (InputManager::getKey(VK_LEFT))
		{
			state = PlayerState::Move;
			if (an->GetActive()->getName()!=L"�÷��̾����̵���ü")
			{
				an->PlayAnimation(L"�÷��̾����̵���ü");
			}
			
		}
		if (InputManager::getKey(VK_RIGHT))
		{
			state = PlayerState::Move;
			if (an->GetActive()->getName() != L"�÷��̾���̵���ü")
			{
				an->PlayAnimation(L"�÷��̾���̵���ü");
			}

		}
		if (InputManager::getKeyDown(VK_SPACE))
		{
			state = PlayerState::Attack;
		}
		if (InputManager::getKeyDown(VK_UP))
		{
			state = PlayerState::Lookup;
		}
		if (InputManager::getKeyDown(VK_DOWN))
		{
			state = PlayerState::Sit;
			//�ٿ��϶��� �ִϸ��̼ǲ���
			//�� ��� ��ġ ����
			//�ݸ��� ���� ���
		}
		
		if (!InputManager::getKey(VK_LEFT)&&!InputManager::getKey(VK_RIGHT))
		{
			an->PlayAnimation(L"�÷��̾���⺻");
			state = PlayerState::Idle;
		}
	}
	void PlayerScript::sit()
	{
		if (InputManager::getKeyUp(VK_DOWN))
		{
			state = PlayerState::Idle;
		}
		if (InputManager::getKeyDown(VK_OEM_COMMA))
		{
			state = PlayerState::Slide;
		}
		if (InputManager::getKey(VK_SPACE))
		{
			//�����̵��ϸ鼭 �ѽ��
		}
		
	}
	void PlayerScript::slide()
	{
		//�ִϸ��̼� ����
	}
	void PlayerScript::attack()
	{
		if (!coolTime)
		{
			ShootBullet();
			state = PlayerState::Idle;
		}
		
		
	}
	void PlayerScript::lookup()
	{
		if (InputManager::getKeyUp(VK_UP))
		{
			state = PlayerState::Idle;
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

		auto tr = GetOwner()->GetComponent<Transform>();
		Vector2 position = tr->GetPosition();
		Vector2 mousePosition =
			app.getmousePosition(); //+ Vector2(position.x - app.getScreen().x / 2, position.y - app.getScreen().y / 2);
		position = { position.x + 40, position.y - 40 };

		std::random_device rd;
		std::mt19937 engine(rd());
		std::uniform_real_distribution<> urd(-1.0, 1.0);
		auto bullet = object::Instantiate<GameObject>(LayerType::Projectile
			, Vector2(position.x, position.y) + Vector2::One * 10.0f * urd(engine));

		if (renderer::mainCamera)
			position = renderer::mainCamera->CalculatPosition(position);

		Vector2 dest = (mousePosition - position).nomalize();
		float degree = acosf(Vector2::Dot(Vector2::Right, dest));
		if (Vector2::Cross(Vector2::Right, dest) < 0)
			degree = 2 * math::kPi - degree;
		auto bulletTr = bullet->GetComponent<Transform>();
		bulletTr->SetRotation(degree);
		bulletTr->SetScale(Vector2::One * 1.5f);

		auto sr = bullet->AddComponent<SpriteRenderer>();
		sr->SetTexture(Resources::Find<graphics::Texture>(L"�Ѿ�png"));

		bullet->AddComponent<BulletScript>();
		bullet->AddComponent<BoxCollider2D>();
		count++;
		coolTime = 0.05f;//�ѽ�� �ִϸ��̼� duration����
		if (count == 5) count = 0;//���ӽŰ��� ��� �ѹ��� 5�߾� ��ϱ� �̷������� �־ ����
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