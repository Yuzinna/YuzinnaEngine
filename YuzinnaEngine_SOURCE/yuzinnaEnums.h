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
			AudioListener,
			AudioSource,
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
			Word,
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
		enum class eUIType
		{
			HpBar,
			Button,
			End,
		};
		enum class eWordType
		{
			None,
			Baba, Rock, Wall, Flag, Key, Skull, Water, Door, // 명사 (Noun)
			Is,                                        // 연결자 (Verb)
			You, Push, Stop, Win, Sink, Defeat, Open, Shut,            // 속성 (Property)
			End
			};
		}
		}