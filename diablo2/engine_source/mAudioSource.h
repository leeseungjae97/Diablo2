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
			Click,
			Hover,
			End,
		};
		AudioSource();
		~AudioSource();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void ReleaseClips();

		void HoverPlay(int type, std::wstring name, bool loop = false, bool b3DAt = false);
		void Play(eUISoundType type, bool loop = false, bool b3DAt = false);
		
		void Play(ePlayerVoiceSoundType type, bool loop = false, bool b3DAt = true);
		void Play(const std::wstring& name, bool loop = false, bool b3DAt = true);
		void Play(int type, const std::wstring& name, bool loop = false, bool b3DAt = true);
		void PlayOnce(int type, std::wstring name, bool loop = false, bool b3DAt = true, bool bNoDelay = false, float vol = 30.f);
		void PlayMonsterVoice(std::wstring name, bool loop = false, bool b3DAt = true);
		void PlayGroup(const std::wstring& name, bool loop = false, bool b3DAt = true);
		void PlayNoDelay(int type, const std::wstring& name, bool loop = false, bool b3DAt = true, float vol = 30.f);
		void PlayNoDelay(const std::wstring& name, bool loop = false, bool b3DAt = true, float vol = 30.f);
		void PlaySounds(ePlayerRunSoundType type, bool loop = false, bool b3DAt = true);
		void Stop();
		void Stop(eAudioClipType type);
		void Stop(int type);

		void ResetAllSoundPlayed();
		void ResetSoundPlayed(int type);
		FMOD::Sound* FindSound(ePlayerVoiceSoundType type);
		FMOD::Sound* FindSound(eUISoundType type);
		FMOD::Sound* FindSound(ePlayerRunSoundType type);
		FMOD::Sound* FindSound(const std::wstring& name);

		AudioClip* GetClip(eAudioClipType audioType) { return mAudioClips[(int)audioType]; }
        void StopAll();

    private:
		std::vector<AudioClip*> mAudioClips;
		std::vector<AudioClip*> mAudioClipGroup;
		std::vector<AudioClip*> mUsedAudioClip;
		bool bActiveAudioClip[(int)eAudioClipType::End] = {false,false, false, false, false, false, false};
		bool bAudioClip3DAtr[(int)eAudioClipType::End] = {true,true, true, true, true, false, false};
		bool bAudioPlayOnce[(int)eAudioClipType::End] = { false, false, false, false, false, false, false};
		eUISoundType mButtonSoundType;
		ePlayerRunSoundType mRunSoundType;

		int iRunIndex;

		bool bRun;
		float fRunAcc;

		bool bGroupSound;
		bool bNextPlay;

		int iRandPlayIndex;
	};
}
