#pragma once
#include "_Engine.h"

namespace m {
	class Entity {
	public:
		Entity();
		virtual ~Entity();

		void SetName(const std::wstring& name) { mName = name; }
		std::wstring& GetName() { return mName; }

		void SetID(UINT64 id) { mColliderID = id; }
		UINT64 GetID() { return mColliderID; }

	private:
		std::wstring mName;
		UINT64 mColliderID;
	};
}

namespace gui
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void SetName(const std::string& name) { mName = name; }
		std::string& GetName() { return mName; }
		void SetID(UINT64 id) { mColliderID = id; }
		UINT64 GetID() { return mColliderID; }

	private:
		std::string mName;
		UINT64 mColliderID;
	};
}
