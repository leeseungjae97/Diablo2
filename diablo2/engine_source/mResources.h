#pragma once
#include "mResource.h"
namespace m {
	class Resources {
	public:
		template <typename T>
		static T* Find(const wstring& key) {
			// 리소스맵에서 데이터 탐색
			map<wstring, Resource*>::iterator iter = mResources.find(key);
			if (iter != mResources.end())
				return dynamic_cast<T*>(iter->second);

			return nullptr;
		};
		template <typename T>
		static T* Load(const wstring& key, const wstring& path) {
			T* resource = Resources::Find<T>(key);
			if (nullptr != resource) {
				return resource;
			}
			// 리소스가 없다면
			resource = new T();
			if (FAILED(resource->Load(path))) {
				assert(false);
				return nullptr;
			}
			resource->SetKey(key);
			resource->SetPath(path);

			mResources.insert(make_pair(key, dynamic_cast<Resource*>(resource)));

			return dynamic_cast<T*>(resource);
		};
		static void Release() {
			for (auto pair : mResources) {
				if (nullptr == pair.second) continue;
				delete pair.second;
				pair.second = nullptr;
			}
		}
		template <typename T>
		static void Insert(const std::wstring& key, T* resource) {
			mResources.insert(make_pair(key, dynamic_cast<Resource*>(resource)));
		}
		//private:
		//	Resources() = delete;
		//	~Resources() = delete;
	private:
		static map<wstring, Resource*> mResources;
	};
}
