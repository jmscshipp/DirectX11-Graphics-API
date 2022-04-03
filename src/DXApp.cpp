#include "DXApp.h"
#include <windows.h>
#include <sstream>
#include <assert.h>
#include "d3dUtil.h"

// needed to load shaders from file
#include <d3dcompiler.h>

#include "Model.h"
#include "ShaderColor.h"
#include "DirectXTex.h"
#include "Texture.h"
#include "FlatPlane.h"
#include "Skybox.h"
#include "TerrainModel.h"
#include "GraphicObject_Color.h"
#include "GraphicObject_TextureLight.h"

void DXApp::InitDemo()
{
	time = 0.0f;
	// setting up color shader
	pShaderColor = new ShaderColor(md3dDevice);
	//setting up texture shader
	pShaderTexture = new ShaderTexture(md3dDevice);
	// setting up texture light shader
	pShaderTextureLight = new TextureLight(md3dDevice);
	pShaderTextureLight->SetPointLightParameters(0, Vect(29, 5, 49), 100, .2 * Vect(0, 1, 0), .1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));
	pShaderTextureLight->SetPointLightParameters(1, Vect(31, 5, 51), 100, .2 * Vect(0, 1, 0), .1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));
	//pShaderTextureLight->SetPointLightParameters(0, Vect(30, -3, 50), 100, .2 * Vect(0, 1, 0), .1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));
	pShaderTextureLight->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(), 0.1 * Vect(0.1f, 0.1f, 0.1f), .5 * Vect(0.1f, 0.1f, 0.1f), Vect(0.1f, 0.1f, 0.1f));
	
	// get texture for graphics object
	carTex = new Texture(md3dDevice, L"../Assets/Textures/cartex.tga");
	truckTex = new Texture(md3dDevice, L"../Assets/Textures/trucktex.tga");
	terrainTex = new Texture(md3dDevice, L"../Assets/Textures/sandgrass.tga", D3D11_FILTER_ANISOTROPIC, 4, true, 0);
	roadTex = new Texture(md3dDevice, L"../Assets/Textures/road.tga");
	houseTex = new Texture(md3dDevice, L"../Assets/Textures/house.tga");
	treeLeafTex = new Texture(md3dDevice, L"../Assets/Textures/treeleaves.tga");
	skyTex = new Texture(md3dDevice, L"../Assets/Textures/skyboxtex.tga");
	lampTex = new Texture(md3dDevice, L"../Assets/Textures/lamptex.tga");
	// get model for graphics objects
	carModel = new Model(md3dDevice, "../Assets/Models/car.azul");
	truckModel = new Model(md3dDevice, "../Assets/Models/truck.azul");
	terrainModel = new TerrainModel(md3dDevice, L"../Assets/Textures/HMtest.tga", 200, 15.0f, -0, 10, 10);
	roadModel = new FlatPlane(md3dDevice, 20, 1, 1);
	houseModel = new Model(md3dDevice, "../Assets/Models/house.azul");
	treeModel = new Model(md3dDevice, "../Assets/Models/tree.azul");
	lampModel = new Model(md3dDevice, "../Assets/Models/lamp.azul");
	personModel = new Model(md3dDevice, "../Assets/Models/person.azul");
	sky = new Skybox(md3dDevice, 2, 1, 1);
	// create graphics objects
	gObjCar = new GraphicObject_TextureLight(pShaderTextureLight, carModel);
	gObjTruck = new GraphicObject_TextureLight(pShaderTextureLight, truckModel);
	gObjHouse = new GraphicObject_TextureLight(pShaderTextureLight, houseModel);
	gObjTree = new GraphicObject_TextureLight(pShaderTextureLight, treeModel);
	gObjLamp = new GraphicObject_TextureLight(pShaderTextureLight, lampModel);
	gObjPerson = new GraphicObject_Color(pShaderColor, personModel);
	// set graphics object mats
	gObjCar->SetMaterial(Vect(1, 1, 1, 100), Vect(1, 1, 1, 100), Vect(1, 1, 1, 100));
	gObjTruck->SetMaterial(Vect(1, 1, 1, 100), Vect(1, 1, 1, 100), Vect(1, 1, 1, 100));
	gObjHouse->SetMaterial(Vect(1, 1, 1, 100), Vect(1, 1, 1, 100), Vect(1, 1, 1, 100));
	gObjTree->SetMaterial(Vect(1, 1, 1, 100), Vect(1, 1, 1, 100), Vect(1, 1, 1, 100));
	gObjLamp->SetMaterial(Vect(1, 1, 1, 100), Vect(1, 1, 1, 100), Vect(1, 1, 1, 100));
	gObjPerson->SetColor(Colors::White);
	// set graphics object texs
	gObjCar->SetTexture(carTex);
	gObjTruck->SetTexture(truckTex);
	gObjHouse->SetTexture(houseTex);
	gObjTree->SetTexture(treeLeafTex);
	gObjLamp->SetTexture(lampTex);
	// create world matrices
	carWorld = Matrix(SCALE, 1, 1, 1) * Matrix(TRANS, 14, -2.5, 3);
	truckWorld = Matrix(SCALE, 1, 1, 1) * Matrix(TRANS, 13.2f, -2.5, 25);
	terrainWorld = Matrix(SCALE, 1, 1, 1) * Matrix(TRANS, 0, -3, 40);
	roadWorld = Matrix(SCALE, 1, 1, 1) * Matrix(ROT_Y, 3.14f / 2.0f) * Matrix(TRANS, 2, 0, 3);
	houseWorld = Matrix(SCALE, 1, 1, 1) * Matrix(ROT_X, -3.14f / 2.0f) * Matrix(ROT_Y, -3.14f) * Matrix(TRANS, 50, 0, 50);
	lampWorld = Matrix(SCALE, 1, 1, 1) * Matrix(TRANS, 30, -3, 50);
	treeWorld = Matrix(SCALE, 1, 1, 1) * Matrix(ROT_X, -3.14f / 2.0f) * Matrix(TRANS, 50, 10, 3);
	skyWorld = Matrix(SCALE, 1, 1, 1) * Matrix(ROT_Y, 3.14f / 2.0f) * Matrix(TRANS, 0, 0, 0);
	personWorld = Matrix(SCALE, 1, 1, 1) * Matrix(ROT_X, -3.14f / 2.0f) * Matrix(ROT_Y, -3.14f) * Matrix(TRANS, 50, 20, 50);
	// set graphics object worlds
	gObjCar->SetWorld(carWorld);
	gObjTruck->SetWorld(truckWorld);
	gObjHouse->SetWorld(houseWorld);
	gObjTree->SetWorld(treeWorld);
	gObjLamp->SetWorld(lampWorld);
	gObjPerson->SetWorld(personWorld);

	// Initialize the projection matrix
	mCam.setPerspective( 3.14159/3, mClientWidth / (float)mClientHeight, 1.0f, 1000.0f);
	mCam.setOrientAndPosition(Vect(0, 1, 0), Vect(50, 0, 35), Vect(-23, 9, 7));

	mTimer.Reset();
}

