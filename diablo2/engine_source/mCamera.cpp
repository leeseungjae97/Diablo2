#include "mCamera.h"
#include "mTransform.h"
#include "mGameObject.h"
#include "mApplication.h"

extern m::Application application;
namespace m
{
	Matrix Camera::mView = Matrix::Identity;
	Matrix Camera::mProjection = Matrix::Identity;
	Camera::Camera()
		: Component(eComponentType::Camera)
		, mType(eProjectionType::Orthorgaphic)
		, mAspectRatio(1.0f)
		, mNear(1.0f)
		, mFar(1000.f)
		, mSize(1.0f)
	{}
	Camera::~Camera()
	{}
	void Camera::Initialize()
	{}
	void Camera::Update()
	{}
	void Camera::LateUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix(mType);
	}
	void Camera::Render()
	{}
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
		mAspectRatio = width / height;

		if (type == eProjectionType::Orthorgaphic)
		{
			//float orthographicRatio = mSize;
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
}