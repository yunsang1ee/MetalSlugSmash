#pragma once
#include "..\\MyEngine_source\\ysResources.h"
#include "..\\MyEngine_source\\ysTexture.h"
#include "..\\MyEngine_source\\ysAudioClip.h"

namespace ys
{
	void LoadResources()
	{
		Resources::Load<graphics::Texture>(L"����ǹ��", L"..\\Resource\\����ǹ��.bmp");
		
		Resources::Load<graphics::Texture>(L"��", L"..\\Resource\\��.bmp");
		Resources::Load<graphics::Texture>(L"����Ա�����1", L"..\\Resource\\��������1����� ������1.bmp");
		Resources::Load<graphics::Texture>(L"����Ա�����2", L"..\\Resource\\��������1�����.bmp");
		
		
		Resources::Load<graphics::Texture>(L"�Ѿ�png", L"..\\Resource\\heavyBullet.png");
		Resources::Load<graphics::Texture>(L"Stage1", L"..\\Resource\\��������1.bmp");


		Resources::Load<graphics::Texture>(L"�÷��̾�_����", L"..\\Resource\\�÷��̾�_����.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�_�°���", L"..\\Resource\\�÷��̾�_����.bmp");

		Resources::Load<graphics::Texture>(L"�÷��̾��̵�", L"..\\Resource\\�÷��̾�_���̵�.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾����̵�", L"..\\Resource\\�÷��̾�_���̵�.bmp");
		
		//����
		Resources::Load<graphics::Texture>(L"�÷��̾������", L"..\\Resource\\�÷��̾�_����_����ü.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾��������", L"..\\Resource\\�÷��̾�_����_����ü.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾��̵�����", L"..\\Resource\\�÷��̾�_����_����ü.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾��̵�������", L"..\\Resource\\�÷��̾�_����_����ü.bmp");

		//��������
		Resources::Load<graphics::Texture>(L"�÷��̾�⺻����", L"..\\Resource\\�÷��̾�⺻����.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�⺻������", L"..\\Resource\\�÷��̾�⺻����.bmp");

		//�Ʒ�����
		Resources::Load<graphics::Texture>(L"�÷��̾�⺻�ѾƷ�", L"..\\Resource\\�÷��̾�⺻�ѾƷ�.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�⺻�ѾƷ���", L"..\\Resource\\�÷��̾�⺻�ѾƷ�.bmp");

		//��������
		Resources::Load<graphics::Texture>(L"�÷��̾���ѽ����", L"..\\Resource\\�����ѽ����.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾���ѽ������", L"..\\Resource\\�����ѽ����.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾���ѽ��", L"..\\Resource\\�����ѽ��.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾���ѽ����", L"..\\Resource\\�����ѽ��.bmp");
		//��������
		Resources::Load<graphics::Texture>(L"�÷��̾������ѽ����", L"..\\Resource\\�����ѽ����.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾������ѽ������", L"..\\Resource\\�����ѽ����.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾������ѽ��", L"..\\Resource\\�����ѽ��.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾������ѽ����", L"..\\Resource\\�����ѽ��.bmp");

		//������
		Resources::Load<graphics::Texture>(L"�÷��̾����ѽ����", L"..\\Resource\\���ѽ����.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾����ѽ������", L"..\\Resource\\���ѽ����.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾����ѽ��", L"..\\Resource\\���ѽ��.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾����ѽ����", L"..\\Resource\\���ѽ��.bmp");

		//�Ʒ�����
		Resources::Load<graphics::Texture>(L"�÷��̾�Ʒ��ѽ����", L"..\\Resource\\�Ʒ��ѽ����.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�Ʒ��ѽ������", L"..\\Resource\\�Ʒ��ѽ����.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�Ʒ��ѽ��", L"..\\Resource\\�Ʒ��ѽ��.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�Ʒ��ѽ����", L"..\\Resource\\�Ʒ��ѽ��.bmp");

		//����ź
		Resources::Load<graphics::Texture>(L"�÷��̾������ź", L"..\\Resource\\��������ź.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾������ź��", L"..\\Resource\\��������ź.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾���������ź", L"..\\Resource\\��������ź.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾���������ź��", L"..\\Resource\\��������ź.bmp");

		Resources::Load<graphics::Texture>(L"�÷��̾���_��_��ü", L"..\\Resource\\�⺻������ü.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾���_��_��ü", L"..\\Resource\\�⺻������ü.bmp");

		


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
		Resources::Load<graphics::Texture>(L"����_�⺻_Move", L"..\\Resource\\boss\\������_move.bmp");
		Resources::Load<graphics::Texture>(L"����_�⺻_Shoot", L"..\\Resource\\boss\\������_shoot.bmp");
		Resources::Load<graphics::Texture>(L"����_Cannon_Move", L"..\\Resource\\boss\\������_cannon_move.bmp");
		Resources::Load<graphics::Texture>(L"����_Cannon_Shoot", L"..\\Resource\\boss\\������_cannon_shoot.bmp");
		Resources::Load<graphics::Texture>(L"����_Cannon_Depoly", L"..\\Resource\\boss\\������_depolyingCannon.bmp");
		Resources::Load<graphics::Texture>(L"����_����", L"..\\Resource\\boss\\������_defeat.bmp");

		//���� �Ѿ�
		Resources::Load<graphics::Texture>(L"����_�Ѿ�", L"..\\Resource\\boss\\������_projectile.bmp");
		Resources::Load<graphics::Texture>(L"����_������", L"..\\Resource\\boss\\������_cannonBall.bmp");

		//����sfx
		Resources::Load<graphics::Texture>(L"����_SFX", L"..\\Resource\\boss\\������_SFX ����.bmp");
		Resources::Load<graphics::Texture>(L"����_cannon_SFX", L"..\\Resource\\boss\\������_cannon_SFX.bmp");
		Resources::Load<graphics::Texture>(L"����_etcSFX", L"..\\Resource\\boss\\������_etcSFX.bmp");
		Resources::Load<graphics::Texture>(L"����_splashSFX", L"..\\Resource\\boss\\������_splashSFX.bmp");
		Resources::Load<graphics::Texture>(L"����_waves", L"..\\Resource\\boss\\������_waves.bmp");

		//�������
		Resources::Load<graphics::Texture>(L"�������", L"..\\Resource\\Boss���.bmp");

		//����
		Resources::Load<AudioClip>(L"stage1���κ��", L"..\\Resource\\03 Main Theme from Metal Slug (Stage 1).mp3");
		Resources::Load<AudioClip>(L"�߻����", L"..\\Resource\\gun_sound.wav");
	}
}