void DXApp::UpdateScene()
{
	time += 0.001f;
	personPos = Vect(50, 22 + sin(time) * 10, 50);
	personWorld = Matrix(SCALE, 1, 1, 1) * Matrix(ROT_X, -3.14f / 2.0f) * Matrix(ROT_Y, -3.14f) * Matrix(TRANS, personPos);
	float camSpeed = 0.04f;
	if (GetKeyState('W') & 0x08000)
	{
		mCam.TranslateFwdBack(camSpeed);
	}
	else if (GetKeyState('S') & 0x08000)
	{
		mCam.TranslateFwdBack(-camSpeed);
	}

	if (GetKeyState('A') & 0x08000)
	{
		mCam.TranslateLeftRight(-camSpeed);
	}
	else if (GetKeyState('D') & 0x08000)
	{
		mCam.TranslateLeftRight(camSpeed);
	}

	float rotSpeed = 0.005f;
	if (GetKeyState(VK_LEFT) & 0x08000)
	{
		mCam.TurnLeftRight(rotSpeed);
	}
	else if (GetKeyState(VK_RIGHT) & 0x08000)
	{
		mCam.TurnLeftRight(-rotSpeed);
	}

	if (GetKeyState(VK_UP) & 0x08000)
	{
		mCam.TiltUpDown(rotSpeed);
	}
	else if (GetKeyState(VK_DOWN) & 0x08000)
	{
		mCam.TiltUpDown(-rotSpeed);
	}

	mCam.updateCamera();
}

