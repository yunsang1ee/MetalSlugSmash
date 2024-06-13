#pragma once
#include "..\\MyEngine_source\\ysResources.h"
#include "..\\MyEngine_source\\ysTexture.h"

namespace ys
{
	void LoadResources()
	{
		Resources::Load<graphics::Texture>(L"����ǹ��", L"..\\Resource\\����ǹ��.bmp");
		Resources::Load<graphics::Texture>(L"���", L"..\\Resource\\��������1.bmp");
		Resources::Load<graphics::Texture>(L"��", L"..\\Resource\\��.bmp");
		Resources::Load<graphics::Texture>(L"����Ա�����1", L"..\\Resource\\��������1����� ������1.bmp");
		Resources::Load<graphics::Texture>(L"����Ա�����2", L"..\\Resource\\��������1�����.bmp");
		//Resources::Load<graphics::Texture>(L"�÷��̾��", L"..\\Resource\\�÷��̾��.bmp");
		
		Resources::Load<graphics::Texture>(L"�Ѿ�png", L"..\\Resource\\heavyBullet.png");
		Resources::Load<graphics::Texture>(L"�Ѿ�", L"..\\Resource\\heavyBullet.bmp");
		Resources::Load<graphics::Texture>(L"CloudOcean", L"..\\Resource\\CloudOcean.png");
		 
		Resources::Load<graphics::Texture>(L"Stage1�ʹݹ��", L"..\\Resource\\1�ʹݹ��.bmp");
		Resources::Load<graphics::Texture>(L"Stage1����ǹ��", L"..\\Resource\\1����ǹ��.bmp");
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

		Resources::Load<graphics::Texture>(L"�÷��̾���_��_��ü", L"..\\Resource\\�⺻������ü.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾���_��_��ü", L"..\\Resource\\�⺻������ü.bmp");


		Resources::Load<graphics::Texture>(L"�÷��̾�ɱ����", L"..\\Resource\\�÷��̾�ɱ����.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�ɱ������", L"..\\Resource\\�÷��̾�ɱ������.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�ɱ��߰�", L"..\\Resource\\�÷��̾�ɱ��߰�.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�ɱ��߰���", L"..\\Resource\\�÷��̾�ɱ��߰���.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾����", L"..\\Resource\\�÷��̾����.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾������", L"..\\Resource\\�÷��̾������.bmp");

		Resources::Load<graphics::Texture>(L"�÷��̾�_�����̵�", L"..\\Resource\\�÷��̾�_�����̵�.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�_�����̵���", L"..\\Resource\\�÷��̾�_�����̵���.bmp");

		Resources::Load<graphics::Texture>(L"�޹�潣", L"..\\Resource\\�޹�潣.bmp");
		Resources::Load<graphics::Texture>(L"�ʰ���1", L"..\\Resource\\�ʰ���1.bmp");
		
	}
}