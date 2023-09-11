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
	UINT GameObject::GameObjectIdDispender = 0;
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
		for (Collider2D* col : GetComponents<Collider2D>())
		{
			if (nullptr == col) continue;
			std::erase(mComponents, col);
			if (GetState() == eState::Delete)
				col->Release();

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
			anim->PlayAnimation(L"noneRectAnim", false);
			subobjects.push_back(obj);
		}
	}

	void GameObject::PlayAnimators(const std::wstring playName, bool loop, Vector2 size)
	{
		int i = 0; 
		for (GameObject* obj : subobjects)
		{
			Vector3 pos = GET_POS(this);
			
			obj->SetCamera(mCamera);
			ADD_COMP(obj, Collider2D);

			pos.x += 50.f * direct1[i].x;
			pos.y += 50.f * direct1[i].y;

			++i;

			SET_POS_VEC(obj, pos);
			SET_SCALE_XYZ_WITH_RAT(obj, size.x, size.y, 1.f);
			Animator* animator = GET_COMP(obj, Animator);
			animator->PlayAnimation(playName, loop);
			//animator->SyncPlay();
		}
	}

	void GameObject::ReleaseAnimators()
	{
		for (GameObject* obj : subobjects) obj->SetState(Delete);
		subobjects.clear();
	}
}
