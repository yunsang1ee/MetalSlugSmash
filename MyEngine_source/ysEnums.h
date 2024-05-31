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
		Block,
		Particle,
		Camera,
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
		Animation,
		Prefab,
		End
	};

	enum class ComponentType
	{
		Transform, 
		Collider,
		RigidBody,
		Script,
		SpriteRenderer,
		Animator,
		Camera,
		End
	};// Reference : Unity lifeCycle
}