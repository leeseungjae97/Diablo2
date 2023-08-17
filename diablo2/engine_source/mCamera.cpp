#include "mCamera.h"
#include "mTransform.h"
#include "mGameObject.h"
#include "mApplication.h"
#include "mRenderer.h"
#include "mSceneManager.h"
#include "mTileManager.h"
#include "mMeshRenderer.h"
#include "mLayer.h"


extern m::Application application;
namespace m
{
	bool CompareZSort(GameObject* a, GameObject* b)
	{
		if (a->GetComponent<Transform>()->GetPosition().z
			<= b->GetComponent<Transform>()->GetPosition().z)
			return false;

		return true;
	}
	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;

	Camera::Camera()
		: Component(eComponentType::Camera)
		, mType(eProjectionType::Orthorgaphic)
		, mAspectRatio(1.0f)
		, mNear(1.0f)
		, mFar(1000.f)
		, mSize(1.0f)
		, mView(Matrix::Identity)
		, mProjection(Matrix::Identity)
	{
		EnableLayerMasks();
		RECT rect = {};
		GetClientRect(application.GetHwnd(), &rect);
		mWidth = (rect.right - rect.left) * mSize;
		mHeight = (rect.bottom - rect.top) * mSize;
	}
	Camera::~Camera()
	{}
	void Camera::Initialize()
	{
		
	}
	void Camera::Update()
	{
		if (mFollowObject)
		{
			GetOwner()->GetComponent<Transform>()->SetPosition(mFollowObject->GetComponent<Transform>()->GetPosition());
		}
	}
	void Camera::LateUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix(mType);
		RegisterCameraInRenderer();
	}
	void Camera::Render()
	{
		View = mView;
		Projection = mProjection;
		mPos = GET_POS(GetOwner());
		AlphaSortGameObject();
		ZSortTransparencyGameObjects();

		RenderOpaque();

		DisableDepthStencilState();

		RenderCutOut();
		RenderTransparent();

		EnableDepthStencilState();
	}
	bool Camera::CreateViewMatrix()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		mView = Matrix::Identity;
		mView *= Matrix::CreateTranslation(-pos);

		Vector3 up = tr->Up();
		Vector3 right = tr->Right();
		Vector3 foward = tr->Foward();

		Matrix viewRotate;
		viewRotate._11 = right.x; viewRotate._12 = up.x; viewRotate._13 = foward.x;
		viewRotate._21 = right.y; viewRotate._22 = up.y; viewRotate._23 = foward.y;
		viewRotate._31 = right.z; viewRotate._32 = up.z; viewRotate._33 = foward.z;
		mView *= viewRotate;

		return true;
	}
	bool Camera::CreateProjectionMatrix(eProjectionType type)
	{
		RECT rect = {};
		GetClientRect(application.GetHwnd(), &rect);
		float width = (rect.right - rect.left) * mSize;
		float height = (rect.bottom - rect.top) * mSize;
		//float width = (rect.right - rect.left);
		//float height = (rect.bottom - rect.top);
		mAspectRatio = width / height;

		if (type == eProjectionType::Orthorgaphic)
		{
			//float orthographicRatio = mSize / 1000.f;
			//width *= orthographicRatio;
			//height *= orthographicRatio;

			mProjection = Matrix::CreateOrthographicLH(width, height, mNear, mFar);
		}
		else
		{
			mProjection = Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.0f, mAspectRatio, mNear, mFar);

		}
		return true;
	}
	void Camera::RegisterCameraInRenderer()
	{
		renderer::cameras.push_back(this);
	}

	void Camera::TurnLayerMask(eLayerType type, bool enable)
	{
		mLayerMask.set((UINT)type, enable);
	}

	void Camera::AlphaSortGameObject()
	{
		mOpaqueGameObjects.clear();
		mCutOutGameObjects.clear();
		mTransparentGameObjects.clear();

		Scene* scene = SceneManager::GetActiveScene();
		for (size_t i = 0; i < (UINT)eLayerType::End; i++)
		{
			if (mLayerMask[i] == true)
			{
				Layer* layer = scene->GetLayer((eLayerType)i);	
				const std::vector<GameObject*>& gameObjs
					= layer->GetGameObjects();
				// layer에 있는 게임오브젝트를 들고온다.
				DivideAlphaBlendGameObjects(gameObjs);
			}
		}
	}

	void Camera::ZSortTransparencyGameObjects()
	{
		std::sort(mCutOutGameObjects.begin()
			, mCutOutGameObjects.end()
			, CompareZSort);
		std::sort(mTransparentGameObjects.begin()
			, mTransparentGameObjects.end()
			, CompareZSort);
	}

	void Camera::DivideAlphaBlendGameObjects(const std::vector<GameObject*>& gameObjs)
	{
		for (GameObject* obj : gameObjs)
		{
			if (obj->GetCamera() != this) continue;
			//렌더러 컴포넌트가 없다면?
			MeshRenderer* mr
				= obj->GetComponent<MeshRenderer>();
			if (mr == nullptr)
				continue;
			if (!ClipingArea(obj)) continue;

			std::shared_ptr<Material> mt = mr->GetMaterial();
			eRenderingMode mode = mt->GetRenderingMode();

			switch (mode)
			{
			case eRenderingMode::Opaque:
				mOpaqueGameObjects.push_back(obj);
				break;
			case eRenderingMode::CutOut:
				mCutOutGameObjects.push_back(obj);
				break;
			case eRenderingMode::Transparent:
				mTransparentGameObjects.push_back(obj);
				break;
			default:
				break;
			}
		}
	}
	bool Camera::ClipingArea(GameObject* gameObj)
	{
		//if (gameObj->GetLayerType() == eLayerType::Tile) return true;

		if (gameObj->GetLayerType() == eLayerType::Skill
			|| gameObj->GetLayerType() == eLayerType::Monster
			|| gameObj->GetLayerType() == eLayerType::MonsterSkill
			|| gameObj->GetLayerType() == eLayerType::PlayerSkill
			|| gameObj->GetLayerType() == eLayerType::Background)
		{
			gameObj->SetCulled(false);
			return true;
		}

		if (Vector2::PointIntersectRect(GET_VEC2_F_VEC3_D(mPos), Vector2(mWidth, mHeight), GET_VEC2_F_VEC3_D(GET_POS(gameObj))))
		{
			//if (gameObj->GetLayerType() == eLayerType::Tile)
			//{
			//	TileManager::notCulledTiles.push_back(dynamic_cast<Tile*>(gameObj));
			//	return true;
			//}
			gameObj->SetCulled(false);
			return true;
		}

		//if (gameObj->GetLayerType() == eLayerType::Tile) return false;

		gameObj->SetCulled(true);
		return false;
	}
	void Camera::RenderOpaque()
	{
		for (GameObject* gameObj : mOpaqueGameObjects)
		{
			if (gameObj == nullptr)
				continue;
			if (gameObj->GetCulled()) continue;

			gameObj->Render();
		}
	}

	void Camera::RenderCutOut()
	{
		for (GameObject* gameObj : mCutOutGameObjects)
		{
			if (gameObj == nullptr)
				continue;
			if (gameObj->GetCulled()) continue;

			gameObj->Render();
		}
	}

	void Camera::RenderTransparent()
	{
		for (GameObject* gameObj : mTransparentGameObjects)
		{
			if (gameObj == nullptr)
				continue;
			if (gameObj->GetCulled()) continue;

			gameObj->Render();
		}
	}
	void Camera::EnableDepthStencilState()
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState
			= renderer::depthStencilStates[(UINT)eDSType::LessEqua];
		GetDevice()->BindDepthStencilState(dsState.Get());
	}

	void Camera::DisableDepthStencilState()
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState
			= renderer::depthStencilStates[(UINT)eDSType::None];
		GetDevice()->BindDepthStencilState(nullptr);
	}
}