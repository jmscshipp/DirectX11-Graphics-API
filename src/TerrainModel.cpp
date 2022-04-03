#include "TerrainModel.h"
#include "Model.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include <assert.h>

TerrainModel::TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV)
{
	DirectX::ScratchImage scrtTex;
	HRESULT hr = LoadFromTGAFile(heightmapFile, nullptr, scrtTex);
	assert(SUCCEEDED(hr));

	const DirectX::Image* hgtmap = scrtTex.GetImage(0, 0, 0);
	assert(hgtmap->height == hgtmap->width);

	size_t side = hgtmap->height;	// the image should be square
	size_t pixel_width = 4;			// 4 bytes RGBA per pixel
	uint8_t h_val = hgtmap->pixels[pixel_width * (5 * side + 3)]; // the 'R' byte of the pixel at (3,5)

	int vertNum = len * len;
	StandardVertex* verts = new StandardVertex[vertNum];

	int triNum = (len - 1) * (len - 1) * 2;
	TriangleByIndex* tris = new TriangleByIndex[triNum];

	float urep = RepeatU / (len - 1);
	float vrep = RepeatV / (len - 1);

	float scale = (len / side);
	float yScale = (255 / maxheight);

	// setting up vertices
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			verts[GetVertexIndex(len, i, j)].set(i - len / 2, hgtmap->pixels[GetTexelIndex(pixel_width, side, i / scale, j / scale)] / yScale, j - len / 2, urep * i, vrep * j);
			//Trace::out("created vertex at %f, %f\n", i - len / 2, j - len / 2);
			// x : i
			// y : hgtmap->pixels[GetTexelIndex(pixel_width, side, i / scale, j / scale)] / yScale
			// z : j
			// u : urep * i
			// v : vrep * j
		}
	}

	// computing normals
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			// check to make sure we skip edge vertices
			if (i != 0 && i != len - 1 && j != 0 && j != len - 1)
			{
				// center
				StandardVertex* center = &verts[GetVertexIndex(len, i, j)];
				// left
				StandardVertex* left = &verts[GetVertexIndex(len, i - 1, j)];
				// right
				StandardVertex* right = &verts[GetVertexIndex(len, i + 1, j)];
				// up
				StandardVertex* up = &verts[GetVertexIndex(len, i, j + 1)];
				// down
				StandardVertex* down = &verts[GetVertexIndex(len, i, j - 1)];
				// down diagonal
				StandardVertex* downDiag = &verts[GetVertexIndex(len, i - 1, j - 1)];
				// up diagonal
				StandardVertex* upDiag = &verts[GetVertexIndex(len, i + 1, j + 1)];

				// left side face
				Vect edge1 = left->Pos - center->Pos;
				Vect helperEdge = up->Pos - center->Pos;
				edge1 = edge1.cross(helperEdge).getNorm();
				// right side face
				Vect edge2 = right->Pos - center->Pos;
				helperEdge = down->Pos - center->Pos;
				edge2 = edge2.cross(helperEdge).getNorm();
				// bottom left corner face
				Vect edge3 = left->Pos - center->Pos;
				helperEdge = downDiag->Pos - center->Pos;
				edge3 = edge3.cross(helperEdge).getNorm();
				// bottom right corner face
				Vect edge4 = down->Pos - center->Pos;
				helperEdge = downDiag->Pos - center->Pos;
				edge4 = edge4.cross(helperEdge).getNorm();
				// top left corner face
				Vect edge5 = up->Pos - center->Pos;
				helperEdge = upDiag->Pos - center->Pos;
				edge5 = edge5.cross(helperEdge).getNorm();
				// top right corner face
				Vect edge6 = right->Pos - center->Pos;
				helperEdge = upDiag->Pos - center->Pos;
				edge6 = edge6.cross(helperEdge).getNorm();

				helperEdge = Vect((edge1.X() + edge2.X() + edge3.X() + edge4.X() + edge5.X() + edge6.X()) / 6,
					(edge1.Y() + edge2.Y() + edge3.Y() + edge4.Y() + edge5.Y() + edge6.Y()) / 6,
					(edge1.Z() + edge2.Z() + edge3.Z() + edge4.Z() + edge5.Z() + edge6.Z()) / 6);

				verts[GetVertexIndex(len, i, j)].normal = helperEdge;

			}
			else
				verts[GetVertexIndex(len, i, j)].normal = Vect(0, 0, 0);
		}
	}

	// setting up triangles
	int triangleIndex = 0;
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1; j++)
		{
			tris[triangleIndex++].set(j + (len * i) + 1, j + len + (len * i), j + (len * i));
			tris[triangleIndex++].set(j + (len * i) + 1, j + len + (len * i) + 1, j + len + (len * i));
		}
	}

	pModTerrain = new Model(dev, verts, vertNum, tris, triNum);
	delete[] verts;
	delete[] tris;
}

int TerrainModel::GetVertexIndex(int sideLength, int i, int j)
{
	return i * sideLength + j;
}

int TerrainModel::GetTexelIndex(size_t pixelWidth, int sideLength, int i, int j)
{
	return pixelWidth * (j * sideLength + i);
}

void TerrainModel::Render(ID3D11DeviceContext* context)
{
	pModTerrain->SetToContext(context);
	pModTerrain->Render(context);
}

TerrainModel::~TerrainModel()
{
	delete pModTerrain;
}