void DXApp::DrawScene()
{
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, VasA(BackgroundColor));
	md3dImmediateContext->ClearDepthStencilView(mpDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	// skybox
	pShaderTexture->SetToContext(md3dImmediateContext);
	pShaderTexture->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	pShaderTexture->SetTextureResourceAndSampler(skyTex);
	pShaderTexture->SendWorld(skyWorld);
	sky->Render(md3dImmediateContext);

	// person
	pShaderColor->SetToContext(md3dImmediateContext);
	pShaderColor->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	gObjPerson->SetWorld(personWorld);
	gObjPerson->Render();

	// other objects
	pShaderTextureLight->SetToContext(md3dImmediateContext);
	pShaderTextureLight->SetPointLightParameters(2, personPos, 100, .2 * Vect(0, 1, 0), .1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));
	pShaderTextureLight->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	pShaderTextureLight->SendFogValues(60.0f, 50.0f, Vect(0.04705882352f, 0.05098039215f, 0.00784313725f, 1));

	Vect eyepos;
	mCam.getPos(eyepos);
	pShaderTextureLight->SendLightParameters(eyepos);

	pShaderTextureLight->SetTextureResourceAndSampler(terrainTex);
	pShaderTextureLight->SendWorldAndMaterial(terrainWorld, Colors::SandyBrown, Colors::SandyBrown, Vect(1, 1, 1, 100));
	terrainModel->Render(md3dImmediateContext);

	pShaderTextureLight->SetTextureResourceAndSampler(roadTex);
	pShaderTextureLight->SendWorldAndMaterial(roadWorld, Colors::DarkSlateGray, Colors::Gray, Vect(1, 1, 1, 100));
	roadModel->Render(md3dImmediateContext);

	roadWorld = Matrix(SCALE, 1, 1, 1) * Matrix(ROT_Y, 3.14f / 2.0f) * Matrix(TRANS, 2, -2.5f, -17);
	pShaderTextureLight->SendWorldAndMaterial(roadWorld, Colors::DarkSlateGray, Colors::Gray, Vect(1, 1, 1, 100));
	roadModel->Render(md3dImmediateContext);

	roadWorld = Matrix(SCALE, 1, 1, 1) * Matrix(ROT_Y, 3.14f / 2.0f) * Matrix(TRANS, 2, -2.5f, 3);
	pShaderTextureLight->SendWorldAndMaterial(roadWorld, Colors::DarkSlateGray, Colors::Gray, Vect(1, 1, 1, 100));
	roadModel->Render(md3dImmediateContext);

	roadWorld = Matrix(SCALE, 1, 1, 1) * Matrix(ROT_Y, 3.14f / 2.0f) * Matrix(TRANS, 2, -2.5f, 23);
	pShaderTextureLight->SendWorldAndMaterial(roadWorld, Colors::DarkSlateGray, Colors::Gray, Vect(1, 1, 1, 100));
	roadModel->Render(md3dImmediateContext);

	roadWorld = Matrix(SCALE, 1, 1, 1) * Matrix(ROT_Y, 3.14f / 2.0f) * Matrix(TRANS, 2, -2.5f, 43);
	pShaderTextureLight->SendWorldAndMaterial(roadWorld, Colors::DarkSlateGray, Colors::Gray, Vect(1, 1, 1, 100));
	roadModel->Render(md3dImmediateContext);

	roadWorld = Matrix(SCALE, 1, 1, 1) * Matrix(ROT_Y, 3.14f / 2.0f) * Matrix(TRANS, 2, -2.5f, 63);
	pShaderTextureLight->SendWorldAndMaterial(roadWorld, Colors::DarkSlateGray, Colors::Gray, Vect(1, 1, 1, 100));
	roadModel->Render(md3dImmediateContext);

	roadWorld = Matrix(SCALE, 1, 1, 1) * Matrix(ROT_Y, 3.14f / 2.0f) * Matrix(TRANS, 2, -2.5f, 83);
	pShaderTextureLight->SendWorldAndMaterial(roadWorld, Colors::DarkSlateGray, Colors::Gray, Vect(1, 1, 1, 100));
	roadModel->Render(md3dImmediateContext);

	// area near the cars
	RenderTree(5, 50, 10, 3);
	RenderTree(5, 50, 10, -10);
	RenderTree(1, 45, 9, 5);
	RenderTree(2, 41, 5, -9);
	RenderTree(14, 40, 6, 10);
	RenderTree(14, 40, 5, 0);
	RenderTree(14, 48, 8, -5);
	RenderTree(3, 30, 0, 5);
	RenderTree(15, 20, -3.3f, -10);
	RenderTree(5, 28, -2, -6);
	RenderTree(15, 25, -3.3f, 20);
	// area far side of the cabin
	RenderTree(5, 50, 5, 75);
	RenderTree(1, 45, 7, 85);
	RenderTree(12, 41, 1, 69);
	RenderTree(18, 28, -2, 75);
	RenderTree(6, 65, 10, 80);
	RenderTree(6, 68, 9, 95);
	RenderTree(6, 68, 9, 105);
	RenderTree(6, 60, 9, 110);
	RenderTree(6, 55, 8, 125);
	RenderTree(6, 50, 7, 110);
	// behind cabin
	RenderTree(11, 80, 5, 30);
	RenderTree(5, 60, 3, 28);
	RenderTree(3, 75, 1, 50);
	RenderTree(6, 75, 6, 68);

	gObjCar->Render();
	gObjTruck->Render();
	gObjHouse->Render();
	gObjLamp->Render();

	// Switches the display to show the now-finished back-buffer
	mSwapChain->Present(0, 0);
}

