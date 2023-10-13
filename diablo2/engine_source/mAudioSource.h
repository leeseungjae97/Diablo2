#pragma once
#include "mComponent.h"
#include "mAudioClip.h"
#include "SoundLookUpTables.h"

namespace m
{
	class AudioSource : public Component
	{
	public:
		enum class eAudioClipType
		{
		    FootStep,
			Voice,
			Cast,
			Fire,
			Crash,
			End,
		};
		AudioSource();
		~AudioSource();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void ReleaseClips();

		void Play(ePlayerVoiceSoundType type, bool loop = false, bool b3DAt = true);
		void Play(eButtonSoundType type, bool loop = false, bool b3DAt = true);
		void Play(const std::wstring& name, bool loop = false, bool b3DAt = true);
		void PlayGroup(const std::wstring& name, bool loop = false, bool b3DAt = true);
		void PlayNoDelay(const std::wstring& name, bool loop = false, bool b3DAt = true, float vol = 30.f);
		void PlaySounds(ePlayerRunSoundType type, bool loop = false, bool b3DAt = true);
		void Stop();
		void Stop(eAudioClipType type);
		
		FMOD::Sound* FindSound(ePlayerVoiceSoundType type);
		FMOD::Sound* FindSound(eButtonSoundType type);
		FMOD::Sound* FindSound(ePlayerRunSoundType type);
		FMOD::Sound* FindSound(const std::wstring& name);

		AudioClip* GetClip(eAudioClipType audioType) { return mAudioClips[(int)audioType]; }
        void StopAll();

    private:
		std::vector<AudioClip*> mAudioClips;
		std::vector<AudioClip*> mAudioClipGroup;
		std::vector<AudioClip*> mUsedAudioClip;
		bool bActiveAudioClip[(int)eAudioClipType::End] = {false,false, false, false, false};
		bool bAudioClip3DAtr[(int)eAudioClipType::End] = {true,true, true, true, true};

		eButtonSoundType mButtonSoundType;
		ePlayerRunSoundType mRunSoundType;

		int iRunIndex;

		bool bRun;
		float fRunAcc;

		bool bGroupSound;
		bool bNextPlay;

		int iRandPlayIndex;
	};
}
