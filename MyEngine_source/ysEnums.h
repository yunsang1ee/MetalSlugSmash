#pragma once

namespace ys::enums
{
	enum class LayerType
	{
		None,
		BackBackGround,
		BackGround,
		Trigger,
		Projectile,
		Wall,
		Block,
		Impediments,
		Enemy,
		EnemyProjectile,
		PlayerLowerBody,
		Boom,
		Particle,
		FrontGround,
		UI,
		Tool,
		Camera,
		Max
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