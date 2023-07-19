#pragma once
//#define RESOL_WID 1600.f
//#define RESOL_HEI 900.f

#define RESOL_WID 1600.f
#define RESOL_HEI 900.f

#define RESOL_H_WID RESOL_WID / 2.f
#define RESOL_H_HEI RESOL_HEI / 2.f

#define RESOURCE_FIND(type, name) Resources::Find<type>(name)
#define GET_COMP(object, p, type) p = object->GetComponent<type>()
#define GET_TRANS(object) object->GetComponent<Transform>()
#define GET_MESHR(object) object->GetComponent<MeshRenderer>()
#define ADD_COMP(object, type) object->AddComponent<type>()

#define SHARED_TEX std::shared_ptr<Texture>
#define SHARED_MAT std::shared_ptr<Material>

#define GET_TEX(object, p) p = GET_MESHR(object)->GetMaterial()->GetTexture()
#define MAKE_TEX(object, p) SHARED_TEX p; \
					GET_TEX(object, p);

#define SET_SCALE_TEX_SIZE_WITH_RAT(object, tex, z) GET_TRANS(object)->SetScale(Vector3(tex->GetWidth() * Texture::GetWidRatio(), tex->GetHeight() * Texture::GetHeiRatio(), z))
#define SET_SCALE_TEX_SIZE(object, tex, z) GET_TRANS(object)->SetScale(Vector3(tex->GetWidth(), tex->GetHeight(), z))
#define SET_SCALE_XYZ(object, width, height, z) GET_TRANS(object)->SetScale(Vector3(width, height, z))
#define SET_SCALE_VEC(object, vector) GET_TRANS(object)->SetScale(vector)
#define SET_SCALE_FULL(object, z) GET_TRANS(object)->SetScale(Vector3(RESOL_WID, RESOL_HEI, z));
#define SET_SCALE_WIDTH_TH(object, width, tex, z) GET_TRANS(object)->SetScale(Vector3(width, tex->GetHeight() * Texture::GetHeiRatio(), z))
#define SET_SCALE_HEIGHT_TW(object), height, tex, z) GET_TRANS(object)->SetScale(Vector3(tex->GetWidth() * Texture::GetWidRatio(), height, z))

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


#define SET_MAIN_CAMERA(object) object->SetCamera(GetSceneMainCamera())


#define MAKE_MATERIAL(shader, texName, texPath, materialName) { \
																SHARED_MAT mat = std::make_shared<Material>(); \
																mat->SetShader(shader); \
																mat->SetTexture(Resources::Load<Texture>(texName, texPath)); \
																Resources::Insert(materialName, mat); \
															  }

#define MAKE_VEC2_F_VEC3(vector2, vector3) Vector2 vector2; \
										  vector2 = Vector2(vector3.x, vector3.y);
#define GET_VEC2_F_VEC3(vector2, vector3) vector2 = Vector2(vector3.x, vector3.y);
#define GET_VEC2_F_VEC3_D(vector3) Vector2(vector3.x, vector3.y)