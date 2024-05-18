#pragma once
#include "..\\MyEngine_source\\ysResources.h"
#include "..\\MyEngine_source\\ysTexture.h"

namespace ys
{
	void LoadResources()
	{
		Resources::Load<graphics::Texture>(L"����ǹ��", L"..\\Resource\\����ǹ��.bmp");
		Resources::Load<graphics::Texture>(L"���", L"..\\Resource\\���.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾��", L"..\\Resource\\�÷��̾��.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾��̵�", L"..\\Resource\\�÷��̾��̵�.bmp");
		Resources::Load<graphics::Texture>(L"�÷��̾�⺻����", L"..\\Resource\\�÷��̾�⺻����.bmp");
		Resources::Load<graphics::Texture>(L"�Ѿ�", L"..\\Resource\\heavyBullet.bmp");
		Resources::Load<graphics::Texture>(L"CloudOcean", L"..\\Resource\\CloudOcean.png");
	}
}