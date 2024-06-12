#pragma once
#include "..\\MyEngine_source\\ysResources.h"
#include "..\\MyEngine_source\\ysTexture.h"
#include "..\\MyEngine\\SoundManager.h"

namespace ys
{
	void LoadResources()
	{
		Resources::Load<graphics::Texture>(L"����ǹ��", L"..\\Resource\\����ǹ��.bmp");
		
		Resources::Load<graphics::Texture>(L"��", L"..\\Resource\\��.bmp");
		Resources::Load<graphics::Texture>(L"����Ա�����1", L"..\\Resource\\��������1����� ������1.bmp");
		Resources::Load<graphics::Texture>(L"����Ա�����2", L"..\\Resource\\��������1�����.bmp");
		
		Resources::Load<graphics::Texture>(L"�÷��̾�_����", L"..\\Resource\\�÷��̾�_����.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�_�°���", L"..\\Resource\\�÷��̾�_����.bmp");
		
		Resources::Load<graphics::Texture>(L"�Ѿ�png", L"..\\Resource\\heavyBullet.png");
		Resources::Load<graphics::Texture>(L"�Ѿ�", L"..\\Resource\\heavyBullet.bmp");
		Resources::Load<graphics::Texture>(L"CloudOcean", L"..\\Resource\\CloudOcean.png");
		
		
		
		Resources::Load<graphics::Texture>(L"Stage1", L"..\\Resource\\��������1.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾��̵�", L"..\\Resource\\�÷��̾�_���̵�.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾����̵�", L"..\\Resource\\�÷��̾�_���̵�.bmp");
		
		Resources::Load<graphics::Texture>(L"�÷��̾�_�⺻��_�����", L"..\\Resource\\�÷��̾�_�⺻��_�����_��ü.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�_�⺻��_�°���", L"..\\Resource\\�÷��̾�_�⺻��_�����_��ü.bmp");

		Resources::Load<graphics::Texture>(L"�÷��̾�⺻����", L"..\\Resource\\�÷��̾�⺻����.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�⺻������", L"..\\Resource\\�÷��̾�_�⺻������.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�_�⺻��_������_��", L"..\\Resource\\�÷��̾�_�⺻��_������.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�_�⺻��_������_��", L"..\\Resource\\�÷��̾�_�⺻��_������.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�⺻_�ѾƷ�", L"..\\Resource\\�÷��̾�⺻�ѾƷ�.bmp");

		


		Resources::Load<graphics::Texture>(L"�÷��̾�ɱ����", L"..\\Resource\\�÷��̾�ɱ����.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�ɱ������", L"..\\Resource\\�÷��̾�ɱ����.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�ɱ��߰�", L"..\\Resource\\�÷��̾�ɱ��߰�.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�ɱ��߰���", L"..\\Resource\\�÷��̾�ɱ��߰�.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾����", L"..\\Resource\\�÷��̾����.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾������", L"..\\Resource\\�÷��̾����.bmp");

		
		Resources::Load<graphics::Texture>(L"�÷��̾�_�����̵�", L"..\\Resource\\�÷��̾�_�����̵�.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�_�����̵���", L"..\\Resource\\�÷��̾�_�����̵�.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�_�����̵�_��", L"..\\Resource\\�÷��̾�_�����̵�.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�_�����̵���_��", L"..\\Resource\\�÷��̾�_�����̵�.bmp");

		Resources::Load<graphics::Texture>(L"�޹�潣", L"..\\Resource\\�޹�潣.bmp");
		Resources::Load<graphics::Texture>(L"�ʰ���1", L"..\\Resource\\�ʰ���1.bmp");
		
		Resources::Load<graphics::Texture>(L"�÷��̾�_�����̵�_�⺻��_����", L"..\\Resource\\�÷��̾�_�����̵�_�⺻��_����.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�_�����̵�_�⺻��_������", L"..\\Resource\\�÷��̾�_�����̵�_�⺻��_����.bmp");

		Resources::Load<graphics::Texture>(L"�÷��̾�_����_����", L"..\\Resource\\�÷��̾�_����_����.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�_����_������", L"..\\Resource\\�÷��̾�_����_����.bmp");

		Resources::Load<graphics::Texture>(L"�÷��̾�_����_����ź", L"..\\Resource\\�÷��̾�_����_����ź.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�_����_����ź��", L"..\\Resource\\�÷��̾�_����_����ź.bmp");

		Resources::Load<graphics::Texture>(L"�÷��̾�_����_�̵�", L"..\\Resource\\�÷��̾�_����_�̵�.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�_����_�̵���", L"..\\Resource\\�÷��̾�_����_�̵�.bmp");

		Resources::Load<graphics::Texture>(L"�÷��̾�_����_��ü", L"..\\Resource\\�÷��̾�_����_����ü.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�_����_��ü��", L"..\\Resource\\�÷��̾�_����_����ü.bmp");

		Resources::Load<graphics::Texture>(L"�÷��̾�_����_��ü", L"..\\Resource\\�÷��̾�_����_����ü.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�_����_��ü��", L"..\\Resource\\�÷��̾�_����_����ü.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�_�̵�_����_��ü", L"..\\Resource\\�÷��̾�_����_����ü.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�_�̵�_����_��ü��", L"..\\Resource\\�÷��̾�_����_����ü.bmp");

		Resources::Load<graphics::Texture>(L"�÷��̾�_��_��ü", L"..\\Resource\\�⺻������ü.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�_��_��ü��", L"..\\Resource\\�⺻������ü.bmp");
		
		Resources::Load<graphics::Texture>(L"��_idle", L"..\\Resource\\monster\\��idle.bmp");
		Resources::Load<graphics::Texture>(L"��_idle_��", L"..\\Resource\\monster\\��idle.bmp");

		Resources::Load<graphics::Texture>(L"��_walk", L"..\\Resource\\monster\\��walk.bmp");
		Resources::Load<graphics::Texture>(L"��_walk_��", L"..\\Resource\\monster\\��walk.bmp");

		Resources::Load<graphics::Texture>(L"��_jump", L"..\\Resource\\monster\\��jump.bmp");
		Resources::Load<graphics::Texture>(L"��_jump_��", L"..\\Resource\\monster\\��jump.bmp");

		Resources::Load<graphics::Texture>(L"��_attack", L"..\\Resource\\monster\\��attack.bmp");
		Resources::Load<graphics::Texture>(L"��_attack_��", L"..\\Resource\\monster\\��attack.bmp");

		//����
		SoundManager::GetInstance()->LoadSound(L"stage1���κ��", "..\\Resource\\03 Main Theme from Metal Slug (Stage 1).mp3");
		SoundManager::GetInstance()->LoadSound(L"�߻����", "..\\Resource\\gun_sound.wav");
		SoundManager::GetInstance()->GetplayerSound()->setVolume(0.3f);


	}
}