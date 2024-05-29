#pragma once
#include "..\\MyEngine_source\\ysResources.h"
#include "..\\MyEngine_source\\ysTexture.h"

namespace ys
{
	void LoadResources()
	{
		Resources::Load<graphics::Texture>(L"����ǹ��", L"..\\Resource\\����ǹ��.bmp");
		Resources::Load<graphics::Texture>(L"���", L"..\\Resource\\��������1.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾��", L"..\\Resource\\�÷��̾��.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾��̵�", L"..\\Resource\\�÷��̾��̵�.bmp");
		Resources::Load<graphics::Texture>(L"�Ѿ�png", L"..\\Resource\\heavyBullet.png");
		Resources::Load<graphics::Texture>(L"�Ѿ�", L"..\\Resource\\heavyBullet.bmp");
		Resources::Load<graphics::Texture>(L"CloudOcean", L"..\\Resource\\CloudOcean.png");
		
		Resources::Load<graphics::Texture>(L"Stage1�ʹݹ��", L"..\\Resource\\1�ʹݹ��.bmp");
		//Resources::Load<graphics::Texture>(L"Stage1", L"..\\Resource\\scene1.bmp");
		Resources::Load<graphics::Texture>(L"Stage1", L"..\\Resource\\��������1.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾��̵�1", L"..\\Resource\\�÷��̾��̵�(1).png");
		Resources::Load<graphics::Texture>(L"�÷��̾��̵�2", L"..\\Resource\\�÷��̾��̵�(2).png");
		Resources::Load<graphics::Texture>(L"�÷��̾��̵�3", L"..\\Resource\\�÷��̾��̵�(3).png");
		Resources::Load<graphics::Texture>(L"�÷��̾��̵�4", L"..\\Resource\\�÷��̾��̵�(4).png");
		Resources::Load<graphics::Texture>(L"�÷��̾��̵�5", L"..\\Resource\\�÷��̾��̵�(5).png");
		Resources::Load<graphics::Texture>(L"�÷��̾��̵�6", L"..\\Resource\\�÷��̾��̵�(6).png");
	}
}