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
		};
		enum eBattleState
		{
			Idle,
			Attack,
			Cast,
			Run,
			GetHit,
			Walk,
			TownWalk,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		eState GetState() { return mState; }
		void SetState(eState state) { mState = state; }

		eBattleState GetBattleState() { return mBattleState; }
		void SetBattleState(eBattleState state) { mBattleState = state; }

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
	private:
		eState mState;
		eBattleState mBattleState;
		std::vector<Component*> mComponents;
		std::vector<Script*> mScripts;

		Camera* mCamera;
		bool bHover;
	};
}