void DXApp::RenderTree(float rotation, float xPos, float yPos, float zPos)
{
	treeWorld = Matrix(SCALE, 1, 1, 1) * Matrix(ROT_X, -3.14f / 2.0f) * Matrix (ROT_Y, rotation) * Matrix(TRANS, xPos, yPos, zPos);
	gObjTree->SetWorld(treeWorld);
	gObjTree->Render();
}


DXApp::DXApp(HWND hwnd)
{
	assert(hwnd);
	mhMainWnd = hwnd;

	BackgroundColor = Colors::MidnightBlue;

	md3dDevice = nullptr;
	md3dImmediateContext = nullptr;
	mSwapChain = nullptr;
	mRenderTargetView = nullptr;

	// Get window data through the window handle
	RECT rc;
	BOOL err = GetClientRect(mhMainWnd, &rc);  // Seriously MS: Redifining BOOL as int? Confusing much?
	assert(err);

	// get width/hight
	mClientWidth = rc.right - rc.left;
	mClientHeight = rc.bottom - rc.top;

	// Get window caption
	const int MAX_LABEL_LENGTH = 100; // probably overkill...
	CHAR str[MAX_LABEL_LENGTH];
	GetWindowText(mhMainWnd, str, MAX_LABEL_LENGTH);
	mMainWndCaption = str;

	// Initialize DX11
	this->InitDirect3D();

	// Demo initialization
	this->InitDemo();
}

