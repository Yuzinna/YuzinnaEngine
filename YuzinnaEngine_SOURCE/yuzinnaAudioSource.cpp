#include "yuzinnaAudioSource.h"
#include "yuzinnaTransform.h"
#include "yuzinnaGameObject.h"
#include "yuzinnaFmod.h"

namespace yuzinna
{
	AudioSource::AudioSource()
		: Component(eComponentType::AudioSource)
		, mAudioClip(nullptr)
		, mSpatialBlend(1.0f) // 기본값은 3D (1.0)
	{
	}

	AudioSource::~AudioSource()
	{
	}

	void AudioSource::Initialize()
	{
	}

	void AudioSource::Update()
	{
	}

	void AudioSource::LateUpdate()
	{
		if (mAudioClip == nullptr)
			return;

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		mAudioClip->Set3DAttributes(pos);
	}

	void AudioSource::Render(HDC hdc)
	{
	}

	void AudioSource::Play()
	{
		if (mAudioClip == nullptr)
			return;

		// blend가 0.5보다 작으면 2D, 크면 3D로 취급 (유니티 스타일)
		 bool is3D = (mSpatialBlend > 0.5f);
		 mAudioClip->Play(is3D);
	}

	void AudioSource::PlayOneShot(AudioClip* clip)
	{
		if (clip == nullptr)
			return;

		bool is3D = (mSpatialBlend > 0.5f);
		clip->PlayOneShot(is3D);

		if (is3D)
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			clip->Set3DAttributes(tr->GetPosition());
		}
	}

	void AudioSource::Stop()
	{
		if (mAudioClip == nullptr)
			return;

		mAudioClip->Stop();
	}

	void AudioSource::SetLoop(bool loop)
	{
		mAudioClip->SetLoop(loop);
	}

	void AudioSource::SetVolume(float volume)
	{
		if (mAudioClip)
			mAudioClip->SetVolume(volume);
	}

	bool AudioSource::IsPlaying()
	{
		if (mAudioClip == nullptr)
			return false;

		return mAudioClip->IsPlaying();
	}

}



