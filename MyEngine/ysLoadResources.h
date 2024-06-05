#pragma once
#include "..\\MyEngine_source\\ysResources.h"
#include "..\\MyEngine_source\\ysTexture.h"

namespace ys
{
	void LoadResources()
	{
		Resources::Load<graphics::Texture>(L"배경의배경", L"..\\Resource\\배경의배경.bmp");
		Resources::Load<graphics::Texture>(L"배경", L"..\\Resource\\스테이지1.bmp");
		Resources::Load<graphics::Texture>(L"돌", L"..\\Resource\\돌.bmp");
		Resources::Load<graphics::Texture>(L"잠수함구조물1", L"..\\Resource\\스테이지1잠수함 구조물1.bmp");
		Resources::Load<graphics::Texture>(L"잠수함구조물2", L"..\\Resource\\스테이지1잠수함.bmp");
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
		Resources::Load<graphics::Texture>(L"플레이어기본총위좌", L"..\\Resource\\플레이어_기본총위좌.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_기본총_위공격_우", L"..\\Resource\\플레이어_기본총_위공격.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_기본총_위공격_좌", L"..\\Resource\\플레이어_기본총_위공격좌.bmp");
		Resources::Load<graphics::Texture>(L"플레이어기본_총아래", L"..\\Resource\\플레이어기본총아래.bmp");


		Resources::Load<graphics::Texture>(L"플레이어앉기시작", L"..\\Resource\\플레이어앉기시작.bmp");
		Resources::Load<graphics::Texture>(L"플레이어앉기시작좌", L"..\\Resource\\플레이어앉기시작좌.bmp");
		Resources::Load<graphics::Texture>(L"플레이어앉기중간", L"..\\Resource\\플레이어앉기중간.bmp");
		Resources::Load<graphics::Texture>(L"플레이어앉기중간좌", L"..\\Resource\\플레이어앉기중간좌.bmp");
		Resources::Load<graphics::Texture>(L"플레이어앉음", L"..\\Resource\\플레이어앉음.bmp");
		Resources::Load<graphics::Texture>(L"플레이어앉음좌", L"..\\Resource\\플레이어앉음좌.bmp");

		Resources::Load<graphics::Texture>(L"플레이어기본총좌우공격상체", L"..\\Resource\\플레이어_기본총_앞공격_상체.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_슬라이딩", L"..\\Resource\\플레이어_슬라이딩.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_슬라이딩좌", L"..\\Resource\\플레이어_슬라이딩좌.bmp");

		Resources::Load<graphics::Texture>(L"뒷배경숲", L"..\\Resource\\뒷배경숲.bmp");
		Resources::Load<graphics::Texture>(L"초가집1", L"..\\Resource\\초가집1.bmp");
		
	}
}