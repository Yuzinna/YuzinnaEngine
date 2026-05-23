#pragma once
#include "yuzinnaComponent.h"
#include "yuzinnaAudioClip.h"

namespace yuzinna
{

	class AudioSource : public Component
	{
	public:
		AudioSource();
		~AudioSource();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void Play();
		void PlayOneShot(AudioClip* clip);
		void Stop();
		void SetLoop(bool loop);
		void SetSpatialBlend(float blend) { mSpatialBlend = blend; }

		void SetClip(AudioClip* clip) { mAudioClip = clip; }
		AudioClip* GetClip() { return mAudioClip; }
		void SetVolume(float volume);
		bool IsPlaying();

	private:
		AudioClip* mAudioClip;
		float mSpatialBlend;
	};
}

