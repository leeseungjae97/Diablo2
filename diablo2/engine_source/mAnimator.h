#pragma once
#include "mComponent.h"
#include "mTexture.h"
#include "mGameObject.h"
#include "mAnimation.h"

namespace m
{
	using namespace graphics;

	class Animation;
	class Animator : public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};

		struct Events
		{
			Event startEvent;
			Event completeEvent;
			Event progressEvent;
			Event endEvent;
		};

		Animator();
		~Animator();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		void Create(const std::wstring& name
			, std::shared_ptr<graphics::Texture> atlas
			, Vector2 leftTop
			, Vector2 size
			, UINT columnLength
			, Vector2 offset = Vector2::Zero
			, Vector2 offsetOfCenterPos = Vector2::Zero
			, float duration = 0.0f
			, float alpha = 1.0f);

		void Create(const std::wstring& name
			, std::shared_ptr<graphics::Texture> atlas
			, Vector2 leftTop
			, Vector2 size
			, UINT columnLength
			, Vector2 offset = Vector2::Zero
			, float duration = 0.0f
			, float alpha = 1.0f);

		Animation* FindAnimation(const std::wstring& name);
		Events* FindEvents(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop);
		void SyncPlay();
		void Binds();
		//void StopAnimation();

		std::function<void()>& StartEvent(const std::wstring key);
		std::function<void()>& CompleteEvent(const std::wstring key);
		std::function<void()>& EndEvent(const std::wstring key);
		std::function<void()>& ProgressEvent(const std::wstring key);

		Animation* GetActiveAnimation() { return mActiveAnimation; }
		std::map<std::wstring, Animation*> GetAnimations() { return mAnimations; }
		std::map<std::wstring, Events*> GetEvents() { return mEvents; }
		std::shared_ptr<Texture> GetSpriteSheet() { return mSpriteSheet; }
		bool GetLoop() { return mbLoop; }

		void SetAnimationStartIndex(int index) { mActiveAnimation->SetStartIndex(index); }
		void SetAnimationProgressIndex(int index) { mActiveAnimation->SetProgressIndex(index); }
		void SetAnimationEndIndex(int index) { index != 0 ? mActiveAnimation->SetEndIndex(index) : void(); }
		void SetAnimationIndex(int index) { mActiveAnimation->SetIndex(index); }
		int GetAnimationIndex() { return mActiveAnimation->GetIndex(); }

		void SetSyncAnimator(Animator* sync) { mSyncAnimator = sync; }
		Animator* GetSyncAnimator() { return mSyncAnimator; }
		void Sync() { bSyncPlay = true; }
		void DeSync() { bSyncPlay = false; }

		void SetAnimations(std::map<std::wstring, Animation*> animations) { mAnimations = animations; }
		void SetEvents(std::map<std::wstring, Events*> events) { mEvents = events; }
		void SetSpriteSheet(std::shared_ptr<Texture> sheet) { mSpriteSheet = sheet; }
		void SetActiveAnimation(Animation* animation) { mActiveAnimation = animation; }
		void SetLoop(bool loop) { mbLoop = loop; }

		int GetLoopCount() { return iLoopCount; }

    private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;
		std::shared_ptr<Texture> mSpriteSheet;
		Animator* mSyncAnimator;
		Animation* mActiveAnimation;

		int iLoopCount;
		bool mbLoop;

		bool bSyncPlay;
	};
}


