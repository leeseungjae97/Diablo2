#include "mParticleSystem.h"
#include "mTransform.h"
#include "mGameObject.h"
#include "mTime.h"
#include "mRenderer.h"
namespace m
{
	ParticleSystem::ParticleSystem()
		: mCount(0)
		, mStartSize(Vector4::One)
		, mEndSize(Vector4::One)
		, mStartColor(Vector4::Zero)
		, mEndColor(Vector4::Zero)
		, mLifeTime(0.0f)
		, mTime(0.0f)
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(mesh);

		std::shared_ptr<Material> material = Resources::Find<Material>(L"particleTex");
		SetMaterial(material);

		mCS = Resources::Find<ParticleComputeShader>(L"ParticleComputeShader");
		

		std::default_random_engine generator(std::time(nullptr));
		std::default_random_engine generator2(std::time(nullptr));
		std::uniform_real_distribution<float> distribution(-XM_2PI, XM_2PI);
		std::uniform_real_distribution<float> distribution2(-XM_2PI, XM_2PI);
		Particle particles[10] = {};
		for (size_t i = 0; i < 10; i++)
		{


			Vector4 pos = Vector4(0.f, 0.f, 1.f, 0.f);	
			//Vector4 pos = Vector4::Zero;	
			//pos.x += rand() % 2000;
			//pos.y += rand() % 1000;

			//int sign = rand() % 2;
			//if (sign == 0)
			//	pos.x *= -1.0f;
			//sign = rand() % 2;
			//if (sign == 0)
			//	pos.y *= -1.0f;

			particles[i].direction =
				Vector4(cosf((float)(rand() % (i + 1)) * (XM_2PI / (float)1000))
						, sinf((float)(rand() % (i + 1)) * (XM_2PI / 100.f))
						, 0.0f, 1.0f);
			//Vector4(cosf(distribution(generator))
			//		, sinf(distribution(generator2))
			//		, 0.0f, 1.0f);
				//Vector4(distribution(generator)
				//		, distribution(generator2)
				//		, 0.0f, 1.0f);
			particles[i].position = pos;
			particles[i].speed = 10.0f;
			particles[i].active = 0;
			particles[i].alpha = distribution(generator2);
			particles[i].alpha2 = distribution(generator2);
			particles[i].alpha3 = (float)(rand() % 1600);
			
		}

		mBuffer = new graphics::StructuredBuffer();
		mBuffer->Create(sizeof(Particle), 10, eViewType::UAV, particles);

		//mSharedBuffer = new graphics::StructuredBuffer();
		//mSharedBuffer->Create(sizeof(ParticleShared), 1, eViewType::UAV, particles, true);
		//mBuffer->SetData(particles, 10);
	}
	ParticleSystem::~ParticleSystem()
	{
		if (mBuffer)
			delete mBuffer;
		if (mSharedBuffer)
			delete mSharedBuffer;
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
		//float AliveTime = 0.05f;
		//mTime += Time::DeltaTime();

		//if (mTime > AliveTime)
		//{
		//	float f = (mTime / AliveTime);
		//	UINT AliveCount = (UINT)f;
		//	mTime = f - floor(f);

		//	ParticleShared shareData = {};
		//	shareData.sharedActiveCount = rand() % 5;
		//	mSharedBuffer->SetData(&shareData, 1);
		//}
		//else
		//{
		//	ParticleShared shareData = {};
		//	shareData.sharedActiveCount = 0;
		//	mSharedBuffer->SetData(&shareData, 1);
		//}

		mCS->SetParticleBuffer(mBuffer);
		//mCS->SetSharedBuffer(mSharedBuffer);
		//mCS->OnExcute();
	}
	void ParticleSystem::Render()
	{
		MeshRenderer::Render();
		GetOwner()->GetComponent<Transform>()->BindConstantBuffer();
		mBuffer->BindSRV(eShaderStage::VS, 14);
		mBuffer->BindSRV(eShaderStage::GS, 14);
		mBuffer->BindSRV(eShaderStage::PS, 14);
		//ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Particle];
		//Particle data = {};
		//data.alpha = 1.f;
		//cb->SetData(&data);

		//cb->Bind(eShaderStage::VS);
		//cb->Bind(eShaderStage::PS);

		GetMaterial()->Binds();
		GetMesh()->RenderInstanced(1000);

		mBuffer->Clear();
	}
}