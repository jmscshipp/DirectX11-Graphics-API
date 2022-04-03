#ifndef _GraphicObject_ColorLight
#define _GraphicObject_ColorLight

#include "GraphicObject_Base.h"

// forward declaration
class ShaderColorLight;
class Model;

class GraphicObject_ColorLight : public GraphicObject_Base
{
public:
	GraphicObject_ColorLight(ShaderColorLight* shader, Model* model);
	GraphicObject_ColorLight(const GraphicObject_ColorLight&) = delete;				   // Copy constructor
	GraphicObject_ColorLight(GraphicObject_ColorLight&&) = default;                    // Move constructor
	GraphicObject_ColorLight& operator=(const GraphicObject_ColorLight&) = default;  // Copy assignment operator
	GraphicObject_ColorLight& operator=(GraphicObject_ColorLight&&) = default;       // Move assignment operator
	~GraphicObject_ColorLight();		  							   // Destructor

	// set all materials
	void SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp);
	// set specific material
	void SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp, int num);
	void SetWorld(const Matrix& worldMat);
	virtual void Render() override;

	friend class ShaderColorLight;

protected:

	struct Material
	{
		Vect ambient;
		Vect diffuse;
		Vect specular;
	};

	ShaderColorLight* pShader;
	Material* materials;
	Matrix world;
	int meshCount;
};

#endif