DXApp::~DXApp()
{
	delete pShaderTextureLight;
	delete pShaderTexture;
	delete pShaderColor;

	// PERSON
	delete personModel;
	delete gObjPerson;
	// HOUSE
	delete houseTex;
	delete houseModel;
	delete gObjHouse;
	// CAR
	delete carTex;
	delete carModel;
	delete gObjCar;
	// TRUCK
	delete truckTex;
	delete truckModel;
	delete gObjTruck;
	// TERRAIN
	delete terrainTex;
	delete terrainModel;
	// ROAD
	delete roadTex;
	delete roadModel;
	// TREE
	delete treeLeafTex;
	delete treeModel;
	delete gObjTree;
	// LAMP
	delete lampTex;
	delete lampModel;
	delete gObjLamp;
	// SKY BOX
	delete skyTex;
	delete sky;

	ReleaseAndDeleteCOMobject(mRenderTargetView);
	ReleaseAndDeleteCOMobject(mpDepthStencilView);
	ReleaseAndDeleteCOMobject(mSwapChain);
	ReleaseAndDeleteCOMobject(md3dImmediateContext);

	// Must be done BEFORE the device is released
	ReportLiveDXObjects();		// See http://masterkenth.com/directx-leak-debugging/

	ReleaseAndDeleteCOMobject(md3dDevice);
}

// See http://masterkenth.com/directx-leak-debugging/
void DXApp::ReportLiveDXObjects()
{
#ifdef _DEBUG
	HRESULT hr = S_OK;

	// Now we set up the Debug interface, to be queried on shutdown
	ID3D11Debug* debugDev;
	hr = md3dDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDev));

	debugDev->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	ReleaseAndDeleteCOMobject(debugDev);
#endif
}

