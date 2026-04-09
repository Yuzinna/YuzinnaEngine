#pragma once
namespace yuzinna
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
			Camera,
			UI,
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
		enum class eWordType
		{
			None,
			Baba, Rock, Wall, Flag, Key, Skull, Water, // 명사 (Noun)
			Is,                                        // 연결자 (Verb)
			You, Push, Stop, Win, Sink,            // 속성 (Property)
			End
			};
		}
		}