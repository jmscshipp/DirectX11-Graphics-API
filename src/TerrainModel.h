#ifndef _TerrainModel
#define _TerrainModel

#include "Matrix.h"
#include <tuple>
#include <d3d11.h>
#include "DirectXTex.h"
#include "Model.h";

struct ID3D11DeviceContext;
struct ID3D11Device;

class TerrainModel : public Align16
{

private:
	Model* pModTerrain;

	int GetVertexIndex(int sideLength, int i, int j);
	int GetTexelIndex(size_t pixelWidth, int sideLength, int i, int j);

public:
	TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV);
	TerrainModel(const TerrainModel&) = delete;			
	TerrainModel(TerrainModel&&) = delete;                 
	TerrainModel& operator=(const TerrainModel&) = delete; 
	TerrainModel& operator=(TerrainModel&&) = delete;      
	~TerrainModel();

	void Render(ID3D11DeviceContext* context);

};



#endif _TerrainModel