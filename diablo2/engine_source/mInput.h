#pragma once
#include "_Engine.h"
namespace m {

	enum class KEYCODE_TYPE {
		NUM_0, NUM_1, NUM_2, NUM_3, NUM_4,
		NUM_5, NUM_6, NUM_7, NUM_8, NUM_9,
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		ALT,
		CTRL,
		LSHIFT,
		SPACE,
		ENTER,
		ESC,
		LBTN,
		RBTN,
		END,
	};

	enum class KEY_STATE {
		DOWN,
		PRESSED,
		UP,
		CLICKED,
		NONE,
	};

	class Input {
	public:
		struct Key {
			KEYCODE_TYPE key;
			KEY_STATE state;
			bool bPressed;
		};

		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		inline static KEY_STATE GetKeyState(KEYCODE_TYPE keyCode) {
			return mKeys[(UINT)keyCode].state;
		};

		static Vector2 GetMousePos() { return mCurMousePos; }

	private:
		static vector<Key> mKeys;
		static Vector2 mCurMousePos;
	};
}