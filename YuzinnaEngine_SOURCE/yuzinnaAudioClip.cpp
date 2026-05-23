#include "yuzinnaAudioClip.h"
namespace yuzinna
{
	AudioClip::AudioClip()
		: Resource(enums::eResourceType::AudioClip)
		, mSound(nullptr)
		, mChannel(nullptr)
		, mMinDistance(100.0f)   // 2D 픽셀 단위에 맞게 최소 거리 상향
		, mMaxDistance(5000.0f)  // 최대 거리 상향
		, mbLoop(false)
		, mVolume(1.0f)
	{
	}

	AudioClip::~AudioClip()
	{
		if (mSound)
			mSound->release();
		mSound = nullptr;
	}

	HRESULT AudioClip::Load(const std::wstring& path)
	{
		std::string cPath(path.begin(), path.end());
		if (!Fmod::CreateSound(cPath, &mSound))
			return S_FALSE;

		mSound->set3DMinMaxDistance(mMinDistance, mMaxDistance);

		return S_OK;
	}

	void AudioClip::Play(bool is3D)
	{
		if (mbLoop)
			mSound->setMode(FMOD_LOOP_NORMAL);
		else
			mSound->setMode(FMOD_LOOP_OFF);

		Fmod::SoundPlay(mSound, &mChannel);
		mChannel->setVolume(mVolume);

		if (is3D)
			mChannel->setMode(FMOD_3D);
		else
			mChannel->setMode(FMOD_2D);
	}

	void AudioClip::PlayOneShot(bool is3D)
	{
		if (mbLoop)
			mSound->setMode(FMOD_LOOP_NORMAL);
		else
			mSound->setMode(FMOD_LOOP_OFF);

		FMOD::Channel* channel = nullptr;
		Fmod::SoundPlay(mSound, &channel);
		channel->setVolume(mVolume);

		if (is3D)
			channel->setMode(FMOD_3D);
		else
			channel->setMode(FMOD_2D);
	}

	void AudioClip::Stop()
	{
		if (mChannel)
			mChannel->stop();
	}

	void AudioClip::Set3DAttributes(const Vector2 pos)
	{
		Set3DAttributes(mChannel, pos);
	}

	void AudioClip::Set3DAttributes(FMOD::Channel* channel, const Vector2 pos)
	{
		if (channel == nullptr)
			return;

		FMOD_VECTOR fmodPos(pos.x, pos.y, 0.0f);
		FMOD_VECTOR fmodVel(0.0f, 0.0f, 0.0f);

		channel->set3DAttributes(&fmodPos, &fmodVel);
	}

	void AudioClip::SetVolume(float volume)
	{
		mVolume = volume;
		if (mChannel)
		{
			mChannel->setVolume(mVolume);
		}
	}

	bool AudioClip::IsPlaying()
	{
		if (mChannel == nullptr)
			return false;

		bool isPlaying = false;
		mChannel->isPlaying(&isPlaying);

		return isPlaying;
	}

}