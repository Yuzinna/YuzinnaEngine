#pragma once
namespace ugina
{
	namespace enums
	{
		enum class eComponentType
		{
			Transform,
			Collider,
			Rigidbody,
			Script,
			SpriteRenderer,
			Animator,
			Camera,
			End
		};
		enum class eLayerType
		{
			None,
			BackGround,
			Tile,
			Animal,
			Player,
			Floor,
			Particle,
			End,
			Max = 16,

		};
		enum class eResourceType
		{
			Texture,
			AudioClip,
			Animation,
			Prefab,
			Count
		};
		enum class eColliderType
		{
			Circle2D,
			Rect2D,
			End
		};
	}
}