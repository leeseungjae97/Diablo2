#pragma once
#include "mResource.h"
namespace m {
	class Resources {
	public:
		template <typename T>
		static std::shared_ptr<T> Find(const wstring& key) {
			// 리소스맵에서 데이터 탐색
			map<wstring, std::shared_ptr<Resource>>::iterator iter = mResources.find(key);
			if (iter != mResources.end())
				return std::dynamic_pointer_cast<T>(iter->second);

			return nullptr;
		};
		template <typename T>
		static std::shared_ptr<T> Load(const wstring& key, const wstring& path) {
			std::shared_ptr<T> resource = Resources::Find<T>(key);
			if (nullptr != resource) {
				return resource;
			}
			// 리소스가 없다면
			resource = std::make_shared<T>();
			if (FAILED(resource->Load(path))) {
				assert(false);
				return nullptr;
			}
			resource->SetKey(key);
			resource->SetPath(path);

			mResources.insert(std::make_pair(key, resource));

			return std::dynamic_pointer_cast<T>(resource);
		};
		static void Release() {
			//for (auto pair : mResources) {
			//	if (nullptr == pair.second) continue;
			//	delete pair.second;
			//	pair.second = nullptr;
			//}
		}
		template <typename T>
		static void Insert(const std::wstring& key, std::shared_ptr<T> resource) {
			mResources.insert(std::make_pair(key, resource));
		}
		//private:
		//	Resources() = delete;
		//	~Resources() = delete;
	private:
		static map<wstring, std::shared_ptr<Resource>> mResources;
	};
}
