#include "yuzinnaAudioManager.h"
#include "yuzinnaGameObject.h"
#include "yuzinnaSceneManager.h"

namespace yuzinna
{
	AudioSource* AudioManager::mBgmSource = nullptr;
	AudioSource* AudioManager::mSfxSource = nullptr;

	void AudioManager::Initialize()
	{
		Scene* dontDestroyOnLoad = SceneManager::GetDontDestroyOnLoad();
		
		// BGM Player
		GameObject* bgmObj = new GameObject();
		bgmObj->SetName(L"BGMPlayer");
		mBgmSource = bgmObj->AddComponent<AudioSource>();
		mBgmSource->SetSpatialBlend(0.0f);
		dontDestroyOnLoad->AddGameObject(bgmObj, enums::eLayerType::None);

		// SFX Player
		GameObject* sfxObj = new GameObject();
		sfxObj->SetName(L"SFXPlayer");
		mSfxSource = sfxObj->AddComponent<AudioSource>();
		mSfxSource->SetSpatialBlend(0.0f);
		dontDestroyOnLoad->AddGameObject(sfxObj, enums::eLayerType::None);
	}

	void AudioManager::PlayBGM(const std::wstring& name, float volume)
	{
		if (mBgmSource == nullptr) return;

		AudioClip* clip = Resources::Find<AudioClip>(name);
		if (clip == nullptr) return;

		mBgmSource->Stop();
		mBgmSource->SetClip(clip);
		mBgmSource->SetLoop(true);
		mBgmSource->SetVolume(volume);
		mBgmSource->Play();
	}

	void AudioManager::StopBGM()
	{
		if (mBgmSource)
			mBgmSource->Stop();
	}

	void AudioManager::SetBGMVolume(float volume)
	{
		if (mBgmSource)
			mBgmSource->SetVolume(volume);
	}

	void AudioManager::PlaySFX(const std::wstring& name, float volume)
	{
		if (mSfxSource == nullptr) return;

		AudioClip* clip = Resources::Find<AudioClip>(name);
		if (clip == nullptr) return;

		clip->SetVolume(volume);
		mSfxSource->PlayOneShot(clip);
	}

	bool AudioManager::IsBGMPlaying()
	{
		if (mBgmSource == nullptr) return false;
		return mBgmSource->IsPlaying();
	}
}
