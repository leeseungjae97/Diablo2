#include "mPlayerScript.h"

#include "../engine_source/mGameObject.h"
#include "../engine_source/mConstantBuffer.h"
#include "../engine_source/mRenderer.h"

namespace m
{
	PlayerScript::PlayerScript()
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{
	}
	void PlayerScript::Update()
	{
	}
	void PlayerScript::LateUpdate()
	{
	}
	void PlayerScript::Render()
	{
	}
	void PlayerScript::OnCollisionEnter(Collider2D* other)
	{
		//ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Vertex];
		//renderer::Vertex vertex;
		//vertex.pos = Vector3::One;
		//vertex.color = Vector4(0.f, 0.f, 1.f, 1.f);
		//vertex.uv = Vector2::One;

		//cb->SetData(&vertex);

		//cb->Bind(eShaderStage::PS);

		GetOwner()->GetComponent<Collider2D>()->SetRectColor(eColor::Red);
	}
	void PlayerScript::OnCollisionStay(Collider2D* other)
	{
	}
	void PlayerScript::OnCollisionExit(Collider2D* other)
	{
		GetOwner()->GetComponent<Collider2D>()->SetRectColor(eColor::Green);
	}
}