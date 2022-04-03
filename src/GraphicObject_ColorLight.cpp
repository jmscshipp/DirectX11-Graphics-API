#include "GraphicObject_ColorLight.h"
#include "ShaderColorLight.h"
#include "Model.h"

GraphicObject_ColorLight::GraphicObject_ColorLight(ShaderColorLight* shader, Model* model)
{
	GraphicObject_Base::SetModel(model);
	pShader = shader;
	world = Matrix(IDENTITY);
	meshCount = model->GetMeshCount();

	materials = new Material[meshCount];
}

GraphicObject_ColorLight::~GraphicObject_ColorLight()
{
	delete[] materials;
}

// setting all materials
void GraphicObject_ColorLight::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp)
{
	for (int i = 0; i < meshCount; i++) 
	{
		materials[i].ambient = amb;
		materials[i].diffuse = dif;
		materials[i].specular = sp;
	}
}
// setting specific mat
void GraphicObject_ColorLight::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp, int num)
{
	materials[num].ambient = amb;
	materials[num].diffuse = dif;
	materials[num].specular = sp;
}

void GraphicObject_ColorLight::SetWorld(const Matrix& worldMat)
{
	world = worldMat;
}

void GraphicObject_ColorLight::Render()
{
	pModel->SetToContext(pShader->GetContext());
	for (int i = 0; i < meshCount; i++)
	{
		pShader->SendWorldAndMaterial(world, materials[i].ambient, materials[i].diffuse, materials[i].specular);
		pModel->Render(pShader->GetContext());
	}
}