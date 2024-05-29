#pragma once
#include "..\\MyEngine_source\\ysResources.h"
#include "..\\MyEngine_source\\ysTexture.h"

namespace ys
{
	void LoadResources()
	{
		Resources::Load<graphics::Texture>(L"배경의배경", L"..\\Resource\\배경의배경.bmp");
		Resources::Load<graphics::Texture>(L"배경", L"..\\Resource\\스테이지1.bmp");
		Resources::Load<graphics::Texture>(L"플레이어가만", L"..\\Resource\\플레이어가만.bmp");
		Resources::Load<graphics::Texture>(L"플레이어이동", L"..\\Resource\\플레이어이동.bmp");
		Resources::Load<graphics::Texture>(L"총알png", L"..\\Resource\\heavyBullet.png");
		Resources::Load<graphics::Texture>(L"총알", L"..\\Resource\\heavyBullet.bmp");
		Resources::Load<graphics::Texture>(L"CloudOcean", L"..\\Resource\\CloudOcean.png");
		
		Resources::Load<graphics::Texture>(L"Stage1초반배경", L"..\\Resource\\1초반배경.bmp");
		//Resources::Load<graphics::Texture>(L"Stage1", L"..\\Resource\\scene1.bmp");
		Resources::Load<graphics::Texture>(L"Stage1", L"..\\Resource\\스테이지1.bmp");
		Resources::Load<graphics::Texture>(L"플레이어이동1", L"..\\Resource\\플레이어이동(1).png");
		Resources::Load<graphics::Texture>(L"플레이어이동2", L"..\\Resource\\플레이어이동(2).png");
		Resources::Load<graphics::Texture>(L"플레이어이동3", L"..\\Resource\\플레이어이동(3).png");
		Resources::Load<graphics::Texture>(L"플레이어이동4", L"..\\Resource\\플레이어이동(4).png");
		Resources::Load<graphics::Texture>(L"플레이어이동5", L"..\\Resource\\플레이어이동(5).png");
		Resources::Load<graphics::Texture>(L"플레이어이동6", L"..\\Resource\\플레이어이동(6).png");
	}
}