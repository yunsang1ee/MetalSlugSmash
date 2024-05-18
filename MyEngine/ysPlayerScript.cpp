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

extern ys::Application app;

namespace ys
{
	PlayerScript::PlayerScript() : prevPosition({ 0, 0 }), speed(300), coolTime(0), count(0)
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
		auto sr = GetOwner()->GetComponent<SpriteRenderer>();
		if (!(InputManager::getKey((BYTE)ys::Key::W) || InputManager::getKey(VK_UP)))
		{
			if (tr->GetPosition().y < 442)
			{
				tr->SetPosition({ tr->GetPosition().x, tr->GetPosition().y + Timer::getDeltaTime() * 300 });//�÷��̾ ȭ�� ������ ������ �ʰ� �ϱ� ���� �ڵ�

			}
		}
		
		static int runAnimation = 0;
		if (InputManager::getKey((BYTE)ys::Key::A) || InputManager::getKey(VK_LEFT))
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x - Timer::getDeltaTime() * speed, position.y });
			
			
			//�����Ӹ��� �ؽ��İ� �ٲ�Ƿ� �����Ӽ��� ������ �ʹ� ������ �����̰� ������ �ʹ� ������ ������
			switch (runAnimation)
			{
			case 0:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"�÷��̾��̵�1"));
				runAnimation++;
				break;
			case 1:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"�÷��̾��̵�2"));
				runAnimation++;
				break;
			case 2:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"�÷��̾��̵�3"));
				runAnimation++;
				break;
			case 3:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"�÷��̾��̵�4"));
				runAnimation++;
				break;
			case 4:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"�÷��̾��̵�5"));
				runAnimation++;
				break;
			case 5:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"�÷��̾��̵�6"));
				runAnimation = 0;
				break;
			default:
				break;
			}
		}
		if (InputManager::getKey((BYTE)ys::Key::D) || InputManager::getKey(VK_RIGHT))
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x + Timer::getDeltaTime() * speed, position.y });
			switch (runAnimation)
			{
			case 0:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"�÷��̾��̵�1"));
				runAnimation++;
				break;
			case 1:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"�÷��̾��̵�2"));
				runAnimation++;
				break;
			case 2:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"�÷��̾��̵�3"));
				runAnimation++;
				break;
			case 3:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"�÷��̾��̵�4"));
				runAnimation++;
				break;
			case 4:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"�÷��̾��̵�5"));
				runAnimation++;
				break;
			case 5:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"�÷��̾��̵�6"));
				runAnimation = 0;
				break;
			default:
				break;
			}
		}
		if (InputManager::getKey((BYTE)ys::Key::W) || InputManager::getKey(VK_UP))
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x, position.y - Timer::getDeltaTime() * speed });
		}
		if (InputManager::getKey((BYTE)ys::Key::S) || InputManager::getKey(VK_DOWN))
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x, position.y + Timer::getDeltaTime() * speed });
		}

		if ((InputManager::getKey(VK_SPACE) || count != 0) && !coolTime)
		{//���콺�� �ƴ϶� Ű���� ���¿� ���� ���ݹ��� ���ϸ� �ǰڳ� $$�ڰ���
			//������ ���콺�� ���� ���� ���ϰ� �ִ°ǰ�?
			auto position = tr->GetPosition();
			auto mousePosition = 
				app.getmousePosition() + Vector2(position.x - app.getScreen().x / 2, position.y - app.getScreen().y / 2);
			position = { position.x + 100, position.y + 60 };
			auto bullet = object::Instantiate<GameObject>(LayerType::Projectile
				, { position.x, position.y});

			auto dest = mousePosition - position;
			bullet->GetComponent<Transform>()->SetRotation(dest.nomalize());

			auto sr = bullet->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"�Ѿ�"));

			bullet->AddComponent<BulletScript>();
			bullet->AddComponent<BoxCollider2D>();
			auto col = bullet->GetComponent<BoxCollider2D>();
			col->SetSize(Vector2(0.7, 0.2));
			
			count++;
			coolTime = 0.05f;//�ѽ�� �ִϸ��̼� duration����
			if (count == 5) count = 0;//���ӽŰ��� ��� �ѹ��� 5�߾� ��ϱ� �̷������� �־ ����
		}
			
		if (InputManager::getKey((BYTE)ys::Key::U) && !coolTime)
		{
			speed += 10.0f;
			coolTime = 0.1f;
		}
		if (InputManager::getKey((BYTE)ys::Key::I) && !coolTime)
		{
			speed -= 10.0f;
			coolTime = 0.1f;
		}
	}
	void PlayerScript::LateUpdate()
	{
	}
	void PlayerScript::Render(HDC hDC)
	{
	}
}