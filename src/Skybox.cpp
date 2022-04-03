#include "Skybox.h"
#include "Model.h"
#include "d3dUtil.h"

Skybox::Skybox(ID3D11Device* dev, float len, float urep, float vrep)
{
	int boxSize = 500;

	int nverts = 24;
	StandardVertex* pVerts = new StandardVertex[nverts];

	int ntri = 12;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	// Setting up faces
		// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(boxSize, boxSize, boxSize, 0.25f, 0.333334f);
	pVerts[vind + 1].set(-boxSize, boxSize, boxSize, 0.5f, 0.333334f);
	pVerts[vind + 2].set(-boxSize, -boxSize, boxSize, 0.5f, 0.666667f);
	pVerts[vind + 3].set(boxSize, -boxSize, boxSize, 0.25f, 0.666667f);
	pTriList[tind].set(vind + 2, vind + 1, vind + 0);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind + 0);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(boxSize, boxSize, -boxSize, 1, 0.333334f);
	pVerts[vind + 1].set(-boxSize, boxSize, -boxSize, 0.75f, 0.333334f);
	pVerts[vind + 2].set(-boxSize, -boxSize, -boxSize, 0.75f, 0.666667f);
	pVerts[vind + 3].set(boxSize, -boxSize, -boxSize, 1, 0.666667f);
	pTriList[tind].set(vind + 0, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind + 0, vind + 2, vind + 3);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(boxSize, boxSize, -boxSize, 0.0f, 0.333334f);
	pVerts[vind + 1].set(boxSize, boxSize, boxSize, 0.25f, 0.333334f);
	pVerts[vind + 2].set(boxSize, -boxSize, boxSize, 0.25f, 0.666667f);
	pVerts[vind + 3].set(boxSize, -boxSize, -boxSize, 0.0f, 0.666667f);
	pTriList[tind].set(vind + 2, vind + 1, vind + 0);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind + 0);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-boxSize, boxSize, boxSize, 0.5f, 0.333334f);
	pVerts[vind + 1].set(-boxSize, boxSize, -boxSize, 0.75, 0.333334f);
	pVerts[vind + 2].set(-boxSize, -boxSize, -boxSize, 0.75, 0.666667f);
	pVerts[vind + 3].set(-boxSize, -boxSize, boxSize, 0.5f, 0.666667f);
	pTriList[tind].set(vind + 2, vind + 1, vind + 0);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind + 0);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(boxSize, boxSize, -boxSize, 0.25f, 0.001f);
	pVerts[vind + 1].set(-boxSize, boxSize, -boxSize, 0.5f, 0.001f);
	pVerts[vind + 2].set(-boxSize, boxSize, boxSize, 0.5f, 0.333334f);
	pVerts[vind + 3].set(boxSize, boxSize, boxSize, 0.25f, 0.333334f);
	pTriList[tind].set(vind + 2, vind + 1, vind + 0);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind + 0);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(boxSize, -boxSize, boxSize, 0.25f, 0.666667f);
	pVerts[vind + 1].set(-boxSize, -boxSize, boxSize, 0.5f, 0.666667f);
	pVerts[vind + 2].set(-boxSize, -boxSize, -boxSize, 0.5f, 0.99f);
	pVerts[vind + 3].set(boxSize, -boxSize, -boxSize, 0.25f, 0.99f);
	pTriList[tind].set(vind + 2, vind + 1, vind + 0);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind + 0);

	pPlane = new Model(dev, pVerts, nverts, pTriList, ntri);

	delete[] pVerts;
	delete[] pTriList;
}

Skybox::~Skybox()
{
	delete pPlane;
}

void Skybox::Render(ID3D11DeviceContext* context)
{
	pPlane->SetToContext(context);
	pPlane->Render(context);
}