#pragma once
#include "yuzinnaAudioSource.h"
#include "yuzinnaAudioClip.h"
#include "yuzinnaResources.h"

namespace yuzinna
{
	class AudioManager
	{
	public:
		static void Initialize();
		
		static void PlayBGM(const std::wstring& name, float volume = 1.0f);
		static void StopBGM();
		static void SetBGMVolume(float volume);

		static void PlaySFX(const std::wstring& name, float volume = 1.0f);

		static bool IsBGMPlaying();

	private:
		static AudioSource* mBgmSource;
		// SFX는 겹쳐서 재생되는 경우가 많으므로 전용 소스를 하나 두거나 
		// PlayOneShot을 활용합니다.
		static AudioSource* mSfxSource; 
	};
}
