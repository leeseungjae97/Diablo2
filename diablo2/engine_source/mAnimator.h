#pragma once
#include "mComponent.h"
#include "mTexture.h"
#include "mGameObject.h"

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
					, float duration = 0.0f);
		Animation* FindAnimation(const std::wstring& name);
		Events* FindEvents(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop);
		void Binds();
		void StopAnimation();

		std::function<void()>& StartEvent(const std::wstring key);
		std::function<void()>& CompleteEvent(const std::wstring key);
		std::function<void()>& EndEvent(const std::wstring key);
		std::function<void()>& ProgressEvent(const std::wstring key);

		Animation* GetActiveAnimation() { return mActiveAnimation; }

		void SetAnimationIndex(int index) { mActiveAnimation->SetIndex(index); }
		int GetAnimationIndex() { return mActiveAnimation->GetIndex(); }

	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;
		Animation* mActiveAnimation;

		bool mbLoop;
	};
}


