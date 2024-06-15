#pragma once
#include "..\\MyEngine_source\\ysResources.h"
#include "..\\MyEngine_source\\ysTexture.h"
#include "..\\MyEngine_source\\ysAudioClip.h"

namespace ys
{
	void LoadResources()
	{
		Resources::Load<graphics::Texture>(L"배경의배경", L"..\\Resource\\배경의배경.bmp");
		
		Resources::Load<graphics::Texture>(L"돌", L"..\\Resource\\돌.bmp");
		Resources::Load<graphics::Texture>(L"잠수함구조물1", L"..\\Resource\\스테이지1잠수함 구조물1.bmp");
		Resources::Load<graphics::Texture>(L"잠수함구조물2", L"..\\Resource\\스테이지1잠수함.bmp");
		
		
		Resources::Load<graphics::Texture>(L"총알png", L"..\\Resource\\heavyBullet.png");
		Resources::Load<graphics::Texture>(L"Stage1", L"..\\Resource\\스테이지1.bmp");


		Resources::Load<graphics::Texture>(L"플레이어_가만", L"..\\Resource\\플레이어_가만.bmp");
		Resources::Load<graphics::Texture>(L"플레이어_좌가만", L"..\\Resource\\플레이어_가만.bmp");

		Resources::Load<graphics::Texture>(L"플레이어이동", L"..\\Resource\\플레이어_우이동.bmp");
		Resources::Load<graphics::Texture>(L"플레이어좌이동", L"..\\Resource\\플레이어_우이동.bmp");
		
		//점프
		Resources::Load<graphics::Texture>(L"플레이어가만점프", L"..\\Resource\\플레이어_점프_상하체.bmp");
		Resources::Load<graphics::Texture>(L"플레이어가만점프좌", L"..\\Resource\\플레이어_점프_상하체.bmp");
		Resources::Load<graphics::Texture>(L"플레이어이동점프", L"..\\Resource\\플레이어_점프_상하체.bmp");
		Resources::Load<graphics::Texture>(L"플레이어이동점프좌", L"..\\Resource\\플레이어_점프_상하체.bmp");

		//위에보기
		Resources::Load<graphics::Texture>(L"플레이어기본총위", L"..\\Resource\\플레이어기본총위.bmp");
		Resources::Load<graphics::Texture>(L"플레이어기본총위좌", L"..\\Resource\\플레이어기본총위.bmp");

		//아래보기
		Resources::Load<graphics::Texture>(L"플레이어기본총아래", L"..\\Resource\\플레이어기본총아래.bmp");
		Resources::Load<graphics::Texture>(L"플레이어기본총아래좌", L"..\\Resource\\플레이어기본총아래.bmp");

		//가만어택
		Resources::Load<graphics::Texture>(L"플레이어가만총쏘는중", L"..\\Resource\\가만총쏘는중.bmp");
		Resources::Load<graphics::Texture>(L"플레이어가만총쏘는중좌", L"..\\Resource\\가만총쏘는중.bmp");
		Resources::Load<graphics::Texture>(L"플레이어가만총쏘기", L"..\\Resource\\가만총쏘기.bmp");
		Resources::Load<graphics::Texture>(L"플레이어가만총쏘기좌", L"..\\Resource\\가만총쏘기.bmp");
		//점프어택
		Resources::Load<graphics::Texture>(L"플레이어점프총쏘는중", L"..\\Resource\\점프총쏘는중.bmp");
		Resources::Load<graphics::Texture>(L"플레이어점프총쏘는중좌", L"..\\Resource\\점프총쏘는중.bmp");
		Resources::Load<graphics::Texture>(L"플레이어점프총쏘기", L"..\\Resource\\점프총쏘기.bmp");
		Resources::Load<graphics::Texture>(L"플레이어점프총쏘기좌", L"..\\Resource\\점프총쏘기.bmp");

		//위어택
		Resources::Load<graphics::Texture>(L"플레이어위총쏘는중", L"..\\Resource\\위총쏘는중.bmp");
		Resources::Load<graphics::Texture>(L"플레이어위총쏘는중좌", L"..\\Resource\\위총쏘는중.bmp");
		Resources::Load<graphics::Texture>(L"플레이어위총쏘기", L"..\\Resource\\위총쏘기.bmp");
		Resources::Load<graphics::Texture>(L"플레이어위총쏘기좌", L"..\\Resource\\위총쏘기.bmp");

		//아래어택
		Resources::Load<graphics::Texture>(L"플레이어아래총쏘는중", L"..\\Resource\\아래총쏘는중.bmp");
		Resources::Load<graphics::Texture>(L"플레이어아래총쏘는중좌", L"..\\Resource\\아래총쏘는중.bmp");
		Resources::Load<graphics::Texture>(L"플레이어아래총쏘기", L"..\\Resource\\아래총쏘기.bmp");
		Resources::Load<graphics::Texture>(L"플레이어아래총쏘기좌", L"..\\Resource\\아래총쏘기.bmp");

		//수류탄
		Resources::Load<graphics::Texture>(L"플레이어가만수류탄", L"..\\Resource\\가만수류탄.bmp");
		Resources::Load<graphics::Texture>(L"플레이어가만수류탄좌", L"..\\Resource\\가만수류탄.bmp");
		Resources::Load<graphics::Texture>(L"플레이어점프수류탄", L"..\\Resource\\점프수류탄.bmp");
		Resources::Load<graphics::Texture>(L"플레이어점프수류탄좌", L"..\\Resource\\점프수류탄.bmp");

		Resources::Load<graphics::Texture>(L"플레이어위_우_하체", L"..\\Resource\\기본위우하체.bmp");
		Resources::Load<graphics::Texture>(L"플레이어위_좌_하체", L"..\\Resource\\기본위좌하체.bmp");

		


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

		//보스
		Resources::Load<graphics::Texture>(L"보스_기본_Move", L"..\\Resource\\boss\\보스게_move.bmp");
		Resources::Load<graphics::Texture>(L"보스_기본_Shoot", L"..\\Resource\\boss\\보스게_shoot.bmp");
		Resources::Load<graphics::Texture>(L"보스_Cannon_Move", L"..\\Resource\\boss\\보스게_cannon_move.bmp");
		Resources::Load<graphics::Texture>(L"보스_Cannon_Shoot", L"..\\Resource\\boss\\보스게_cannon_shoot.bmp");
		Resources::Load<graphics::Texture>(L"보스_Cannon_Depoly", L"..\\Resource\\boss\\보스게_depolyingCannon.bmp");
		Resources::Load<graphics::Texture>(L"보스_죽음", L"..\\Resource\\boss\\보스게_defeat.bmp");

		//보스 총알
		Resources::Load<graphics::Texture>(L"보스_총알", L"..\\Resource\\boss\\보스게_projectile.bmp");
		Resources::Load<graphics::Texture>(L"보스_대포알", L"..\\Resource\\boss\\보스게_cannonBall.bmp");

		//보스sfx
		Resources::Load<graphics::Texture>(L"보스_SFX", L"..\\Resource\\boss\\보스게_SFX 복사.bmp");
		Resources::Load<graphics::Texture>(L"보스_cannon_SFX", L"..\\Resource\\boss\\보스게_cannon_SFX.bmp");
		Resources::Load<graphics::Texture>(L"보스_etcSFX", L"..\\Resource\\boss\\보스게_etcSFX.bmp");
		Resources::Load<graphics::Texture>(L"보스_splashSFX", L"..\\Resource\\boss\\보스게_splashSFX.bmp");
		Resources::Load<graphics::Texture>(L"보스_waves", L"..\\Resource\\boss\\보스게_waves.bmp");

		//보스배경
		Resources::Load<graphics::Texture>(L"보스배경", L"..\\Resource\\Boss배경.bmp");

		//사운드
		Resources::Load<AudioClip>(L"stage1메인브금", L"..\\Resource\\03 Main Theme from Metal Slug (Stage 1).mp3");
		Resources::Load<AudioClip>(L"발사사운드", L"..\\Resource\\gun_sound.wav");
	}
}