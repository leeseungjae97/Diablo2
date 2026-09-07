#pragma once
#include "mResource.h"
namespace m
{
	class Resources
	{
	public:
		template <typename T>
		static std::shared_ptr<T> Find(const std::wstring& key)
		{
			// ���ҽ��ʿ��� ������ Ž��
			std::map<std::wstring, std::shared_ptr<Resource>>::iterator iter = mResources.find(key);
			if (iter != mResources.end())
			{
				iter->second->SetKey(key);
				return std::dynamic_pointer_cast<T>(iter->second);
			}

			return nullptr;
		};
		static std::filesystem::path GetExecutableDirectory()
		{
			wchar_t modulePath[MAX_PATH] = {};
			GetModuleFileNameW(nullptr, modulePath, MAX_PATH);
			return std::filesystem::path(modulePath).parent_path();
		}

		static std::wstring ResolvePath(const std::wstring& path)
		{
			std::filesystem::path requested(path);
			if (std::filesystem::exists(requested))
				return requested.wstring();

			std::filesystem::path current = GetExecutableDirectory();
			std::filesystem::path relative = requested.lexically_normal();
			std::filesystem::path tail;
			bool foundResources = false;
			for (const std::filesystem::path& part : relative)
			{
				if (foundResources)
				{
					tail /= part;
				}
				else if (part == L"Resources")
				{
					foundResources = true;
				}
			}

			for (int i = 0; i < 8 && !current.empty(); ++i)
			{
				std::filesystem::path resources = current / L"Resources";
				std::filesystem::path candidate = foundResources ? resources / tail : current / requested;
				if (std::filesystem::exists(candidate))
					return candidate.wstring();

				current = current.parent_path();
			}

			return path;
		}

		static void LogLoadFailure(const std::wstring& key, const std::wstring& path, const std::wstring& resolvedPath)
		{
			std::wstring message = L"Resources::Load failed\r\nkey: " + key
				+ L"\r\npath: " + path
				+ L"\r\nresolved: " + resolvedPath
				+ L"\r\nexe dir: " + GetExecutableDirectory().wstring() + L"\r\n\r\n";

			OutputDebugStringW(message.c_str());

			std::filesystem::path logPath = GetExecutableDirectory() / L"resource_load_error.log";
			FILE* file = nullptr;
			if (_wfopen_s(&file, logPath.c_str(), L"a, ccs=UTF-8") == 0 && file != nullptr)
			{
				fputws(message.c_str(), file);
				fclose(file);
			}
		}

		template <typename T>
		static std::shared_ptr<T> Load(const std::wstring& key, const std::wstring& path)
		{
			std::shared_ptr<T> resource = Resources::Find<T>(key);
			if (nullptr != resource)
			{
				return resource;
			}
			// ���ҽ��� ���ٸ�
			resource = std::make_shared<T>();
			std::wstring resolvedPath = ResolvePath(path);
			if (FAILED(resource->Load(resolvedPath)))
			{
				LogLoadFailure(key, path, resolvedPath);
				assert(false);
				return nullptr;
			}
			resource->SetKey(key);
			resource->SetPath(resolvedPath);

			mResources.insert(std::make_pair(key, resource));

			return std::dynamic_pointer_cast<T>(resource);
		};
		template <typename T>
		static void Insert(const std::wstring& key, std::shared_ptr<T> resource)
		{
			mResources.insert(std::make_pair(key, resource));
		}
	private:
		static std::map<std::wstring, std::shared_ptr<Resource>> mResources;
	};
}
