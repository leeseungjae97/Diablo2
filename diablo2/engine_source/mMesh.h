#pragma once
#include "mResource.h"
#include "mGraphicDevice_DX11.h"

namespace m
{
	class Mesh :
		public Resource
	{
	public:
		Mesh();
		~Mesh();

		virtual HRESULT Load(const std::wstring& path) override;

		bool CreateVertexBuffer(void* data, UINT Count);
		bool CreateIndexBuffer(void* data, UINT Count);

		void BindBuffer(); //Buffer ���������ο� �����ش�.
		void Render();
		void RenderInstanced(UINT instanceCount);

		void SetVertexes(std::vector<Vertex>& _v) { vertexes = _v; }
		std::vector<Vertex>& GetVertexes() { return vertexes; }

		UINT GetIndexCount() { return mIndexCount; }
		

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> mIndexBuffer;

		D3D11_BUFFER_DESC mVBDesc;
		D3D11_BUFFER_DESC mIBDesc;

		UINT mIndexCount;
		std::vector<Vertex> vertexes;
	};
}