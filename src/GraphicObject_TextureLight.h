#ifndef _GraphicObject_TextureLight
#define _GraphicObject_TextureLight

#include "GraphicObject_Base.h"

// forward declaration
class TextureLight;
class Texture;
class Model;

class GraphicObject_TextureLight : public GraphicObject_Base
{
public:
	GraphicObject_TextureLight(TextureLight* shader, Model* model);
	GraphicObject_TextureLight(const GraphicObject_TextureLight&) = delete;				   // Copy constructor
	GraphicObject_TextureLight(GraphicObject_TextureLight&&) = default;                    // Move constructor
	GraphicObject_TextureLight& operator=(const GraphicObject_TextureLight&) = default;  // Copy assignment operator
	GraphicObject_TextureLight& operator=(GraphicObject_TextureLight&&) = default;       // Move assignment operator
	~GraphicObject_TextureLight();		  							   // Destructor
	
	// set all meshes
	void SetTexture(Texture* tex);
	void SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp);
	// sets specific mesh
	void SetTexture(Texture* tex, int meshIndex);
	void SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp, int meshIndex);

	void SetWorld(const Matrix& worldMat);
	virtual void Render() override;

protected:

	struct Material
	{
		Vect ambient;
		Vect diffuse;
		Vect specular;
	};

	TextureLight* pShader;
	Texture** textures;
	Material* materials;
	Matrix world;
	int meshCount;
};

#endif