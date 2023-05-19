#pragma once
#include "mEntity.h"

namespace m {
	using namespace enums;

	class Resource : public Entity {
	public:
		Resource(eResourceType type);
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;
		//virtual HRESULT Create(const std::wstring& path);


		const std::wstring& GetKey() { return mKey; }
		const std::wstring& GetPath() { return mPath; }
		eResourceType GetType() { return mType; }

		void SetKey(const std::wstring& key) { mKey = key; }
		void SetPath(const std::wstring& path) { mPath = path; }

	private:
		const eResourceType mType;
		std::wstring mKey;
		std::wstring mPath;
	};
}