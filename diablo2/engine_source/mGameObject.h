#pragma once
#include "mEntity.h"
#include "mComponent.h"
#include "mScript.h"
#include "mCamera.h"

namespace m
{
	class GameObject :
		public Entity
	{
	public:
		enum eState
		{
			RenderUpdate,
			NoRenderUpdate,
			RenderNoUpdate,
			NoRenderNoUpdate,
			Delete,
			DelayDelete,
		};
		enum eBattleState
		{
			Idle,
			Attack,
			Cast,
			Run,
			Hit,
			Walk,
			TownWalk,
			ToDead,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

		void Release();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		
		eState GetState() { return mState; }
		void SetState(eState state) { mState = state; }

		eBattleState GetBattleState() { return mBattleState; }
		void SetBattleState(eBattleState state) { mBattleState = state; }

		void SetLayerType(eLayerType type) { mLayerType = type; }
		eLayerType GetLayerType() { return mLayerType; }

		template <typename T>
		T* GetComponent()
		{
			T* component;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					return component;
			}
			for (Script* script : mScripts)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					return component;
			}

			return nullptr;
		}
		template <typename T, typename... Types>
		T* AddComponent(Types... args)
		{
			T* comp = new T(args...);

			Component* buff
				= dynamic_cast<Component*>(comp);
			Script* script
				= dynamic_cast<Script*>(buff);

			if (buff == nullptr)
				return nullptr;

			if (script == nullptr)
				mComponents.push_back(buff);
			else
				mScripts.push_back(script);

			comp->SetOwner(this);
			comp->Initialize();

			return comp;
		}
		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();

			Component* buff
				= dynamic_cast<Component*>(comp);
			Script* script
				= dynamic_cast<Script*>(buff);

			if (buff == nullptr)
				return nullptr;

			if (script == nullptr)
				mComponents.push_back(buff);
			else
				mScripts.push_back(script);

			comp->SetOwner(this);
			comp->Initialize();

			return comp;
		}
		template <typename T>
		const std::vector<T*> GetComponents()
		{
			std::vector<T*> comps;

			T* component;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					comps.push_back(component);
			}

			for (Script* script : mScripts)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					comps.push_back(component);
			}

			return comps;
		}
		void SetCamera(Camera* camera) { mCamera = camera; }
		Camera* GetCamera() { return mCamera; }

		void MousePosHoverGameObject();
		bool GetHover() { return bHover; }
		std::vector<Script*>& GetScripts() { return mScripts; }
		std::vector<Component*> GetComponents() { return mComponents; }

		bool GetCulled() { return bCulled; }
		void SetCulled(bool cull) { bCulled = cull; }

		bool IsRhombus() { return bRhombus; }
		void SetIsRhombus(bool r) { bRhombus = r; }

		const UINT GetGameObjectId() { return iGameObjectId; }

		void CreateAnimators(
			int count
			, Animator* animator
			, const std::wstring& name
			, std::shared_ptr<graphics::Texture> atlas
			, Vector2 leftTop
			, Vector2 size
			, UINT columnLength
			, Vector2 offset = Vector2::Zero
			, float duration = 0.0f
			, float alpha = 1.0f
		);
		//void CreateAnimators(
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
		//);
		//void PlayRandPosAnimators(const std::wstring playName, bool loop, Vector2 size);
		//void PlayAnimators(std::vector<std::wstring>, bool loop, std::vector<Vector3> pos, int loopStartIndex = 0, int loopEndIndex = 0, int loopCount = 0);
		void PlayAnimators(const std::wstring playName, bool loop, Vector2 size, bool useDirect, Collider2D* col);
		void ReleaseAnimators();

		bool SoundPlay() { return bSoundPlay; }
		void SetSoundPlay(bool play) { bSoundPlay = play; }
	private:
		eState mState;
		eLayerType mLayerType;
		eBattleState mBattleState;
		std::vector<Component*> mComponents;
		std::vector<Script*> mScripts;

		Camera* mCamera;
		bool bRhombus;
		bool bHover;

		bool bCulled;
		bool bTileCulled;

		bool bSoundPlay;

		UINT iGameObjectId;
		static UINT GameObjectIdDispender;
		Vector2 direct1[4] = {
			Vector2(-1, -1)
		    ,Vector2(-1, 1)
		    ,Vector2(1, 1)
		    ,Vector2(1, -1)
		};

		std::vector<GameObject*> subobjects;
	};
}


