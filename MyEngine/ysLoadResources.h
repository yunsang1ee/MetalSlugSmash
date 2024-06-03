#pragma once
#include "..\\MyEngine_source\\ysResources.h"
#include "..\\MyEngine_source\\ysTexture.h"

namespace ys
{
	void LoadResources()
	{
		Resources::Load<graphics::Texture>(L"배경의배경", L"..\\Resource\\배경의배경.bmp");
		Resources::Load<graphics::Texture>(L"배경", L"..\\Resource\\스테이지1.bmp");
		//Resources::Load<graphics::Texture>(L"플레이어가만", L"..\\Resource\\플레이어가만.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_가만", L"..\\Resource\\플레이어_가만.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_좌가만", L"..\\Resource\\플레이어_좌가만.bmp");
		
		Resources::Load<graphics::Texture>(L"총알png", L"..\\Resource\\heavyBullet.png");
		Resources::Load<graphics::Texture>(L"총알", L"..\\Resource\\heavyBullet.bmp");
		Resources::Load<graphics::Texture>(L"CloudOcean", L"..\\Resource\\CloudOcean.png");
		
		Resources::Load<graphics::Texture>(L"Stage1초반배경", L"..\\Resource\\1초반배경.bmp");
		
		Resources::Load<graphics::Texture>(L"Stage1", L"..\\Resource\\스테이지1.bmp");
		Resources::Load<graphics::Texture>(L"플레이어이동", L"..\\Resource\\플레이어_우이동.bmp");
		Resources::Load<graphics::Texture>(L"플레이어좌이동", L"..\\Resource\\플레이어_좌이동.bmp");
		
		Resources::Load<graphics::Texture>(L"플레이어기본총위", L"..\\Resource\\플레이어기본총위.bmp");
		Resources::Load<graphics::Texture>(L"플레이어기본총아래", L"..\\Resource\\플레이어기본총위.bmp");


		Resources::Load<graphics::Texture>(L"플레이어앉기시작", L"..\\Resource\\플레이어앉기시작.bmp");
		Resources::Load<graphics::Texture>(L"플레이어앉기중간", L"..\\Resource\\플레이어앉기중간.bmp");
		Resources::Load<graphics::Texture>(L"플레이어앉음", L"..\\Resource\\플레이어앉음.bmp");
	}
}