#include "mAnimator.h"

namespace m
{
	Animator::Animator()
		:Component(eComponentType::Animator)
		, mActiveAnimation(nullptr)
		, mbLoop(false)
		, bSyncPlay(false)
	    , iLoopCount(0)
	{

	}

    Animator::~Animator()
	{
		for (auto& iter : mAnimations)
		{
			if (nullptr == iter.second)
				continue;

			delete iter.second;
			iter.second = nullptr;
		}

		//for (auto& iter : mEvents)
		//{
		//	
		//	if (nullptr == iter.second)
		//		continue;

		//	delete iter.second;
		//	iter.second = nullptr;
		//}

		//std::map<std::wstring, Events*>::iterator iter = mEvents.begin();
		////iter->second.
		//while(iter != mEvents.end())
		//{
		//	
		//	if (iter->second)
		//	{
		//		delete iter->second;
		//		iter->second = nullptr;
		//		++iter;
		//	}
		//	else ++iter;
		//}
	}
	void Animator::Initialize()
	{
	}
	void Animator::Update()
	{
		if (mActiveAnimation == nullptr
			|| mActiveAnimation->IsStop())
			return;

		if (mActiveAnimation->IsComplete() && mbLoop)
		{
			Events* events = FindEvents(mActiveAnimation->GetKey());

			++iLoopCount;

			if (events)
				events->completeEvent();
			mActiveAnimation->Reset();
		}
		if (mActiveAnimation->IsProgress())
		{
			Events* events = FindEvents(mActiveAnimation->GetKey());
			if (events)
				events->progressEvent();
		}
		if (mActiveAnimation->IsComplete() && !mbLoop)
		{
			Events* events = FindEvents(mActiveAnimation->GetKey());
			if (events)
				events->endEvent();
			mActiveAnimation->SetStop();
		}
	}
	void Animator::LateUpdate()
	{
		if (mActiveAnimation == nullptr
			|| mActiveAnimation->IsStop())
			return;


		if(!bSyncPlay)
			mActiveAnimation->LateUpdate();
		else
			SyncPlay();
	}
	void Animator::Render()
	{
	}
	void Animator::Create(const std::wstring& name
		, std::shared_ptr<graphics::Texture> atlas
		, Vector2 leftTop
		, Vector2 size
		, UINT columnLength
		, Vector2 offset
		, Vector2 offsetOfCenterPos
		, float duration
		, float alpha)
	{
		Animation* animation = FindAnimation(name);
		if (nullptr != animation)
			return;

		animation = new Animation();
		animation->SetAnimator(this);
		animation->SetKey(name);

		animation->Create(name
			, atlas
			, leftTop
			, size
			, columnLength
			, offset
			, offsetOfCenterPos
			, duration
			, alpha);

		mAnimations.insert(std::make_pair(name, animation));

		Events* events = FindEvents(name);
		if (nullptr != events)
			return;

		//events = new Events();
		events = {};
		mEvents.insert(std::make_pair(name, events));
	}
	void Animator::Create(const std::wstring& name
						  , std::shared_ptr<graphics::Texture> atlas
						  , Vector2 leftTop
						  , Vector2 size
						  , UINT columnLength
						  , Vector2 offset
						  , float duration
						  , float alpha)
	{
		Animation* animation = FindAnimation(name);
		if (nullptr != animation)
			return;

		animation = new Animation();
		animation->SetAnimator(this);
		animation->SetKey(name);

		animation->Create(name
						  , atlas
						  , leftTop
						  , size
						  , columnLength
						  , offset
						  , duration
						  , alpha);

		mAnimations.insert(std::make_pair(name, animation));

		Events* events = FindEvents(name);
		if (nullptr != events)
			return;

		//events = new Events();
		events = {};
		mEvents.insert(std::make_pair(name, events));
	}
	void Animator::SyncPlay()
	{
		if (nullptr == mSyncAnimator) return;

		int index = mSyncAnimator->GetActiveAnimation()->GetIndex();

		if(!mActiveAnimation->GetEndIndex() < index)
			mActiveAnimation->SetIndex(index);
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter
			= mAnimations.find(name);

		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}
	Animator::Events Animator::FindEvents(const std::wstring& name)
	{
		std::map<std::wstring, Events>::iterator iter
			= mEvents.find(name);

		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}
	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		iLoopCount = 0;
		Animation* prevAnimation = mActiveAnimation;
		Events* events;
		if (prevAnimation != nullptr)
		{
			prevAnimation->Reset();
			events = FindEvents(prevAnimation->GetKey());
			if (events)
				events->endEvent();
		}


		Animation* animation = FindAnimation(name);
		if (animation)
		{
			mActiveAnimation = animation;

		}
		events = FindEvents(mActiveAnimation->GetKey());
		if (events)
			events->startEvent();

		mbLoop = loop;
		mActiveAnimation->Reset();
	}

	void Animator::Binds()
	{
		if (mActiveAnimation == nullptr)
			return;

		mActiveAnimation->Binds();
	}
	std::function<void()>& Animator::StartEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->startEvent.mEvent;
	}
	std::function<void()>& Animator::CompleteEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->completeEvent.mEvent;
	}
	std::function<void()>& Animator::EndEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->endEvent.mEvent;
	}
	std::function<void()>& Animator::ProgressEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->progressEvent.mEvent;
	}
}
