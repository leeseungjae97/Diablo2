#include "mCameraScript.h"
#include "mTransform.h"
#include "mTime.h"
#include "mGameObject.h"
namespace m
{
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.x += 1.0f * Time::DeltaTime();
		tr->SetPosition(pos);
	}
}