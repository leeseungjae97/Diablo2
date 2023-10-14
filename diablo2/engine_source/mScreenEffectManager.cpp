#include "mScreenEffectManager.h"

#include "mMeshRenderer.h"
#include "mTransform.h"
#include "mGameObject.h"
#include "mCamera.h"
#include "mSceneManager.h"
#include "mSoundManager.h"
#include "mTime.h"

namespace m
{
	GameObject* ScreenEffectManager::mFade;
	float ScreenEffectManager::fFadeValue = -1.f;
	Camera* ScreenEffectManager::mUICamera = nullptr;
	Camera* ScreenEffectManager::mPlayCamera = nullptr;
	bool ScreenEffectManager::bFadeIn = false;
	bool ScreenEffectManager::bFadeOut = false;
	bool ScreenEffectManager::bFadeInOut = false;
	bool ScreenEffectManager::bShakeCamera = false;
	float ScreenEffectManager::fShakeTime = 0.f;

	void ScreenEffectManager::Initialize()
	{
		mUICamera = SceneManager::GetActiveScene()->GetSceneUICamera();
		mPlayCamera = SceneManager::GetActiveScene()->GetSceneMainCamera();

		mFade = new GameObject();
		MeshRenderer* mr = ADD_COMP(mFade, MeshRenderer);
		mr->AddTrappingColorBuffer();

		mFade->SetState(GameObject::NoRenderNoUpdate);
		mFade->SetCamera(mUICamera);
		SET_MESH(mFade, L"RectMesh");
		SET_MATERIAL(mFade, L"black");
		SET_SCALE_XYZ(mFade, 1600.f, 900.f, 1.f);
		SET_POS_XYZ(mFade, 0, 0, -1.f);

		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Light, mFade);
	}

	void ScreenEffectManager::Update()
	{
		if (bFadeInOut)
		{
			DoFadeOutIn();
		}
		else
		{
			if (bFadeIn)
			{
				DoFadeIn();
			}
			if (bFadeOut)
			{
				DoFadeOut();
			}
		}
		if (bShakeCamera)
		{
			DoShake();
		}
	}

	void ScreenEffectManager::DoFadeIn()
	{
		if (mFade->GetState() == GameObject::NoRenderNoUpdate)
			mFade->SetState(GameObject::RenderUpdate);

		MeshRenderer* mr = GET_COMP(mFade, MeshRenderer);
		fFadeValue -= 0.5f * Time::fDeltaTime();
		mr->SetTrappingColor(Vector4(0.f, 0.f, 0.f, fFadeValue));

		if (fFadeValue <= 0.f)
		{
			mFade->SetState(GameObject::NoRenderNoUpdate);
			bFadeIn = false;
			bFadeInOut = false;
		}
	}

	void ScreenEffectManager::DoFadeOut()
	{
		if (mFade->GetState() == GameObject::NoRenderNoUpdate)
			mFade->SetState(GameObject::RenderUpdate);

		MeshRenderer* mr = GET_COMP(mFade, MeshRenderer);
		fFadeValue += 0.5f * Time::fDeltaTime();
		mr->SetTrappingColor(Vector4(0.f, 0.f, 0.f, fFadeValue));

		if (fFadeValue >= 1.0f)
		{
			mFade->SetState(GameObject::NoRenderNoUpdate);
			bFadeOut = false;
			if (bFadeInOut) bFadeIn = true;
		}
	}

	void ScreenEffectManager::DoFadeOutIn()
	{
		if (bFadeOut)
			DoFadeOut();

		if (bFadeIn)
			DoFadeIn();
	}

	void ScreenEffectManager::DoShake()
	{
		fShakeTime -= Time::fDeltaTime();
		if (fShakeTime > 0.0f)
		{
			SoundManager::ExternSFXSound(0);
			Vector3 pos = GET_POS(mPlayCamera->GetOwner());

			int randX = rand() % 40;
			int randY = rand() % 40;

			int randXSign = rand() % 2;
			int randYSign = rand() % 2;

			if (randXSign) randX *= -1;
			if (randYSign) randY *= -1;

			pos.y += static_cast<float>(randY);
			pos.x += static_cast<float>(randX);

			SET_POS_VEC(mPlayCamera->GetOwner(), pos);
		}
		else
		{
			SoundManager::StopExtern(SoundManager::eExternAudioType::SFX);
			SoundManager::ResetPlayed(SoundManager::eExternAudioType::SFX);
			bShakeCamera = false;
		}
	}

	void ScreenEffectManager::FadeIn()
	{
		bFadeIn = true; bFadeOut = false; bFadeInOut = false;
		fFadeValue = 1.0f;
	}

	void ScreenEffectManager::FadeOut()
	{
		bFadeIn = false; bFadeOut = true; bFadeInOut = false;
		fFadeValue = 0.0f;
	}

	void ScreenEffectManager::FadeOutIn()
	{
		bFadeIn = false; bFadeOut = true; bFadeInOut = true;
		fFadeValue = 0.0f;
	}
}
