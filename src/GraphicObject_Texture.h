#ifndef _GraphicObject_Texture
#define _GraphicObject_Texture

#include "GraphicObject_Base.h"

// forward declarations
class ShaderTexture;
class Texture;

class GraphicObject_Texture : public GraphicObject_Base
{
public:
	GraphicObject_Texture(ShaderTexture* shader, Model* model);
	GraphicObject_Texture(const GraphicObject_Texture&) = delete;				   // Copy constructor
	GraphicObject_Texture(GraphicObject_Texture&&) = default;                    // Move constructor
	GraphicObject_Texture& operator=(const GraphicObject_Texture&) = default;  // Copy assignment operator
	GraphicObject_Texture& operator=(GraphicObject_Texture&&) = default;       // Move assignment operator
	~GraphicObject_Texture();		  							   // Destructor

	// sets all meshes
	void SetTexture(Texture* tex);
	// sets specific mesh
	void SetTexture(Texture* tex, int meshIndex);
	void SetWorld(const Matrix& worldMat);
	virtual void Render() override;

protected:
	ShaderTexture* pShader;
	Texture** textures;
	int meshCount;
	Matrix world;
};

#endif