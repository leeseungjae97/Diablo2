#include "mParticleSystem.h"
#include "mTransform.h"
#include "mGameObject.h"
namespace m
{
	ParticleSystem::ParticleSystem()
		: mCount(0)
		, mStartSize(Vector4::One)
		, mEndSize(Vector4::One)
		, mStartColor(Vector4::Zero)
		, mEndColor(Vector4::Zero)
		, mLifeTime(0.0f)
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(mesh);

		std::shared_ptr<Material> material = Resources::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);

		mCS = Resources::Find<ParticleShader>(L"ParticleSystemShader");

		Particle particles[1000] = {};
		for (size_t i = 0; i < 1000; i++)
		{
			//Vector4 pos = Vector4(0.f, 0.f, 1.f, 0.f);	
			Vector4 pos = Vector4::Zero;	
			pos.x += rand() % 2000;
			pos.y += rand() % 1000;

			int sign = rand() % 2;
			if (sign == 0)
				pos.x *= -1.0f;
			sign = rand() % 2;
			if (sign == 0)
				pos.y *= -1.0f;

			particles[i].direction =
				Vector4(cosf((float)i * (XM_2PI / (float)1000))
						, sinf((float)i * (XM_2PI / 100.f))
						, 0.0f, 1.0f);

			particles[i].position = pos;
			particles[i].speed = 10.0f;
			particles[i].active = 1;
		}

		mBuffer = new graphics::StructedBuffer();
		mBuffer->Create(sizeof(Particle), 1000, eViewType::UAV, particles);
		//mBuffer->SetData(particles, 1000);
	}
	ParticleSystem::~ParticleSystem()
	{
	}
	void ParticleSystem::Initialize()
	{
		MeshRenderer::Initialize();
	}
	void ParticleSystem::Update()
	{
		MeshRenderer::Update();
	}
	void ParticleSystem::LateUpdate()
	{
		MeshRenderer::LateUpdate();
		mCS->SetParticleBuffer(mBuffer);
		mCS->OnExcute();
	}
	void ParticleSystem::Render()
	{
		MeshRenderer::Render();
		GetOwner()->GetComponent<Transform>()->BindConstantBuffer();
		mBuffer->BindSRV(eShaderStage::VS, 14);
		mBuffer->BindSRV(eShaderStage::GS, 14);
		mBuffer->BindSRV(eShaderStage::PS, 14);

		GetMaterial()->Binds();
		GetMesh()->RenderInstanced(1000);

		mBuffer->Clear();
	}
}