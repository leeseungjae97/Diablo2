#pragma once
#include "mResource.h"
#include "mTexture.h"

namespace m
{
	using namespace math;
	using namespace graphics;

	class Animator;
	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;
			Vector2 atlasSize;
			float duration;
			float alpha;

			Sprite()
				: leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, atlasSize(Vector2::Zero)
				, duration(0.0f)
			{

			}
		};

		Animation();
		~Animation();

		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; };

		void Update();
		void LateUpdate();
		void Render();

		void Create(std::wstring name
					, std::shared_ptr<graphics::Texture> atlas
					, Vector2 leftTop
					, Vector2 size
					, UINT columnLength
					, Vector2 offset = Vector2::Zero
					, float duration = 0.0f
					, float alpha = 1.0f);

		void Binds();
		void Reset();
		void SetIndex(int index) { mIndex = index; }
		void SetInitIndex(int index) { mInitIndex = index; }
		void SetProgressIndex(int index) { mProgressIndex = index; }
		const Sprite& GetCurrentSprite() { return mSprites[mIndex]; }

		int GetIndex() { return mIndex; }
		int GetProgressIndex() { return mProgressIndex; }
		bool IsComplete() { return mbComplete; }
		bool IsProgress() { return mbProgress; }
	private:
		std::shared_ptr<graphics::Texture> mAtlas;
		Animator* mAnimator;
		std::vector<Sprite> mSprites;
		int mInitIndex;
		int mIndex;
		int mProgressIndex;
		float mTime;
		bool mbComplete;
		bool mbProgress;
	};
}

