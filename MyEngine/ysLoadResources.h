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
		Resources::Load<graphics::Texture>(L"플레이어가만(왼)", L"..\\Resource\\플레이어가만(왼).bmp");

		Resources::Load<graphics::Texture>(L"총알", L"..\\Resource\\heavyBullet.bmp");
		Resources::Load<graphics::Texture>(L"총알아래", L"..\\Resource\\heavyBullet아래.bmp");
		Resources::Load<graphics::Texture>(L"총알위", L"..\\Resource\\heavyBullet위.bmp");
		Resources::Load<graphics::Texture>(L"총알왼쪽", L"..\\Resource\\heavyBullet왼쪽.bmp");

		Resources::Load<graphics::Texture>(L"CloudOcean", L"..\\Resource\\CloudOcean.png");
		Resources::Load<graphics::Texture>(L"문제의 그 배경", L"..\\Resource\\스테이지1.bmp");
		//Resources::Load<graphics::Texture>(L"Stage1", L"..\\Resource\\1.bmp");
		Resources::Load<graphics::Texture>(L"Stage1초반배경", L"..\\Resource\\1초반배경.bmp");
		Resources::Load<graphics::Texture>(L"Stage1", L"..\\Resource\\scene1.bmp");

		Resources::Load<graphics::Texture>(L"플레이어이동1", L"..\\Resource\\플레이어이동(1).png");
		Resources::Load<graphics::Texture>(L"플레이어이동2", L"..\\Resource\\플레이어이동(2).png");
		Resources::Load<graphics::Texture>(L"플레이어이동3", L"..\\Resource\\플레이어이동(3).png");
		Resources::Load<graphics::Texture>(L"플레이어이동4", L"..\\Resource\\플레이어이동(4).png");
		Resources::Load<graphics::Texture>(L"플레이어이동5", L"..\\Resource\\플레이어이동(5).png");
		Resources::Load<graphics::Texture>(L"플레이어이동6", L"..\\Resource\\플레이어이동(6).png");
		Resources::Load<graphics::Texture>(L"게1", L"..\\Resource\\몬스터(게)1.bmp");
		Resources::Load<graphics::Texture>(L"게2", L"..\\Resource\\몬스터(게)2.bmp");
		Resources::Load<graphics::Texture>(L"게3", L"..\\Resource\\몬스터(게)3.bmp");
		Resources::Load<graphics::Texture>(L"게4", L"..\\Resource\\몬스터(게)4.bmp");
		Resources::Load<graphics::Texture>(L"게5", L"..\\Resource\\몬스터(게)5.bmp");
		Resources::Load<graphics::Texture>(L"게6", L"..\\Resource\\몬스터(게)6.bmp");
		Resources::Load<graphics::Texture>(L"게7", L"..\\Resource\\몬스터(게)7.bmp");
		Resources::Load<graphics::Texture>(L"게8", L"..\\Resource\\몬스터(게)8.bmp");
		Resources::Load<graphics::Texture>(L"게9", L"..\\Resource\\몬스터(게)9.bmp");
		Resources::Load<graphics::Texture>(L"게10", L"..\\Resource\\몬스터(게)10.bmp");
		Resources::Load<graphics::Texture>(L"게11", L"..\\Resource\\몬스터(게)11.bmp");
		Resources::Load<graphics::Texture>(L"게12", L"..\\Resource\\몬스터(게)12.bmp");
		
		Resources::Load<graphics::Texture>(L"Block", L"..\\Resource\\block.png");
	}
}