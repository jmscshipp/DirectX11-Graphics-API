#include "GraphicObject_Texture.h"
#include "ShaderTexture.h"
#include "Model.h"
#include "Texture.h"

GraphicObject_Texture::GraphicObject_Texture(ShaderTexture* shader, Model* model)
{
	GraphicObject_Base::SetModel(model);
	pShader = shader;
	world = Matrix(IDENTITY);

	// set mesh list to all empty
	meshCount = model->GetMeshCount();
	textures = new Texture*[meshCount];
	for (int i = 0; i < meshCount; i++)
		textures[i] = nullptr;
}

GraphicObject_Texture::~GraphicObject_Texture()
{
	delete[] textures;
}

// set all textures to same
void GraphicObject_Texture::SetTexture(Texture* tex)
{
	for (int i = 0; i < meshCount; i++)
		textures[i] = tex;
}
// set specific tex
void GraphicObject_Texture::SetTexture(Texture* tex, int meshIndex)
{
	textures[meshIndex] = tex;
}

void GraphicObject_Texture::SetWorld(const Matrix& worldMat)
{
	world = worldMat;
}

void GraphicObject_Texture::Render()
{
	pShader->SendWorld(world);
	pModel->SetToContext(pShader->GetContext());

	for (int i = 0; i < meshCount; i++)
	{
		pShader->SetTextureResourceAndSampler(textures[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}