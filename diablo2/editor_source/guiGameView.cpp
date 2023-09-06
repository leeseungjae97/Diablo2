#include "guiGameView.h"

#include "../engine_source/mApplication.h"
#include "../engine_source/mTexture.h"
#include "../engine_source/mResources.h"
#include "../engine_source/mGraphicDevice_Dx11.h"
#include "../engine_source/mRenderer.h"

namespace gui
{
	GameView::GameView()
	{
	}
	GameView::~GameView()
	{
	}
	void GameView::FixedUpdate()
	{
	}
	void GameView::Update()
	{
		std::shared_ptr<m::graphics::Texture> renderTarget
			= m::Resources::Find<m::graphics::Texture>(L"RenderTarget");

		std::shared_ptr<m::graphics::Texture> gameTarget
			= std::make_shared<m::graphics::Texture>();

		D3D11_VIEWPORT viewPort = m::graphics::GetDevice()->GetD3D11Viewport();
		gameTarget->Create(viewPort.Width, viewPort.Height
			, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE);

		ID3D11ShaderResourceView* srv = nullptr;
		m::graphics::GetDevice()->BindShaderResource(eShaderStage::PS, 61, &srv);

		m::graphics::GetDevice()->CopyResource(gameTarget->GetTexture().Get()
			, renderTarget->GetTexture().Get());

		gameTarget->BindShaderResource(eShaderStage::PS, 61);

		ImGuiIO io = ImGui::GetIO();
		ImVec2 pannelSize = ImGui::GetWindowSize();
		ImVec4 tintColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ImVec2 scene_size = ImVec2(io.DisplaySize.x, io.DisplaySize.y);

		ImGui::Image(gameTarget->GetSRV().Get(), pannelSize
			, ImVec2(0, 0), ImVec2(1, 1), tintColor, ImVec4(0, 0, 0, 0));

	}
	void GameView::LateUpdate()
	{
	}
	void GameView::Render()
	{
		Widget::Render();
	}
}
