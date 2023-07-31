#pragma once
#include "_Engine.h"
#include "mMath.h"
#include "SystemDefine.h"

namespace m
{
	using namespace m::math;
	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,

		UP, DOWN, LEFT, RIGHT, SPACE,
		LBUTTON, RBUTTON,
		END,
	};

	enum class eKeyState
	{
		Down,
		Pressed,
		Up,
		None,
	};

	class Input
	{
	public:
		struct Key
		{
			eKeyCode key;
			eKeyState state;
			bool bPressed;
		};

		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		inline static eKeyState GetKeyState(eKeyCode keyCode)
		{
			return mKeys[(UINT)keyCode].state;
		};

		//GetKey()		키를 누르는 시간만큼 true를 반환
		//GetKeyDown()	키를 눌렀을 때, 딱 한번 true를 반환
		//GetKeyUp()	키를 누르다 땠을 때, 딱 한번 true를 반환

		static __forceinline bool GetKey(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Pressed;
		}

		static __forceinline bool GetKeyDown(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Down;
		}

		static __forceinline bool GetKeyUp(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Up;
		}
		static __forceinline bool GetKeyDownOne(eKeyCode keyCode)
		{
			bool syncClick = mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Down;
			mKeys[static_cast<UINT>(keyCode)].state = eKeyState::None;
			return syncClick;
		}
		static __forceinline bool GetKeyUpOne(eKeyCode keyCode)
		{
			bool syncClick = mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Up;
			mKeys[static_cast<UINT>(keyCode)].state = eKeyState::None;
			return syncClick;
		}
		static __forceinline bool GetKeyOne(eKeyCode keyCode)
		{
			bool syncClick = mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Pressed;
			mKeys[static_cast<UINT>(keyCode)].state = eKeyState::None;
			return syncClick;
		}

		//bool GetOneClick()
		//{
		//	bool syncClick = bOneClick;
		//	bOneClick = false;
		//	return syncClick;
		//}
		static __forceinline Vector2 GetMousePos() { return mMousePos; }

		static __forceinline Vector3 GetUnprojectionMousePos(float curDepth, Matrix projMat, Matrix view)
		{
			Viewport viewport = {
				0.f,
				0.f,
				RESOL_WID,
				RESOL_HEI,
				10.f,
				-1.f,
			};
			Vector3 mousePos3 = Vector3(mMousePos.x, mMousePos.y, curDepth);
			return viewport.Unproject(mousePos3, projMat, view, Matrix::Identity);
		}

	private:
		static std::vector<Key> mKeys;
		static Vector2 mMousePos;

	};
}
