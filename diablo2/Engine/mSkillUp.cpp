#include "mSkillUp.h"

#include "..\engine_source\mMeshRenderer.h"
#include "..\engine_source\mTransform.h"
#include "..\engine_source\mSceneManager.h"
#include "mButton.h"


namespace m
{
	SkillUp::SkillUp(Camera* camera)
		: coldBtn(nullptr)
		, fireBtn(nullptr)
		, lightBtn(nullptr)
	{
		SetCamera(camera);
		Transform* tr = GetComponent<Transform>();

		tr->SetPosition(Vector3(400.f * Texture::GetWidRatio() / 2.f
			, 450.f - 555.f * Texture::GetHeiRatio() / 2.f, -1.f));
		tr->SetScale(Vector3(400.f * Texture::GetWidRatio()
			, 555.f * Texture::GetHeiRatio(), 0.f));

		MeshRenderer* mr = GetComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"skillPanelCold"));

		skillP1 = Resources::Find<Material>(L"skillPanelCold");
		skillP2 = Resources::Find<Material>(L"skillPanelLight");
		skillP3 = Resources::Find<Material>(L"skillPanelFire");

		Scene* curScene = SceneManager::GetActiveScene();
		curScene->AddGameObject(eLayerType::UI, this);

		coldBtn = new Button();
		coldBtn->SetCamera(GetCamera());
		// x 230 , y 170
		coldBtn->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		coldBtn->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"noneRect"));
		coldBtn->GetComponent<Transform>()->SetScale(Vector3(91.f * Texture::GetWidRatio(), 110.f * Texture::GetHeiRatio(), 0.f));
		coldBtn->GetComponent<Transform>()->SetPosition(Vector3(tr->GetPosition().x + 30.f * Texture::GetWidRatio() + 91.f * Texture::GetWidRatio() / 2.f, 450.f - 170.f - 110.f * Texture::GetHeiRatio(), -1.0f));
		//coldBtn->SetClickFunction([](SkillUp* ss) { ; });
		buttons.push_back(coldBtn);
		curScene->AddGameObject(eLayerType::UI, coldBtn);


		fireBtn = new Button();
		fireBtn->SetCamera(GetCamera());
		// x 230 , y 278
		fireBtn->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		fireBtn->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"noneRect"));
		fireBtn->GetComponent<Transform>()->SetScale(Vector3(91.f * Texture::GetWidRatio(), 110.f * Texture::GetHeiRatio(), 0.f));
		fireBtn->GetComponent<Transform>()->SetPosition(Vector3(tr->GetPosition().x + 30.f * Texture::GetWidRatio() + 91.f * Texture::GetWidRatio() / 2.f, 450.f - 170.f - 110.f * Texture::GetHeiRatio() * 2, -1.0f));
		buttons.push_back(fireBtn);
		curScene->AddGameObject(eLayerType::UI, fireBtn);

		lightBtn = new Button();
		lightBtn->SetCamera(GetCamera());
		// x 230 , y 385
		lightBtn->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		lightBtn->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"noneRect"));
		lightBtn->GetComponent<Transform>()->SetScale(Vector3(91.f * Texture::GetWidRatio(), 110.f * Texture::GetHeiRatio(), 0.f));
		lightBtn->GetComponent<Transform>()->SetPosition(Vector3(tr->GetPosition().x + 30.f * Texture::GetWidRatio() + 91.f * Texture::GetWidRatio() / 2.f, 450.f - 170.f - 110.f * Texture::GetHeiRatio() * 3, -1.0f));
		buttons.push_back(lightBtn);
		curScene->AddGameObject(eLayerType::UI, lightBtn);
	}
	SkillUp::~SkillUp()
	{}
	void SkillUp::Initialize()
	{
		UI::Initialize();
	}
	void SkillUp::Update()
	{
		UI::Update();
		if (buttons[0]->GetState() != GetState())
		{
			for (Button* btn : buttons)
			{
				btn->SetState(GetState());
			}
		}

		if (coldBtn->GetClick())
		{
			GetComponent<MeshRenderer>()->SetMaterial(skillP1);
		}
		if (fireBtn->GetClick())
		{
			GetComponent<MeshRenderer>()->SetMaterial(skillP2);
		}
		if (lightBtn->GetClick())
		{
			GetComponent<MeshRenderer>()->SetMaterial(skillP3);
		}

		
	}
	void SkillUp::LateUpdate()
	{
		UI::LateUpdate();
	}
	void SkillUp::Render()
	{
		UI::Render();
	}
}