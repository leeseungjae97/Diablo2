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
			Vector2 offsetOfCenterPos;

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
			, Vector2 offsetOfCenterPos = Vector2::Zero
			, float duration = 0.0f
			, float alpha = 1.0f);

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

		void SetStop() { mbStop = true; }
		void SetReverse(bool loop);
		void SetIndex(int index) { mCurIndex = index; }
		void SetStartIndex(int index) { mAnimStartIndex = index; }
		void SetProgressIndex(int index) { mAnimProgressIndex = index; }
		void SetEndIndex(int index) { mAnimEndIndex = index; }

		const Sprite& GetCurrentSprite() { return mSprites[mCurIndex]; }

		int GetAltasLength() { return mSprites.size(); }
		int GetIndex() { return mCurIndex; }
		int GetProgressIndex() { return mAnimProgressIndex; }
		int GetEndIndex() { return mEndIndex; }
		bool IsComplete() { return mbComplete; }
		bool IsProgress() { return mbProgress; }
		bool IsStop() { return mbStop; }

		void SetAnimator(Animator* animator) { mAnimator = animator; }
	private:
		int mLength;
		std::shared_ptr<graphics::Texture> mAtlas;

		Animator* mAnimator;
		std::vector<Sprite> mSprites;
		int mEndIndex;
		int mCurIndex;
		
		int mAnimEndIndex;
		int mAnimStartIndex;
		int mAnimProgressIndex;

		float mTime;
		bool mbComplete;
		bool mbProgress;
		bool mbStop;
		bool mbReverse;
	};
}