void DXApp::InitDirect3D()
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// This is a *greatly* simplified process to create a DX device and context:
	// We force the use of DX11 feature level since that's what CDM labs are limited to.
	// For real-life applications would need to test what's the best feature level and act accordingly
	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, nullptr, 0, D3D11_SDK_VERSION, &md3dDevice, nullptr, &md3dImmediateContext);
	assert(SUCCEEDED(hr));

	// Now we obtain the associated DXGIfactory1 with our device 
	// Many steps...
	IDXGIDevice* dxgiDevice = nullptr;
	hr = md3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
	assert(SUCCEEDED(hr));

	IDXGIAdapter* adapter = nullptr;
	hr = dxgiDevice->GetAdapter(&adapter);
	assert(SUCCEEDED(hr));

	IDXGIFactory1* dxgiFactory1 = nullptr;
	hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory1));
	assert(SUCCEEDED(hr));
	// See also note on weird stuff with factories and swap chains (1s and 2s)
	// https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

	// We are done with these now...
	ReleaseAndDeleteCOMobject(adapter);
	ReleaseAndDeleteCOMobject(dxgiDevice);

	// Controls MSAA option:
	// - 4x count level garanteed for all DX11 
	// - MUST be the same for depth buffer!
	// - We _need_ to work with the depth buffer because reasons... (see below)
	DXGI_SAMPLE_DESC sampDesc;
	sampDesc.Count = 1;
	sampDesc.Quality = static_cast<UINT>(D3D11_CENTER_MULTISAMPLE_PATTERN);  // MS: what's with the type mismtach?

	DXGI_MODE_DESC buffdesc;				// https://msdn.microsoft.com/en-us/library/windows/desktop/bb173064(v=vs.85).aspx
	ZeroMemory(&buffdesc, sizeof(buffdesc));
	buffdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Next we create a swap chain. 
	// Useful thread: http://stackoverflow.com/questions/27270504/directx-creating-the-swapchain
	// Note that this is for a DirectX 11.0: in a real app, we should test the feature levels and act accordingly

	DXGI_SWAP_CHAIN_DESC sd;				// See MSDN: https://msdn.microsoft.com/en-us/library/windows/desktop/bb173075(v=vs.85).aspx
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;						// Much confusion about this number... see http://www.gamedev.net/topic/633807-swap-chain-buffer-count/
	sd.BufferDesc = buffdesc;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = mhMainWnd;
	sd.SampleDesc = sampDesc;
	sd.Windowed = TRUE;

	hr = dxgiFactory1->CreateSwapChain(md3dDevice, &sd, &mSwapChain);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(dxgiFactory1);

	// Create a render target view		https://msdn.microsoft.com/en-us/library/windows/desktop/ff476582(v=vs.85).aspx
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	assert(SUCCEEDED(hr));;

	hr = md3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mRenderTargetView);
	ReleaseAndDeleteCOMobject(pBackBuffer);
	assert(SUCCEEDED(hr));

	/**********************************************************/

	// First we fix what it means for triangles to be front facing.
	// Requires setting a whole new rasterizer state
	//*
	D3D11_RASTERIZER_DESC rd;
	//rd.FillMode = D3D11_FILL_WIREFRAME;  // Also: D3D11_FILL_WIREFRAME
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = true; // true for RH forward facing
	rd.DepthBias = 0;
	rd.SlopeScaledDepthBias = 0.0f;
	rd.DepthBiasClamp = 0.0f;
	rd.DepthClipEnable = true;
	rd.ScissorEnable = false;
	rd.MultisampleEnable = true;  // Does not in fact turn on/off multisample: https://msdn.microsoft.com/en-us/library/windows/desktop/ff476198(v=vs.85).aspx
	rd.AntialiasedLineEnable = true;

	ID3D11RasterizerState* rs;
	md3dDevice->CreateRasterizerState(&rd, &rs);

	md3dImmediateContext->RSSetState(rs);
	ReleaseAndDeleteCOMobject(rs); // we can release this resource since we won't be changing it any further
	//*/

	// We must turn on the abilty to process depth during rendering.
	// Done through depth stencils (see https://msdn.microsoft.com/en-us/library/windows/desktop/bb205074(v=vs.85).aspx)
	// Below is a simplified version
	//*
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = mClientWidth;
	descDepth.Height = mClientHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc = sampDesc;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	ID3D11Texture2D* pDepthStencil;
	hr = md3dDevice->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
	assert(SUCCEEDED(hr));

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	descDSV.Texture2D.MipSlice = 0;;

	hr = md3dDevice->CreateDepthStencilView(pDepthStencil, &descDSV, &mpDepthStencilView);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(pDepthStencil);
	//*/

	/**********************************************************/

	//md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, nullptr);  // to use without depth stencil
	md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mpDepthStencilView);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)mClientWidth;
	vp.Height = (FLOAT)mClientHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	md3dImmediateContext->RSSetViewports(1, &vp);
}

void DXApp::CalculateFrameStats()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if ((mTimer.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::ostringstream outs;
		outs.precision(6);
		outs << mMainWndCaption << "    "
			<< "FPS: " << fps << "    "
			<< "Frame Time: " << mspf << " (ms)";
		SetWindowText(mhMainWnd, outs.str().c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

void DXApp::FrameTick()
{
	mTimer.Tick();
	CalculateFrameStats();

	this->UpdateScene();
	this->DrawScene();
}

void DXApp::OnMouseDown(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void DXApp::OnMouseUp(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void DXApp::OnMouseMove(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void  DXApp::OnMouseWheel(short delta)
{
	UNREFERENCED_PARAMETER(delta);
}


// Shader loading utility. Will be moved elsewhere later...
// Needs to be moved. Requires
HRESULT DXApp::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}