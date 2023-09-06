#pragma once
//#define RESOL_WID 1600.f
//#define RESOL_HEI 900.f

#define RESOL_WID 1600.f
#define RESOL_HEI 900.f

#define RESOL_H_WID RESOL_WID / 2.f
#define RESOL_H_HEI RESOL_HEI / 2.f

#define RESOURCE_FIND(type, name) Resources::Find<type>(name)
#define RESOURCE_LOAD(type, name, path) Resources::Load<type>(name, path)
#define GET_COMP(object, type) object->GetComponent<type>()
#define GET_COMPS(object, type) object->GetComponents<type>()
#define GET_TRANS(object) object->GetComponent<Transform>()
#define GET_MESHR(object) object->GetComponent<MeshRenderer>()
#define ADD_COMP(object, type) object->AddComponent<type>()
#define DELETE_COMP(object, type) std::vector<type> comps = object->GetComponents<type>();\
								for(T* comp : comps)\
								{\
									std::erase(comps, comp);\
								}\						

#define SHARED_TEX std::shared_ptr<Texture>
#define SHARED_MAT std::shared_ptr<Material>

#define GET_TEX(object, p) p = GET_MESHR(object)->GetMaterial()->GetTexture()
#define MAKE_GET_TEX(object, p) SHARED_TEX p; \
					GET_TEX(object, p);
						  

#define SET_SCALE_TEX_SIZE_WITH_RAT(object, tex, z) GET_TRANS(object)->SetScale(Vector3(tex->GetMetaDataWidth() * Texture::GetWidRatio(), tex->GetMetaDataHeight() * Texture::GetHeiRatio(), z))
#define SET_SCALE_TEX_SIZE(object, tex, z) GET_TRANS(object)->SetScale(Vector3(tex->GetMetaDataWidth(), tex->GetMetaDataHeight(), z))
#define SET_SCALE_XYZ(object, width, height, z) GET_TRANS(object)->SetScale(Vector3(width, height, z))
#define SET_SCALE_XYZ_WITH_RAT(object, width, height, z) GET_TRANS(object)->SetScale(Vector3(width * Texture::GetWidRatio(), height * Texture::GetHeiRatio(), z))
#define SET_SCALE_VEC(object, vector) GET_TRANS(object)->SetScale(vector)
#define SET_SCALE_VEC_WTTH_RAT(object, vector) GET_TRANS(object)->SetScale(Vector3(vector.x * Texture::GetWidRatio(), vector.y * Texture::GetHeiRatio(), vector.z))
#define SET_SCALE_FULL(object, z) GET_TRANS(object)->SetScale(Vector3(RESOL_WID, RESOL_HEI, z));
#define SET_SCALE_WIDTH_TH(object, width, tex, z) GET_TRANS(object)->SetScale(Vector3(width, tex->GetMetaDataHeight() * Texture::GetHeiRatio(), z))
#define SET_SCALE_HEIGHT_TW(object), height, tex, z) GET_TRANS(object)->SetScale(Vector3(tex->GetMetaDataWidth() * Texture::GetWidRatio(), height, z))

#define SET_POS_XYZ(object, x, y, z) GET_TRANS(object)->SetPosition(Vector3(x,y,z))
#define SET_POS_VEC(object, vector) GET_TRANS(object)->SetPosition(vector)

#define SET_ROTATION_XYZ(object, x, y, z) GET_TRANS(object)->SetRotation(Vector3(x,y,z))
#define SET_ROTATION_VEC(object, vector) GET_TRANS(object)->SetRotation(vector)

#define GET_POS(object) GET_TRANS(object)->GetPosition()
#define GET_SCALE(object) GET_TRANS(object)->GetScale()

#define MAKE_POS(p, object) Vector3 p; \
					p = GET_POS(object);

#define SET_MESH(object, meshName) GET_MESHR(object)->SetMesh(RESOURCE_FIND(Mesh, meshName))
#define SET_MATERIAL(object, materialName) GET_MESHR(object)->SetMaterial(RESOURCE_FIND(Material, materialName))

#define SET_MATERIAL_D(object, material) GET_MESHR(object)->SetMaterial(material)

#define SET_MAIN_CAMERA(object) object->SetCamera(GetSceneMainCamera())

#define MAKE_MATERIAL_F(shader, texName, materialName)		   { \
																SHARED_MAT mat = std::make_shared<Material>(); \
																mat->SetShader(shader); \
																mat->SetTexture(RESOURCE_FIND(Texture, texName)); \
																Resources::Insert(materialName, mat); \
															}

#define MAKE_MATERIAL(shader, texName, texPath, materialName) { \
																SHARED_MAT mat = std::make_shared<Material>(); \
																mat->SetShader(shader); \
																mat->SetTexture(Resources::Load<Texture>(texName, texPath)); \
																Resources::Insert(materialName, mat); \
															  }
