#include "mAnimator.h"
#include "mAnimation.h"
namespace m
{
	Animator::Animator()
		:Component(eComponentType::Animator)
		, mActiveAnimation(nullptr)
		, mbLoop(false)
	{

	}
	Animator::~Animator()
	{
		for (auto& iter : mAnimations)
		{
			delete iter.second;
			iter.second = nullptr;
		}

		for (auto& iter : mEvents)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
	void Animator::Initialize()
	{
	}
	void Animator::Update()
	{
		if (mActiveAnimation == nullptr)
			return;

		if (mActiveAnimation->IsComplete() && mbLoop)
		{
			Events* events = FindEvents(mActiveAnimation->GetKey());
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
			mActiveAnimation->Reset();
		}

		mActiveAnimation->LateUpdate();
	}
	void Animator::LateUpdate()
	{
	}
	void Animator::Render()
	{
	}
	//void Animator::CreateAnimation(const std::wstring& name
	//							   , std::shared_ptr<Texture> sheet, Vector2 leftTop
	//							   , UINT coulmn, UINT row, UINT spriteLength
	//							   , Vector2 offset, float duration)
	//{
	//	Animation* animation = FindAnimation(name);
	//	if (animation != nullptr)
	//		return;

	//	animation = new Animation();
	//	animation->Create(name, sheet, leftTop, Vector2(0.f, 0.f), spriteLength, offset, duration);
	//	animation->SetKey(name);
	//	//animation->SetAnimator(this);

	//	mAnimations.insert(std::make_pair(name, animation));
	//	Events* event = new Events();
	//	mEvents.insert(std::make_pair(name, event));
	//}
	//void Animator::CreateAnimations(const std::wstring& path, Vector2 offset, float duration)
	//{
	//	UINT width = 0;
	//	UINT height = 0;
	//	UINT fileCount = 0;

	//	std::filesystem::path fs(path);
	//	std::vector<std::shared_ptr<Texture>> textures = {};
	//	for (const auto& p : std::filesystem::recursive_directory_iterator(path))
	//	{
	//		std::wstring fileName = p.path().filename();
	//		std::wstring fullName = path + L"\\" + fileName;

	//		const std::wstring ext = p.path().extension();
	//		if (ext == L".png")
	//			continue;

	//		std::shared_ptr<Texture> tex= Resources::Load<Texture>(fileName, fullName);
	//		textures.push_back(tex);

	//		if (width < tex->GetWidth())
	//		{
	//			width = tex->GetWidth();
	//		}
	//		if (height < tex->GetHeight())
	//		{
	//			height = tex->GetHeight();
	//		}
	//		fileCount++;
	//	}

	//	std::wstring key = fs.parent_path().filename();
	//	//key += fs.filename();
	//	//mSpriteSheet = Image::Create(key, width * fileCount, height);

	//	int index = 0;
	//	for (std::shared_ptr<Texture> tex : textures)
	//	{
	//		int centerX = (width - tex->GetWidth()) / 2;
	//		int centerY = (height - tex->GetHeight());

	//		//BitBlt(mSpriteSheet->GetHdc()
	//		//	   , width * index + centerX
	//		//	   , 0 + centerY
	//		//	   , image->GetWidth(), image->GetHeight()
	//		//	   , image->GetHdc(), 0, 0, SRCCOPY);

	//		index++;
	//	}

	//	CreateAnimation(key, mSpriteSheet, Vector2::Zero, index, 1, index, offset, duration);
	//}
	void Animator::Create(const std::wstring& name
						  , std::shared_ptr<graphics::Texture> atlas
						  , Vector2 leftTop
						  , Vector2 size
						  , UINT columnLength
						  , Vector2 offset
						  , float duration)
	{
		Animation* animation = FindAnimation(name);
		if (nullptr != animation)
			return;

		animation = new Animation();
		animation->SetKey(name);

		animation->Create(name
						  , atlas
						  , leftTop
						  , size
						  , columnLength
						  , offset
						  , duration);

		mAnimations.insert(std::make_pair(name, animation));

		Events* events = FindEvents(name);
		if (nullptr != events)
			return;

		events = new Events();
		mEvents.insert(std::make_pair(name, events));
	}
	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter
			= mAnimations.find(name);

		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}
	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		std::map<std::wstring, Events*>::iterator iter
			= mEvents.find(name);

		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}
	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		Animation* prevAnimation = mActiveAnimation;

		Events* events;
		if (prevAnimation != nullptr)
		{
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
	void Animator::StopAnimation()
	{
		if (mActiveAnimation == nullptr)
			return;

		mActiveAnimation->Reset();
		
		mActiveAnimation = nullptr;
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