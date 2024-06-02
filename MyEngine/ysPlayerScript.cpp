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
	PlayerScript::PlayerScript() : coolTime(0), count(0)
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

		auto tr = GetOwner()->GetComponent<Transform>();
		bulletStartPos = tr->GetPosition();
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
			direction = Vector2::Left;
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
		if (InputManager::getKeyDown(VK_UP))
		{
			state = PlayerState::Lookup;
		}
		if (InputManager::getKeyDown(VK_DOWN))
		{
			state = PlayerState::Sit;
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
			bulletStartPos = { bulletStartPos.x - 40, bulletStartPos.y - 40 };
			tr->SetRotation(kPi);
			direction = Vector2::Left;
		}
		if (InputManager::getKey(VK_RIGHT))
		{
			state = PlayerState::Move;
			if (an->GetActive()->getName() != L"�÷��̾���̵���ü")
			{
				an->PlayAnimation(L"�÷��̾���̵���ü");
			}
			bulletStartPos = { bulletStartPos.x + 40, bulletStartPos.y - 40 };
			tr->SetRotation(kPi);
			direction = Vector2::Right;
		}
		if (InputManager::getKeyDown(VK_SPACE))
		{

			state = PlayerState::Attack;
		}
		if (InputManager::getKeyDown(VK_UP))
		{
			direction = Vector2::Up;
			state = PlayerState::Lookup;
		}
		if (InputManager::getKeyDown(VK_DOWN))
		{
			state = PlayerState::Sit;
		}
		
		if (InputManager::getKeyUp(VK_LEFT)||InputManager::getKeyUp(VK_RIGHT))
		{
			an->PlayAnimation(L"�÷��̾���⺻");
			state = PlayerState::Idle;
		}
	}
	void PlayerScript::sit()
	{
		//�ѽ�� ��ġ ����
		bulletStartPos = { bulletStartPos.x, bulletStartPos.y + 40 };
		auto an = GetOwner()->GetComponent<Animator>();
		if (an->GetActive()->getName()!= L"�÷��̾���Ⱥ���")
		{
			an->PlayAnimation(L"�÷��̾���Ⱥ���");
		}
		if (InputManager::getKey(VK_DOWN))
		{
			state = PlayerState::Sit;
		}
		if (InputManager::getKeyUp(VK_DOWN))
		{
			an->PlayAnimation(L"�÷��̾���⺻");
			state = PlayerState::Idle;
		}
		if (InputManager::getKeyDown(VK_OEM_COMMA))
		{
			state = PlayerState::Slide;
		}
		if (InputManager::getKey(VK_SPACE))
		{
			ShootBullet();
		}
		
	}
	void PlayerScript::slide()
	{
		//�ִϸ��̼� ����
		
		auto tr = GetOwner()->GetComponent<Transform>();
		
		
	}
	void PlayerScript::attack()
	{
		//�����ִ� �������� �ѽ��
		
		if (!coolTime)
		{
			ShootBullet();
			bulletStartPos = GetOwner()->GetComponent<Transform>()->GetPosition();
			
		}
		else {
			state = PlayerState::Idle;
		}
		
		
	}
	void PlayerScript::lookup()
	{
  		auto an = GetOwner()->GetComponent<Animator>();
		
		if (an->getName()!= L"�÷��̾�⺻������ü")
		{
			an->PlayAnimation(L"�÷��̾�⺻������ü");
		}
		
		if (InputManager::getKeyUp(VK_UP))
		{
			state = PlayerState::Idle;
		}
		if (InputManager::getKeyDown(VK_DOWN))
		{
			state = PlayerState::Sit;
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
		
		//Vector2 mousePosition = app.getmousePosition(); //+ Vector2(position.x - app.getScreen().x / 2, position.y - app.getScreen().y / 2);
		
		

		std::random_device rd;
		std::mt19937 engine(rd());
		std::uniform_real_distribution<> urd(-1.0, 1.0);
		auto bullet = object::Instantiate<GameObject>(LayerType::Projectile
			, Vector2(bulletStartPos.x, bulletStartPos.y) + Vector2::One * 10.0f * urd(engine));

		if (renderer::mainCamera)
			bulletStartPos = renderer::mainCamera->CalculatPosition(bulletStartPos);

		Vector2 dest = (direction - bulletStartPos).nomalize();
		float degree = acosf(Vector2::Dot(Vector2::Right, dest));
		if (Vector2::Cross(Vector2::Right, dest) < 0)
			degree = 2 * math::kPi - degree;
		auto bulletTr = bullet->GetComponent<Transform>();
		bulletTr->SetRotation(tr->GetRotation());
		bulletTr->SetScale(Vector2::One * 1.5f);

		auto sr = bullet->AddComponent<SpriteRenderer>();//Animation
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