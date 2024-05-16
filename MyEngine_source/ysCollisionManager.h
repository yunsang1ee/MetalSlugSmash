#pragma once
#include "CommonInclude.h"
#include "ysCollider.h"
#include "ysBoxCollider2D.h"
#include "ysCircleCollider2D.h"

namespace ys
{
	using namespace enums;
	class CollisionManager
	{
	public:
		static void Init();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hDC);

		static void CollisionLayerCheck(const LayerType& left
			, const LayerType& right
			, const bool& enable);

		static void LayerCollision(class Scene* scene
			, const LayerType& left
			, const LayerType& right);

		static void ColliderCollision(Collider* left, Collider* right);

	private:
		//상삼각만 사용
		static std::bitset<(UINT)LayerType::Max> collisionLayerMatrix[(UINT)LayerType::Max];
	};
}

