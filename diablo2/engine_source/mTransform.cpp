#include "mTransform.h"

#include "mApplication.h"
#include "mRenderer.h"
#include "mConstantBuffer.h"
#include "mCamera.h"
#include "mGameObject.h"

extern m::Application application;
namespace m
{
	Transform::Transform()
		: Component(eComponentType::Transform)
		, mPosition(Vector3::Zero)
		, mRotation(Vector3::Zero)
		, mScale(Vector3::One)
		, mFoward(Vector3::Forward)
		, mRight(Vector3::Right)
		, mUp(Vector3::Up)
	    , useTextureRatio(false)
	{}

	Transform::~Transform()
	{}

	void Transform::Initialize()
	{}

	void Transform::Update()
	{}

	void Transform::LateUpdate()
	{
		mWorld = Matrix::Identity;
		for(Collider2D* col : GetOwner()->GetComponents<Collider2D>())
		{
			if(col->GetColliderFunctionType() == eColliderFunctionType::TilePos)
			{
				col->SetCenter(Vector2(0.f, -mScale.y / 2.f));
				break;
			}
		}
		Matrix scale = Matrix::CreateScale(mScale);

		Matrix rotation;
		//if (mParent)
		//{
		//	rotation = Matrix::CreateRotationX(mParent->mRotation.x);
		//	rotation *= Matrix::CreateRotationY(mParent->mRotation.y);
		//	rotation *= Matrix::CreateRotationZ(mParent->mRotation.z);
		//}
		//else
		//{
		//	rotation = Matrix::CreateRotationX(mRotation.x);
		//	rotation *= Matrix::CreateRotationY(mRotation.y);
		//	rotation *= Matrix::CreateRotationZ(mRotation.z);
		//}

		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);

		Matrix position;
		position.Translation(mPosition);

		mWorld = scale * rotation * position;

		mUp = Vector3::TransformNormal(Vector3::Up, rotation);
		mFoward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);

		if (mParent) { mWorld *= mParent->mWorld; }
	}

	void Transform::Render()
	{

	}

	void Transform::BindConstantBuffer()
	{
		renderer::TransformCB trCB = {};
		trCB.mWorld = mWorld;
		trCB.View = Camera::GetViewMatrix();
		trCB.Projection = Camera::GetProjectionMatrix();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Transform];
		
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::HS);
		cb->Bind(eShaderStage::DS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);
	}

    Vector3 Transform::ProjectionPosition()
    {
		Matrix proj = Matrix::Identity;
		Matrix view = Matrix::Identity;

		if (nullptr == GetOwner()->GetCamera())
		{
			proj = Camera::GetProjectionMatrix();
			view = Camera::GetViewMatrix();
		}
		else
		{
			proj = GetOwner()->GetCamera()->GetPrivateProjectionMatrix();
			view = GetOwner()->GetCamera()->GetPrivateViewMatrix();
		}
		Viewport viewport = Application::GetViewPort();
		return viewport.Project(mPosition, proj, view, Matrix::Identity);
    }
	Vector3 Transform::TransPositionOtherCamera(Camera* camera)
	{
		Matrix proj = camera->GetPrivateProjectionMatrix();
		Matrix view = camera->GetPrivateViewMatrix();
		//Matrix world = camera->World();

		//proj = GetOwner()->GetCamera()->GetPrivateProjectionMatrix();
		//view = GetOwner()->GetCamera()->GetPrivateViewMatrix();

		//XMMATRIX ViewProj = view * proj;
		//XMMATRIX WorldViewProj = mWorld * view * proj;
		//XMVECTOR clipSpacePosition = XMVector4Transform(XMVectorSet(mPosition.x, mPosition.y, mPosition.z, 1.0f), WorldViewProj);

		//Vector3 worldPos = mPosition;


		//XMVECTOR projected = XMVector3Project(XMLoadFloat3(&worldPos)
		//	, 0, 0, RESOL_WID, RESOL_HEI, -10.f, 1.0f
		//	, view, proj, Matrix::Identity);

		//float screenX = ((clipSpacePosition.m128_f32[0] / clipSpacePosition.m128_f32[3]) + 1.0f) * 0.5f * RESOL_WID;
		//float screenY = ((-clipSpacePosition.m128_f32[1] / clipSpacePosition.m128_f32[3]) + 1.0f) * 0.5f * RESOL_HEI;

		Viewport viewport = Application::GetViewPort();

		POINT point;
		point.x = mPosition.x;
		point.y = mPosition.y;

		ScreenToClient(application.GetHwnd(), &point);
		Vector3 p =viewport.Unproject(Vector3(point.x, point.y, mPosition.z), proj, view, Matrix::Identity);
		p.z = mPosition.z;
		return p;
	}
    Vector3 Transform::ProjectionCetnerPosition(Vector2 fontSize)
    {
		Vector3 centerPos = ProjectionPosition();
		centerPos.y -= fontSize.y / 2.f;
		centerPos.x -= fontSize.x / 2.f;

		return centerPos;
    }
}
