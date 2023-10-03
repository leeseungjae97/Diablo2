#include "mGameObject.h"
#include "mRenderer.h"
#include "mGraphicDevice_DX11.h"
#include "mMeshRenderer.h"
#include "mMouseManager.h"
#include "mSceneManager.h"
#include "mTransform.h"
#include "mScript.h"
namespace m
{
	UINT GameObject::GameObjectIdDispender = 1;
	GameObject::GameObject()
		: mState(eState::RenderUpdate)
		, mBattleState(eBattleState::Idle)
		, mCamera(nullptr)
		, bHover(false)
		, bCulled(false)
		, bTileCulled(false)
		, bRhombus(false)
		, iGameObjectId(0)
	{
		iGameObjectId = GameObjectIdDispender;
		GameObjectIdDispender++;
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		//for (Collider2D* col : GetComponents<Collider2D>())
		//{
		//	if (nullptr == col) continue;
		//	
		//	col->Release();
		//}
		for (Animator* anim : GetComponents<Animator>())
		{
			if (nullptr == anim) continue;
			std::erase(mComponents, anim);
			delete anim;
			anim = nullptr;
		}
		for (Collider2D* col : GetComponents<Collider2D>())
		{
			if (nullptr == col) continue;
			std::erase(mComponents, col);
			delete col;
			col = nullptr;
		}

		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			delete comp;
			comp = nullptr;
		}
		for (Script* script : mScripts)
		{
			if (script == nullptr)
				continue;

			delete script;
			script = nullptr;
		}
	}
	void GameObject::Release()
	{
		for (Collider2D* col : GetComponents<Collider2D>())
		{
			if (nullptr == col) continue;

			col->Release();
		}
	}
	void GameObject::Initialize()
	{
		for (Component* comp : mComponents)
		{
			comp->Initialize();
		}
	}

	void GameObject::Update()
	{
		MousePosHoverGameObject();

		for (Component* comp : mComponents)
		{
			comp->Update();
		}
		for (Script* script : mScripts)
		{
			script->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (Component* comp : mComponents)
		{
			comp->LateUpdate();
		}
		for (Script* script : mScripts)
		{
			script->LateUpdate();
		}
	}

	void GameObject::Render()
	{
		for (Component* comp : mComponents)
		{
			comp->Render();
		}
		for (Script* script : mScripts)
		{
			script->Render();
		}

	}
	void GameObject::MousePosHoverGameObject()
	{
		if (mLayerType == eLayerType::Tile) return;
		if (GetState() != eState::RenderUpdate)
		{
			bHover = false;
			return;
		}
		Transform* tr = GetComponent<Transform>();
		Vector3 mPos = tr->GetPosition();
		Vector3 mScale = tr->GetScale();

		MAKE_VEC2_F_VEC3(mPosV2, mPos);
		MAKE_VEC2_F_VEC3(mScaleV2, mScale);

		if (nullptr == GetCamera()) return;

		Vector3 unprojMousePos = MouseManager::UnprojectionMousePos(mPos.z, GetCamera());
		MAKE_VEC2_F_VEC3(unpMPosV2, unprojMousePos);
		if (bRhombus)
		{
			if (Vector2::PointIntersectRhombus(mPosV2
				, mScaleV2
				, unpMPosV2))
			{
				bHover = true;
			}
			else bHover = false;
		}
		else
		{
			if (Vector2::PointIntersectRect(mPosV2
				, mScaleV2
				, unpMPosV2))
			{
				bHover = true;
			}
			else bHover = false;
		}

	}
	//void GameObject::CreateAnimators(
	//	int count
	//	, std::vector<std::wstring> names
	//	, std::vector<std::shared_ptr<graphics::Texture>> textures
	//	, std::vector<Vector2> leftTops
	//	, std::vector<Vector2> sizes
	//	, std::vector<UINT> columnLengths
	//	, std::vector<Vector2> offsets
	//	, std::vector<float> durations
	//	, std::vector<float> alphas
	//	, std::vector<Vector3> poss
	//)
	//{
	//	if (!subobjects.empty())
	//	{
	//		ReleaseAnimators();
	//	}

	//	SHARED_MAT noneMat = RESOURCE_FIND(Material, L"noneRect");
	//	for (int i = 0; i < count; ++i)
	//	{
	//		GameObject* obj = new GameObject();
	//		obj->SetName(L"animatorObject");

	//		SceneManager::GetActiveScene()->AddGameObject(mLayerType, obj);

	//		Vector3 _pos = poss[i];

	//		SET_POS_VEC(obj, _pos);
	//		//SET_SCALE_XYZ(obj, size.x, size.y, 1.f);

	//		ADD_COMP(obj, MeshRenderer);

	//		SET_MESH(obj, L"RectMesh");
	//		SET_MATERIAL(obj, L"AnimationMaterial");
	//		SET_SCALE_XYZ_WITH_RAT(obj, sizes[i].x, sizes[i].y, 1.f);
	//		Animator* anim = ADD_COMP(obj, Animator);
	//		anim->Create(
	//			names[i]
	//			, textures[i]
	//			, leftTops[i]
	//			, sizes[i]
	//			, columnLengths[i]
	//			, offsets[i]
	//			, durations[i]
	//			, alphas[i]
	//		);

	//		anim->Create(
	//			L"noneRectAnim"
	//			, noneMat->GetTexture()
	//			, Vector2::Zero
	//			, Vector2(20.f, 20.f)
	//			, 1
	//			, Vector2::Zero
	//			, 0.03f
	//		);

	//		//if(animator)
	//		//    anim->SetSyncAnimator(animator);
	//		anim->PlayAnimation(L"noneRectAnim", false);
	//		subobjects.push_back(obj);
	//	}
	//}
	void GameObject::CreateAnimators(
		int count
		, Animator* animator
		, const std::wstring& name
		, std::shared_ptr<graphics::Texture> atlas
		, Vector2 leftTop
		, Vector2 size
		, UINT columnLength
		, Vector2 offset
		, float duration
		, float alpha
	)
	{
		if (!subobjects.empty())
		{
			ReleaseAnimators();
		}

		//Vector3 pos = GET_POS(this);

		SHARED_MAT noneMat = RESOURCE_FIND(Material, L"noneRect");
		for (int i = 0; i < count; ++i)
		{
			GameObject* obj = new GameObject();
			obj->SetName(L"animatorObject");
			
			SceneManager::GetActiveScene()->AddGameObject(mLayerType, obj);

			//pos.x += 30.f;
			//pos.y += 30.f;

			//SET_POS_VEC(obj, pos);
			//SET_SCALE_XYZ(obj, size.x, size.y, 1.f);

			ADD_COMP(obj, MeshRenderer);

			SET_MESH(obj, L"RectMesh");
			SET_MATERIAL(obj, L"AnimationMaterial");
			
			Animator* anim = ADD_COMP(obj, Animator);
			anim->Create(name, atlas, leftTop, size, columnLength, offset, duration, alpha);
			anim->Create(
				L"noneRectAnim"
				, noneMat->GetTexture()
				, Vector2::Zero
				, Vector2(20.f, 20.f)
				, 1
				, Vector2::Zero
				, 0.03f
			);

			//if(animator)
			//    anim->SetSyncAnimator(animator);
			anim->PlayAnimation(L"noneRectAnim", true);
			subobjects.push_back(obj);
		}
	}
	//void GameObject::PlayRandPosAnimators(const std::wstring playName, bool loop, Vector2 size, Vector2 randPosRange)
	//{
	//	int i = 0;
	//	for (GameObject* obj : subobjects)
	//	{
	//		Vector3 pos = GET_POS(this);

	//		int randXPos = rand() % (int)randPosRange.x;
	//		int randYPos = rand() % (int)randPosRange.y;

	//		Vector3 _pos = Vector3(pos.x + randXPos, pos.y + randYPos, pos.z);

	//		obj->SetCamera(mCamera);
	//		ADD_COMP(obj, Collider2D);

	//		SET_POS_VEC(obj, _pos);
	//		SET_SCALE_XYZ_WITH_RAT(obj, size.x, size.y, 1.f);
	//		Animator* animator = GET_COMP(obj, Animator);
	//		animator->PlayAnimation(playName, loop);
	//		//animator->SyncPlay();
	//	}
	//}
	//void GameObject::PlayAnimators(std::vector<std::wstring> playName, bool loop, std::vector<Vector3> pos, int loopStartIndex, int loopEndIndex, int loopCount)
	//{
	//	for (int i = 0 ; i < subobjects.size(); ++i)
	//	{
	//		GameObject* obj = subobjects[i];
	//		obj->SetCamera(mCamera);
	//		ADD_COMP(obj, Collider2D);

	//		SET_POS_VEC(obj, pos[i]);
	//		//SET_SCALE_XYZ_WITH_RAT(obj, size[i].x, size[i].y, 1.f);

	//		Animator* animator = GET_COMP(obj, Animator);
	//		animator->PlayAnimation(playName[i], loop);
	//	}
	//}
	void GameObject::PlayAnimators(const std::wstring playName, bool loop, Vector2 size, bool useDirect, Collider2D* col)
	{
		int i = 0;

		float minX = D3D11_FLOAT32_MAX;
		float minY = D3D11_FLOAT32_MAX;
		float maxX = -D3D11_FLOAT32_MAX;
		float maxY = -D3D11_FLOAT32_MAX;

		for (GameObject* obj : subobjects)
		{
			Vector3 pos = GET_POS(this);
			
			obj->SetCamera(mCamera);

			if(useDirect)
			{
				pos.x += 50.f * direct1[i % 4].x;
				pos.y += 50.f * direct1[i % 4].y;
				++i;
			}


			SET_POS_VEC(obj, pos);
			maxX = max(maxX, pos.x + (size.x / 2.f) * Texture::GetWidRatio());
			maxY = max(maxY, pos.y + (size.y / 2.f) * Texture::GetHeiRatio());

			minX = min(minX,pos.x - (size.x / 2.f) * Texture::GetWidRatio());
			minY = min(minY,pos.y - (size.y / 2.f) * Texture::GetHeiRatio());

			SET_SCALE_XYZ_WITH_RAT(obj, size.x, size.y, 1.f);
			Animator* animator = GET_COMP(obj, Animator);
			animator->PlayAnimation(playName, loop);

			//animator->SyncPlay();
		}
		float scaleX = maxX - minX;
		float scaleY = maxY - minY;

		col->SetScale(Vector3(scaleX, scaleY, 1.f));
	}

	void GameObject::ReleaseAnimators()
	{
		for (GameObject* obj : subobjects) obj->SetState(Delete);
		subobjects.clear();
	}
}
