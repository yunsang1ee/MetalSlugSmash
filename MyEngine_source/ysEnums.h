#pragma once

namespace ys::enums
{
	enum class LayerType
	{
		None,
		BackGround,
		Projectile,
		Enemy,
		Player,
		Particle,
		Camera,
		Block,
		Max = 16
	};

	enum class ColliderType
	{
		Box2D,
		Circle2D,
		End
	};

	enum class ResourceType
	{
		Texture,
		AudioClip,
		Prefab,
		End
	};

	enum class ComponentType
	{
		Transform, 
		Collider,
		Script,
		SpriteRenderer,
		//Animator,
		Camera,
		End
	};// Reference : Unity lifeCycle
}