#define MAKE_MATERIAL_T(shader, texName, texPath, materialName) { \
																SHARED_MAT mat = std::make_shared<Material>(); \
																mat->SetShader(shader); \
																mat->SetRenderingMode(eRenderingMode::Transparent);\
																mat->SetTexture(Resources::Load<Texture>(texName, texPath)); \
																Resources::Insert(materialName, mat); \
															  }

#define MAKE_MATERIAL_PATH(shader, texName, texPath, texWidth, texHeight, length, materialName) { \
																SHARED_MAT mat = std::make_shared<Material>(); \
																mat->SetShader(shader); \
																SHARED_TEX tex = std::make_shared<Texture>();\
																tex->CreateTex(texWidth,texHeight, length, texPath);\
																Resources::Insert(texName, tex);\
																mat->SetTexture(tex); \
																mat->SetRenderingMode(eRenderingMode::Transparent);\
																Resources::Insert(materialName, mat); \
																}

#define MAKE_MATERIAL_COMPUT_TEST(shader, texName, materialName) { \
																SHARED_MAT mat = std::make_shared<Material>(); \
																mat->SetShader(shader); \
																mat->SetTexture(RESOURCE_FIND(Texture, texName)); \
																Resources::Insert(materialName, mat); \
															  }

#define MAKE_VEC2_F_VEC3(vector2, vector3) Vector2 vector2; \
										  vector2 = Vector2(vector3.x, vector3.y);
#define GET_VEC2_F_VEC3(vector2, vector3) vector2 = Vector2(vector3.x, vector3.y);
#define GET_VEC2_F_VEC3_D(vector3) Vector2(vector3.x, vector3.y)

#define MAKE_SKILL(skillType, skill, vector3Pos, fireLayerType) switch (skillFunctionTypes[(int)skillType])\
								{\
								case m::eSkillFunctionType::Straight:\
								{\
									skill = new SkillStraight(skillType, vector3Pos, skillSpeed[(int)skillType]);\
									skill->SetCamera(GetOwner()->GetCamera());\
									skill->SkillFire();\
									SceneManager::GetActiveScene()->AddGameObject(fireLayerType, skill);\
								}\
									break;\
								case m::eSkillFunctionType::Fall:\
								{\
									skill = new SkillFall(skillType, vector3Pos);\
									skill->SetCamera(GetOwner()->GetCamera());\
									skill->SkillFire();\
									SceneManager::GetActiveScene()->AddGameObject(fireLayerType, skill);\
								}\
									break;\
								case m::eSkillFunctionType::MutiFall:\
								{\
									Vector3 unprojMousePos = MouseManager::UnprojectionMousePos(GET_POS(GetOwner()).z, GetOwner()->GetCamera());\
									unprojMousePos.y += 300.f;\
									unprojMousePos.z = GET_POS(GetOwner()).z;\
									skill = new SkillMultiFire(unprojMousePos, skillType, 20, SkillMultiFire::eFireType::Random, fireLayerType, Vector2(200.f, 50.f));\
									skill->SetCamera(GetOwner()->GetCamera());\
									skill->SkillFire();\
									SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, skill);\
								}\
									break;\
								case m::eSkillFunctionType::MultiStraight:\
								{\
									skill = new SkillMultiFire(GET_POS(GetOwner()), skillType, 20, SkillMultiFire::eFireType::Linear, fireLayerType);\
									skill->SetCamera(GetOwner()->GetCamera());\
									skill->SkillFire();\
									SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, skill);\
								}\
									break;\
								case m::eSkillFunctionType::Orb:\
								{\
									skill = new SkillOrb(skillType, GET_POS(GetOwner()), 300.f);\
									skill->SetCamera(GetOwner()->GetCamera());\
									skill->SkillFire();\
									SceneManager::GetActiveScene()->AddGameObject(eLayerType::PlayerSkill, skill);\
								}\
									break;\
								case m::eSkillFunctionType::None:\
									break;\
								case m::eSkillFunctionType::END:\
									break;\
								default:\
								{\
									skill = new Skill(skillType, vector3Pos);\
									skill->SetCamera(GetOwner()->GetCamera());\
									skill->SkillFire();\
									SceneManager::GetActiveScene()->AddGameObject(fireLayerType, skill);\
								}\
									break;\
								}\

#define WSTRING_SUBSTR(srcStr, token, subStr) std::wstring subStr = L"";\
									   int tokenIndex = 0;\
									   for(int i = 0; i < srcStr.length(); ++i) \
									   {\
											if(token == srcStr[i]) \
											{\
												tokenIndex = i;\
												break;\
											}\
									   }\
									   subStr = srcStr.substr(0, tokenIndex + 1);