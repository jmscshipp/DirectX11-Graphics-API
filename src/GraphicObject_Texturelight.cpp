#include "GraphicObject_TextureLight.h"
#include "TextureLight.h"
#include "Model.h"

GraphicObject_TextureLight::GraphicObject_TextureLight(TextureLight* shader, Model* model)
{
	GraphicObject_Base::SetModel(model);
	pShader = shader;
	world = Matrix(IDENTITY);

	meshCount = model->GetMeshCount();
	// set up textures
	textures = new Texture * [meshCount];
	for (int i = 0; i < meshCount; i++)
		textures[i] = nullptr;
	// set up mats
	materials = new Material[meshCount];
}

GraphicObject_TextureLight::~GraphicObject_TextureLight()
{
	delete[] textures;
	delete[] materials;
}

// set all textures to same
void GraphicObject_TextureLight::SetTexture(Texture* tex)
{
	for (int i = 0; i < meshCount; i++)
		textures[i] = tex;
}
// set specific tex
void GraphicObject_TextureLight::SetTexture(Texture* tex, int meshIndex)
{
	textures[meshIndex] = tex;
}

// setting all materials
void GraphicObject_TextureLight::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp)
{
	for (int i = 0; i < meshCount; i++)
	{
		materials[i].ambient = amb;
		materials[i].diffuse = dif;
		materials[i].specular = sp;
	}
}
// setting specific mat
void GraphicObject_TextureLight::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp, int num)
{
	materials[num].ambient = amb;
	materials[num].diffuse = dif;
	materials[num].specular = sp;
}

void GraphicObject_TextureLight::SetWorld(const Matrix& worldMat)
{
	world = worldMat;
}

void GraphicObject_TextureLight::Render()
{
	pModel->SetToContext(pShader->GetContext());

	for (int i = 0; i < meshCount; i++)
	{
		pShader->SetTextureResourceAndSampler(textures[i]);
		pShader->SendWorldAndMaterial(world, materials[i].ambient, materials[i].diffuse, materials[i].specular);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}