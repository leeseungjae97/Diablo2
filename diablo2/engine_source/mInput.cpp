#include "mInput.h"
#include "mApplication.h"

extern m::Application application;

namespace m
{
	int ASCII[(UINT)eKeyCode::END] =
	{
		'1', '2', '3', '4', '5', '6', '7', '8', '9',

		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',

		VK_UP, VK_DOWN, VK_LEFT ,VK_RIGHT, VK_SPACE,
		VK_LBUTTON, VK_RBUTTON, VK_ESCAPE, VK_MENU,
		VK_BACK, VK_SHIFT
	};

	std::vector<Input::Key> Input::mKeys;
	Vector2 Input::mMousePos = Vector2::Zero;
	bool Input::bCallDownOne = false;
	bool Input::bCallUpOne = false;
	bool Input::bCallOne = false;

	void Input::Initialize()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
		{
			Key keyInfo;
			keyInfo.key = (eKeyCode)i;
			keyInfo.state = eKeyState::None;
			keyInfo.bPressed = false;

			mKeys.push_back(keyInfo);
		}
	}

	void Input::Update()
	{

		if (GetFocus())
		{

			for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
			{
				if (GetAsyncKeyState(ASCII[i]) & 0x8000)
				{
					// 이전 프레임에도 눌려 있었다
					if (mKeys[i].bPressed)
						mKeys[i].state = eKeyState::Pressed;
					else
						mKeys[i].state = eKeyState::Down;

					mKeys[i].bPressed = true;
				}
				else // 현재 프레임에 키가 눌려있지 않다.
				{
					// 이전 프레임에 내키가 눌려있엇다.
					if (mKeys[i].bPressed)
						mKeys[i].state = eKeyState::Up;
					else
						mKeys[i].state = eKeyState::None;

					mKeys[i].bPressed = false;
				}
			}

			POINT mousePos = {};
			GetCursorPos(&mousePos);

			ScreenToClient(application.GetHwnd(), &mousePos);
			mMousePos.x = mousePos.x;
			mMousePos.y = mousePos.y;
		}
		else
		{
			SetFocus(NULL);
			for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
			{
				if (eKeyState::Down == mKeys[i].state
					|| eKeyState::Pressed == mKeys[i].state)
				{
					mKeys[i].state = eKeyState::Up;
				}
				else if (eKeyState::Up == mKeys[i].state)
				{
					mKeys[i].state = eKeyState::None;
				}

				mKeys[i].bPressed = false;
			}
		}
	}

	void Input::Render(HDC hdc)
	{

	}

    int Input::GetInputKey()
    {
		for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
		{
			if (eKeyState::Down == mKeys[i].state)
			{
				if (ASCII[i] == VK_UP
					|| ASCII[i] == VK_DOWN
					|| ASCII[i] == VK_LEFT
					|| ASCII[i] == VK_RIGHT
					|| ASCII[i] == VK_SPACE
					|| ASCII[i] == VK_LBUTTON
					|| ASCII[i] == VK_RBUTTON
					|| ASCII[i] == VK_ESCAPE
					|| ASCII[i] == VK_SHIFT
					|| ASCII[i] == VK_MENU)
					continue;

				if (eKeyState::Down == mKeys[(int)eKeyCode::SHIFT].state
					|| eKeyState::Pressed == mKeys[(int)eKeyCode::SHIFT].state)
				{
					return ASCII[i];
				}

				if(ASCII[i] == VK_BACK)
					return ASCII[i];

				return ASCII[i] + 32;
			}
		}
		return -1;
    }
}
