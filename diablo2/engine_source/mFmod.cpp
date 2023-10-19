#include "mFmod.h"
namespace m
{
    FMOD::Studio::System* Fmod::mSystem = nullptr;
    FMOD::System* Fmod::mCoreSystem = nullptr;
	FMOD::ChannelGroup* Fmod::mFootStepGroup = nullptr;
	FMOD::ChannelGroup* Fmod::mSkillFireGroup = nullptr;
	FMOD::ChannelGroup* Fmod::mSkillCrashGroup = nullptr;



	void Fmod::Initialize()
	{
		void* extraDriverData = NULL;
		FMOD::Studio::System::create(&mSystem);
		mSystem->getCoreSystem(&mCoreSystem);
		mCoreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0);

		mSystem->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, extraDriverData);
		mCoreSystem->createChannelGroup("footStep", &mFootStepGroup);
		mCoreSystem->createChannelGroup("skillFire", &mSkillFireGroup);
		mCoreSystem->createChannelGroup("skillCrash", &mSkillCrashGroup);
	}
	void Fmod::Update()
	{
		mCoreSystem->update();
	}
	bool Fmod::CreateSound(const std::string& path, FMOD::Sound** sound)
	{
		if (FMOD_OK != mCoreSystem->createSound(path.c_str(), FMOD_3D | FMOD_3D_LINEARROLLOFF, 0, sound))
			return false;

		return true;
	}

	void Fmod::SoundPlay(FMOD::Sound* sound, FMOD::Channel** channel)
	{
		mCoreSystem->playSound(sound, 0, false, channel);
	}
	void Fmod::SkillFireSoundPlay(FMOD::Sound* sound, FMOD::Channel** channel)
	{
		mCoreSystem->playSound(sound, mSkillFireGroup, false, channel);
	}

	void Fmod::SkillCrashSoundPlay(FMOD::Sound* sound, FMOD::Channel** channel)
	{
		mCoreSystem->playSound(sound, mSkillCrashGroup, false, channel);
	}

	void Fmod::RunSoundPlay(FMOD::Sound* sound, FMOD::Channel** channel)
	{
		mCoreSystem->playSound(sound, mFootStepGroup, false, channel);
	}
	void Fmod::StopFireChannelGroup()
	{
		mSkillFireGroup->stop();
	}

	void Fmod::Set3DListenerAttributes(const Vector3* pos, const Vector3* vel, const Vector3* forward, const Vector3* up)
	{
		FMOD_VECTOR fmodPos(pos->x, pos->y, pos->z);
		FMOD_VECTOR fmodForward(0, 0, 1);
		FMOD_VECTOR fmodUp(0, 1, 0);

		FMOD_VECTOR listenerPos = {0.0f, 0.0f, 0.0f};

		mCoreSystem->set3DListenerAttributes(0, &fmodPos, &listenerPos, &fmodForward, &fmodUp);
	}

	void Fmod::Release()
	{
		//mCoreSystem->release();
		//mCoreSystem = nullptr;

		mSystem->release();
		mSystem = nullptr;
	}
}
