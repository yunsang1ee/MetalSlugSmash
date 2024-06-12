#pragma once
#include "..\\MyEngine_source\\ysResources.h"
#include "..\\MyEngine_source\\ysTexture.h"
#include "..\\MyEngine\\SoundManager.h"

namespace ys
{
	void LoadResources()
	{
		Resources::Load<graphics::Texture>(L"배경의배경", L"..\\Resource\\배경의배경.bmp");
		
		Resources::Load<graphics::Texture>(L"돌", L"..\\Resource\\돌.bmp");
		Resources::Load<graphics::Texture>(L"잠수함구조물1", L"..\\Resource\\스테이지1잠수함 구조물1.bmp");
		Resources::Load<graphics::Texture>(L"잠수함구조물2", L"..\\Resource\\스테이지1잠수함.bmp");
		
		Resources::Load<graphics::Texture>(L"플레이어_가만", L"..\\Resource\\플레이어_가만.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_좌가만", L"..\\Resource\\플레이어_가만.bmp");
		
		Resources::Load<graphics::Texture>(L"총알png", L"..\\Resource\\heavyBullet.png");
		Resources::Load<graphics::Texture>(L"총알", L"..\\Resource\\heavyBullet.bmp");
		Resources::Load<graphics::Texture>(L"CloudOcean", L"..\\Resource\\CloudOcean.png");
		
		
		
		Resources::Load<graphics::Texture>(L"Stage1", L"..\\Resource\\스테이지1.bmp");
		Resources::Load<graphics::Texture>(L"플레이어이동", L"..\\Resource\\플레이어_우이동.bmp");
		Resources::Load<graphics::Texture>(L"플레이어좌이동", L"..\\Resource\\플레이어_우이동.bmp");
		
		Resources::Load<graphics::Texture>(L"플레이어_기본총_우공격", L"..\\Resource\\플레이어_기본총_우공격_상체.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_기본총_좌공격", L"..\\Resource\\플레이어_기본총_우공격_상체.bmp");

		Resources::Load<graphics::Texture>(L"플레이어기본총위", L"..\\Resource\\플레이어기본총위.bmp");
		Resources::Load<graphics::Texture>(L"플레이어기본총위좌", L"..\\Resource\\플레이어_기본총위좌.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_기본총_위공격_우", L"..\\Resource\\플레이어_기본총_위공격.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_기본총_위공격_좌", L"..\\Resource\\플레이어_기본총_위공격.bmp");
		Resources::Load<graphics::Texture>(L"플레이어기본_총아래", L"..\\Resource\\플레이어기본총아래.bmp");

		


		Resources::Load<graphics::Texture>(L"플레이어앉기시작", L"..\\Resource\\플레이어앉기시작.bmp");
		Resources::Load<graphics::Texture>(L"플레이어앉기시작좌", L"..\\Resource\\플레이어앉기시작.bmp");
		Resources::Load<graphics::Texture>(L"플레이어앉기중간", L"..\\Resource\\플레이어앉기중간.bmp");
		Resources::Load<graphics::Texture>(L"플레이어앉기중간좌", L"..\\Resource\\플레이어앉기중간.bmp");
		Resources::Load<graphics::Texture>(L"플레이어앉음", L"..\\Resource\\플레이어앉음.bmp");
		Resources::Load<graphics::Texture>(L"플레이어앉음좌", L"..\\Resource\\플레이어앉음.bmp");

		
		Resources::Load<graphics::Texture>(L"플레이어_슬라이딩", L"..\\Resource\\플레이어_슬라이딩.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_슬라이딩좌", L"..\\Resource\\플레이어_슬라이딩.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_슬라이딩_끝", L"..\\Resource\\플레이어_슬라이딩.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_슬라이딩좌_끝", L"..\\Resource\\플레이어_슬라이딩.bmp");

		Resources::Load<graphics::Texture>(L"뒷배경숲", L"..\\Resource\\뒷배경숲.bmp");
		Resources::Load<graphics::Texture>(L"초가집1", L"..\\Resource\\초가집1.bmp");
		
		Resources::Load<graphics::Texture>(L"플레이어_슬라이딩_기본총_공격", L"..\\Resource\\플레이어_슬라이딩_기본총_공격.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_슬라이딩_기본총_공격좌", L"..\\Resource\\플레이어_슬라이딩_기본총_공격.bmp");

		Resources::Load<graphics::Texture>(L"플레이어_앉음_공격", L"..\\Resource\\플레이어_앉음_공격.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_앉음_공격좌", L"..\\Resource\\플레이어_앉음_공격.bmp");

		Resources::Load<graphics::Texture>(L"플레이어_앉음_수류탄", L"..\\Resource\\플레이어_앉음_수류탄.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_앉음_수류탄좌", L"..\\Resource\\플레이어_앉음_수류탄.bmp");

		Resources::Load<graphics::Texture>(L"플레이어_앉음_이동", L"..\\Resource\\플레이어_앉음_이동.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_앉음_이동좌", L"..\\Resource\\플레이어_앉음_이동.bmp");

		Resources::Load<graphics::Texture>(L"플레이어_점프_상체", L"..\\Resource\\플레이어_점프_상하체.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_점프_상체좌", L"..\\Resource\\플레이어_점프_상하체.bmp");

		Resources::Load<graphics::Texture>(L"플레이어_점프_하체", L"..\\Resource\\플레이어_점프_상하체.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_점프_하체좌", L"..\\Resource\\플레이어_점프_상하체.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_이동_점프_하체", L"..\\Resource\\플레이어_점프_상하체.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_이동_점프_하체좌", L"..\\Resource\\플레이어_점프_상하체.bmp");

		Resources::Load<graphics::Texture>(L"플레이어_위_하체", L"..\\Resource\\기본위우하체.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_위_하체좌", L"..\\Resource\\기본위우하체.bmp");
		
		Resources::Load<graphics::Texture>(L"게_idle", L"..\\Resource\\monster\\게idle.bmp");
		Resources::Load<graphics::Texture>(L"게_idle_좌", L"..\\Resource\\monster\\게idle.bmp");

		Resources::Load<graphics::Texture>(L"게_walk", L"..\\Resource\\monster\\게walk.bmp");
		Resources::Load<graphics::Texture>(L"게_walk_좌", L"..\\Resource\\monster\\게walk.bmp");

		Resources::Load<graphics::Texture>(L"게_jump", L"..\\Resource\\monster\\게jump.bmp");
		Resources::Load<graphics::Texture>(L"게_jump_좌", L"..\\Resource\\monster\\게jump.bmp");

		Resources::Load<graphics::Texture>(L"게_attack", L"..\\Resource\\monster\\게attack.bmp");
		Resources::Load<graphics::Texture>(L"게_attack_좌", L"..\\Resource\\monster\\게attack.bmp");

		//사운드
		SoundManager::GetInstance()->LoadSound(L"stage1메인브금", "..\\Resource\\03 Main Theme from Metal Slug (Stage 1).mp3");
		SoundManager::GetInstance()->LoadSound(L"발사사운드", "..\\Resource\\gun_sound.wav");
		SoundManager::GetInstance()->GetplayerSound()->setVolume(0.3f);


	}
}