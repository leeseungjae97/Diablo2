#include "mAnimation.h"
#include "mTime.h"
#include "mAnimator.h"
#include "mRenderer.h"

namespace m
{
	Animation::Animation()
		: Resource(eResourceType::Animation)
		, mAtlas(nullptr)
		, mAnimator(nullptr)
		, mSprites{}
		, mCurIndex(0)
		, mEndIndex(0)
		, mTime(0.0f)
		, mAnimStartIndex(0)
		, mAnimProgressIndex(0)
		, mAnimEndIndex(0)
		, mbComplete(false)
		, mbProgress(false)
		, mbStop(false)
	{

	}
	Animation::~Animation()
	{
	}
	void Animation::Update()
	{
	}
	void Animation::LateUpdate()
	{
		if (mbComplete || mbStop)
			return;

		mTime += Time::DeltaTime();

		if (mSprites[mCurIndex].duration <= mTime)
		{
			mCurIndex++;
			mTime = 0.0f;

			if (mEndIndex <= mCurIndex)
			{
				//mCurIndex = mSprites.size() - 1;
				mCurIndex = mEndIndex - 1;
				mbComplete = true;
			}
		}
		if (mCurIndex == mAnimProgressIndex)
		{
			mbProgress = true;
		}
	}
	void Animation::Render()
	{
	}
	void Animation::Create(std::wstring name
		, std::shared_ptr<graphics::Texture> atlas
		, Vector2 leftTop
		, Vector2 size
		, UINT columnLength
		, Vector2 offset
		, Vector2 offsetOfCenterPos
		, float duration
		, float alpha)
	{
		SetKey(name);
		mAtlas = atlas;

		float width = (float)atlas->GetMetaDataWidth();
		float height = (float)atlas->GetMetaDataHeight();

		for (size_t i = 0; i < columnLength; i++)
		{
			Sprite sprite = {};
			sprite.leftTop.x = leftTop.x + (i * size.x) / width;
			sprite.leftTop.y = leftTop.y / height;
			sprite.size.x = size.x / width;
			sprite.size.y = size.y / height;
			sprite.offset.x = offset.x / width;
			sprite.offset.y = offset.y / height;
			sprite.offsetOfCenterPos.x = offsetOfCenterPos.x / width;
			sprite.offsetOfCenterPos.y = offsetOfCenterPos.y / height;
			sprite.atlasSize = Vector2(size.x / width, size.y / height);
			sprite.duration = duration;
			sprite.alpha = alpha;

			mSprites.push_back(sprite);
		}
	}
	void Animation::Create(std::wstring name
						   , std::shared_ptr<graphics::Texture> atlas
						   , Vector2 leftTop
						   , Vector2 size
						   , UINT columnLength
						   , Vector2 offset
						   , float duration
						   , float alpha)
	{
		SetKey(name);
		mAtlas = atlas;

		float width = (float)atlas->GetMetaDataWidth();
		float height = (float)atlas->GetMetaDataHeight();
		mLength = columnLength;
		for (size_t i = 0; i < columnLength; i++)
		{
			Sprite sprite = {};
			sprite.leftTop.x = leftTop.x + (i * size.x) / width;
			sprite.leftTop.y = leftTop.y / height;
			sprite.size.x = size.x / width;
			sprite.size.y = size.y / height;
			sprite.offset.x = offset.x / width;
			sprite.offset.y = offset.y / height;
			sprite.atlasSize = Vector2(size.x / width, size.y / height);
			sprite.duration = duration;
			sprite.alpha = alpha;

			mSprites.push_back(sprite);
		}
	}

	void Animation::Binds()
	{
		// texture bind
		mAtlas->BindShaderResource(eShaderStage::PS, 16);

		// AnimationCB
		renderer::AnimatorCB data = {};

		data.spriteLeftTop = mSprites[mCurIndex].leftTop;
		data.spriteSize = mSprites[mCurIndex].size;
		data.spriteOffset = mSprites[mCurIndex].offset;
		data.atlasSize = mSprites[mCurIndex].atlasSize;
		data.spriteOffsetOfCenterPos = mSprites[mCurIndex].offsetOfCenterPos;
		data.animationType = 1;
		data.alpha = mSprites[mCurIndex].alpha;

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animator];
		cb->SetData(&data);

		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}
	void Animation::Reset()
	{
		mTime = 0.0f;
		mbComplete = false;
		mbProgress = false;
		mbStop = false;
		mCurIndex = mAnimStartIndex;
		mEndIndex = mAnimEndIndex == 0 ? mSprites.size() : mAnimEndIndex;
	}
}