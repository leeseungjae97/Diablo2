#include "mCameraScript.h"

#include "../engine_source/mTransform.h"
#include "../engine_source/mTime.h"
#include "../engine_source/mGameObject.h"
#include "../engine_source/mInput.h"

namespace m
{
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::W))
		{
			pos.z += 5.0f * Time::fDeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::S))
		{
			pos.z -= 5.0f * Time::fDeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 100.0f * Time::fDeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			pos.x += 100.0f * Time::fDeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::Q))
		{
			pos.y -= 100.0f * Time::fDeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::E))
		{
			pos.y += 100.0f * Time::fDeltaTime();
			tr->SetPosition(pos);
		}
	}
}