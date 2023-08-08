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
		, mIndex(-1)
		, mTime(0.0f)
		, mInitIndex(0)
		, mProgressIndex(0)
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

		if (mSprites[mIndex].duration <= mTime)
		{
			mIndex++;
			mTime = 0.0f;

			if (mSprites.size() <= mIndex)
			{
				mIndex = mSprites.size() - 1;
				mbComplete = true;
			}
		}
		if (mIndex == mProgressIndex)
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
			sprite.atlasSize = Vector2(size.x / width, size.y / height);
			sprite.duration = duration;
			sprite.alpha = alpha;

			mSprites.push_back(sprite);
		}
	}

	void Animation::Binds()
	{
		// texture bind
		mAtlas->BindShaderResource(eShaderStage::PS, 12);

		// AnimationCB
		renderer::AnimatorCB data = {};

		data.spriteLeftTop = mSprites[mIndex].leftTop;
		data.spriteSize = mSprites[mIndex].size;
		data.spriteOffset = mSprites[mIndex].offset;
		data.atlasSize = mSprites[mIndex].atlasSize;
		data.animationType = 1;
		data.alpha = mSprites[mIndex].alpha;

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
		mIndex = mInitIndex;
		mbStop = false;
	}
}