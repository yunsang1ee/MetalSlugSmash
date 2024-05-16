#include "ysCollisionManager.h"
#include "ysSceneManager.h"

namespace ys
{
	std::bitset<(UINT)LayerType::Max> CollisionManager::collisionLayerMatrix[(UINT)LayerType::Max]{};

	void CollisionManager::Init()
	{
	}
	void CollisionManager::Update()
	{
		auto scene = SceneManager::GetaActiveScene();
		for (UINT row = 0; row < (UINT)LayerType::Max; ++row)
			for (UINT col = row; col < (UINT)LayerType::Max; ++col)
				if (collisionLayerMatrix[row][col] == true)
					LayerCollision(scene, static_cast<LayerType>(row), static_cast<LayerType>(col));
	}
	void CollisionManager::LateUpdate()
	{
	}
	void CollisionManager::Render(HDC hDC)
	{
	}
	void CollisionManager::CollisionLayerCheck(const LayerType& left/*col*/, const LayerType& right/*row*/, const bool& enable)
	{
		int row = 0; int col = 0;
		if (left <= right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}
		else
		{
			row = (UINT)right;
			col = (UINT)left;
		}

		collisionLayerMatrix[row][col] = enable;
	}
	void CollisionManager::LayerCollision(Scene* scene, const LayerType& left, const LayerType& right)
	{
		auto& lefts = scene->GetLayer(left)->GetGameObjects();
		auto& rights = scene->GetLayer(right)->GetGameObjects();

		for(auto left : lefts)
		{
			if (left->IsActive() == false) continue;
			auto leftCD = left->GetComponent<Collider>();
			if (leftCD == nullptr) continue;

			for (auto right : rights)
			{
				if (right->IsActive() == false) continue;
				auto rightCD = right->GetComponent<Collider>();
				if (rightCD == nullptr) continue;
				if (left == right) continue;

				ColliderCollision(leftCD, rightCD);
			}
		}
	}
	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{

	}
}