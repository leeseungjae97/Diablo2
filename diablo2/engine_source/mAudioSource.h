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


		void Play(ePlayerVoiceSoundType type, bool loop = false);
		void Play(eButtonSoundType type, bool loop = false);
		void PlaySounds(ePlayerRunSoundType type, bool loop = false);
		void Play(ePlayerRunSoundType type, bool loop = false);
		void Stop();
		void Stop(eAudioClipType type);

		std::shared_ptr<AudioClip> FindClip(ePlayerVoiceSoundType type);
		std::shared_ptr<AudioClip> FindClip(eButtonSoundType type);
		std::shared_ptr<AudioClip> FindClip(ePlayerRunSoundType type);

		std::shared_ptr<AudioClip> GetClip(eAudioClipType audioType) { return mAudioClips[(int)audioType]; }

	private:
		std::vector<std::shared_ptr<AudioClip>> mAudioClips;
		bool bActiveAudioClip[(int)eAudioClipType::End] = {false,false, false, false, false};

		eButtonSoundType mButtonSoundType;
		ePlayerRunSoundType mRunSoundType;

		int iRunIndex;

		bool bRun;
		float fRunAcc;

		bool bLoopGroupSound;
		bool bNextPlay;

		int iRandPlayIndex;
	};
}
