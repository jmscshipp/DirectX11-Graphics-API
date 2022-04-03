// DXApp
// Andre Berthiaume, June 2016
// Note: DX 11 SDK https://www.microsoft.com/en-us/download/details.aspx?id=6812
// Note on weird stuff with swap chain (1s and 2s) https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

#ifndef _DXApp
#define _DXApp

#include <d3d11.h>
#include "d3dUtil.h"
#include "Align16.h"
#include "GameTimer.h"
#include <string>

// New includes for demo
#include "Vect.h"
#include "Matrix.h"
#include "Camera.h"
#include "ShaderColor.h"
#include "ShaderTexture.h"
#include "TextureLight.h"

class Model;
class Texture;
class FlatPlane;
class TerrainModel;
class Skybox;
class GraphicObject_TextureLight;
class GraphicObject_Color;
class GraphicObject_Texture;

class DXApp : public Align16
{
private:	
	// Main window handle
	HWND mhMainWnd;

	Vect BackgroundColor;

	// DX application elements
	ID3D11Device* md3dDevice;					// Connects to the graphics card
	ID3D11DeviceContext* md3dImmediateContext;	// Settings for the GPU to use
	IDXGISwapChain* mSwapChain;					// image buffers used for rendering
	ID3D11RenderTargetView* mRenderTargetView;	// Where to send rendring operations (typically: points to one of the swap buffers)
	ID3D11DepthStencilView* mpDepthStencilView; // Needed to force depth-buffer operations

	GameTimer mTimer;
	std::string mMainWndCaption;
	int mClientWidth;
	int mClientHeight;

	void InitDirect3D();
	void InitDemo();
	void UpdateScene();
	void DrawScene();
	void CalculateFrameStats();

	void RenderTree(float rotation, float xPos, float yPos, float ZPos);
	// Shader loading utility. SHould be moved elsewhere later...
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	// Debug utility
	void ReportLiveDXObjects();

	// MY STUFF
	float time;
	Camera mCam;
    
	TextureLight* pShaderTextureLight;
	ShaderTexture* pShaderTexture;
	ShaderColor* pShaderColor;

	// SKYBOX
	Texture* skyTex;
	Skybox* sky;
	Matrix skyWorld;
	// PERSON
	Model* personModel;
	GraphicObject_Color* gObjPerson;
	Vect personPos;
	Matrix personWorld;
	// HOUSE
	Texture* houseTex;
	Model* houseModel;
	GraphicObject_TextureLight* gObjHouse;
	Matrix houseWorld;
	// CAR
	Texture* carTex;
	Model* carModel;
	GraphicObject_TextureLight* gObjCar;
	Matrix carWorld;

	// TRUCK
	Texture* truckTex;
	Model* truckModel;
	GraphicObject_TextureLight* gObjTruck;
	Matrix truckWorld;

	// TERRAIN
	Texture* terrainTex;
	TerrainModel* terrainModel;
	Matrix terrainWorld;

	// ROAD
	Texture* roadTex;
	FlatPlane* roadModel;
	Matrix roadWorld;

	// TREE
	Texture* treeLeafTex;
	Model* treeModel;
	GraphicObject_TextureLight* gObjTree;
	Matrix treeWorld;

	// LAMP
	Texture* lampTex;
	Model* lampModel;
	GraphicObject_TextureLight* gObjLamp;
	Matrix lampWorld;

public:
	DXApp(HWND hwnd);
	virtual ~DXApp();
	
	void FrameTick();

	// overrides for handling mouse input.
	void OnMouseDown(WPARAM btnState, int xval, int yval);
	void OnMouseUp(WPARAM btnState, int xval, int yval);
	void OnMouseMove(WPARAM btnState, int xval, int yval);
	void OnMouseWheel(short delta);

};

#endif _DXApp