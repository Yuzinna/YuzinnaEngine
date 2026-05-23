#pragma once
#include "yuzinnaFmod.h"
#include "yuzinnaResource.h"

namespace yuzinna
{
	class AudioClip : public Resource
	{
	public:
		AudioClip();
		virtual ~AudioClip();

		virtual HRESULT Load(const std::wstring& path) override;

		void Play(bool is3D = true);
		void PlayOneShot(bool is3D = true);
		void Stop();
		void Set3DAttributes(const Vector2 pos);
		void Set3DAttributes(FMOD::Channel* channel, const Vector2 pos);
		void SetLoop(bool loop) { mbLoop = loop; }
		void SetVolume(float volume);
		float GetVolume() { return mVolume; }
		bool IsPlaying();

	private:
		FMOD::Sound* mSound;
		FMOD::Channel* mChannel;
		float mMinDistance;
		float mMaxDistance;
		bool mbLoop;
		float mVolume;
	};
}


