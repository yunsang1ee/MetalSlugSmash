#pragma once

namespace ys::enums
{
	enum class LayerType
	{
		None,
		BackBackGround,
		BackGround,
		Projectile,
		Block,
		Impediments,
		Enemy,
		PlayerLowerBody,
		PlayerTop,
		Particle,
		FrontGround,
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

	enum class AudioGroup
	{
		None,
		BackGorund,
		Player,
		Enemy,
		Effect,
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
		AudioListener,
		AudioSource,
		End
	};// Reference : Unity lifeCycle
}