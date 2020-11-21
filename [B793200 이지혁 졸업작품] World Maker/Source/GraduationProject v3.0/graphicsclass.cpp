////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_ShaderManager = 0;
	m_Camera = 0;
	for (int i = 0; i < LIGHTNUM; i++)
		m_Light[i] = 0;
	for (int i = 0; i < MAXMODELNUM; i++)
		m_Model[i] = 0;

	m_PointLight0 = 0;

	m_Text = 0;

	m_Skybox = 0;

	m_Md5Model = 0;

	m_Game = 0;

	for (int i = 0; i < BITMAPNUM; i++)
		m_Bitmap[i] = 0;

	m_movement = 0.0f;
	m_AImovement = 0.0f;
	plusMinus = 1;

	checkFirst = false;

	isLClicked = false;
	isRClicked = false;

	m_animTimeStack = 0.0f;
	m_constructAnimTrigger = false;

	m_charPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_charRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < LOOTINGMODELNUM; i++)
		m_isLootModelRender[i] = true;

	isF5On = false;
	isEnterOn = false;

	tfI = false;
	isIOn = false;

	tfE = false;
	isEOn = false;

	cactusCollision1 = false;
	cactusCollision2 = false;
	cactusCollision3 = false;

	palmTreeExTF1 = true;
	palmTreeExTF2 = true;
	palmTreeExTF3 = true;

	woodStackTF1 = true;
	woodStackTF2 = true;
	woodStackTF3 = true;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	m_hwnd = hwnd;

	bool result;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if (!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	// Create the game object.
	m_Game = new GameClass;
	if (!m_Game)
	{
		return false;
	}

	// Initialize the game object.
	result = m_Game->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}


	///////////
	// Sound //
	///////////

	// Create the sound object.
	m_Sound = new SoundClass;

	// Initialize the sound object.
	result = m_Sound->Initialize(hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct Sound.", L"Error", MB_OK);
		return false;
	}

	// Play the wave file now that it has been loaded.
	// result = m_Sound->PlayWaveFile(0, true, -1500);


	////////////
	// Camera //
	////////////

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, 0.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(m_BaseViewMatrix);
	m_Camera->SetPosition(0.0f, 100.0f, 0.0f);
	m_Camera->SetRotation(20.0f, 0.0f, 0.0f);


	////////////
	// Skybox //
	////////////

	// Create the skybox object.
	m_Skybox = new SkyboxClass;
	if (!m_Skybox)
	{
		return false;
	}

	m_Skybox->CreateSphere(m_D3D->GetDevice(), 10, 10);
	m_Skybox->InitializeSkyboxShader(m_D3D->GetDevice());


	////////////////
	// FontEngine //
	////////////////

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, m_BaseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}


	//////////////////
	// BitmapShader //
	//////////////////

	// Create the texture shader object.
	m_BitmapShader = new BitmapShaderClass;
	if (!m_BitmapShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_BitmapShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap shader object.", L"Error", MB_OK);
		return false;
	}


	/////////////////
	// Bitmap (UI) //
	/////////////////

	for (int i = 0; i < BITMAPNUM; i++)
	{
		// Create the bitmap object.
		m_Bitmap[i] = new BitmapClass;
		if (!m_Bitmap)
		{
			return false;
		}
	}

	// Initialize the bitmap object.
	result = m_Bitmap[0]->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, (WCHAR*)L"../GraduationProject v3.0/UI/1600 x 900/UI Construction container SciFi crate.png", 239, 239);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap[1]->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, (WCHAR*)L"../GraduationProject v3.0/UI/1600 x 900/UI Inventory HUD with Jewels and woodstack.png", 606, 73);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap[2]->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, (WCHAR*)L"../GraduationProject v3.0/UI/1600 x 900/World Maker Title img.png", 1600, 900);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap[3]->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, (WCHAR*)L"../GraduationProject v3.0/UI/1600 x 900/World Maker Controls img2.png", 1600, 900);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap[4]->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, (WCHAR*)L"../GraduationProject v3.0/UI/1600 x 900/World Maker Ending img.png", 1600, 900);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap[5]->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, (WCHAR*)L"../GraduationProject v3.0/UI/Tutorial instruction resized.png", 500, 200);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap[6]->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, (WCHAR*)L"../GraduationProject v3.0/UI/Exclamation mark resized.png", 80, 80);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap[7]->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, (WCHAR*)L"../GraduationProject v3.0/UI/1600 x 900/UI Inventory window.png", 554, 714);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap[8]->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, (WCHAR*)L"../GraduationProject v3.0/UI/Tutorial instruction2.png", 500, 200);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap[9]->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, (WCHAR*)L"../GraduationProject v3.0/UI/1600 x 900/UI Build Menu2.jpg", 478, 717);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the bitmap object. (Builtype == MARKETTENT)
	result = m_Bitmap[10]->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, (WCHAR*)L"../GraduationProject v3.0/UI/1600 x 900/UI Construction container market tent.png", 239, 239);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the bitmap object. (Buildtype == ENERGYCELL)
	result = m_Bitmap[11]->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, (WCHAR*)L"../GraduationProject v3.0/UI/1600 x 900/UI Construction container Energy Cell.png", 239, 239);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the bitmap object. (Buildtype == MARKETTENTADVENCED)
	result = m_Bitmap[12]->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, (WCHAR*)L"../GraduationProject v3.0/UI/1600 x 900/UI Construction container market tent advenced.png", 239, 239);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}


	/////////////
	// Raycast //
	/////////////

	// Create the raycast object.
	m_Raycast = new RaycastingClass;
	if (!m_Raycast)
	{
		return false;
	}


	/////////////////
	// NormalLight //
	/////////////////

	// Create the light object.
	for (int i = 0; i < LIGHTNUM; i++)
		m_Light[i] = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.

	//0 -1 0 Direction Light with high SpecularPower
	m_Light[0]->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light[0]->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light[0]->SetDirection(0.0f, -1.0f, 0.0f);
	m_Light[0]->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light[0]->SetSpecularPower(0.5f);

	//1 -1 1 Direction Light with high SpecularPower
	m_Light[1]->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light[1]->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light[1]->SetDirection(1.0f, -1.0f, 1.0f);
	m_Light[1]->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light[1]->SetSpecularPower(64.0f);


	////////////////
	// PointLight //
	////////////////

	// Create the first pointlight object.
	m_PointLight0 = new PointLightClass;
	if (!m_PointLight0)
	{
		return false;
	}

	// Initialize the first pointlight object.
	m_PointLight0->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_PointLight0->SetPosition(-1463.0f, 786.0f, -959.0f);


	// Create the model objects.
	for (int i = 0; i < MAXMODELNUM; i++)
	{
		m_Model[i] = new ModelClass;
		if (!m_Model[i])
		{
			return false;
		}
	}


	///////////////
	// Md5 Model //
	///////////////

	// Create the Md5Model object.
	m_Md5Model = new Md5ModelClass;
	if (!m_Md5Model)
	{
		return false;
	}

	// Initialize the Md5Model object.
	result = m_Md5Model->InitializeMd5Model
	(
		L"NuclearSuit character.md5mesh",
		L"NuclearSuit character Walk.md5anim",
		L"NuclearSuit character Construction.md5anim",
		m_D3D->GetDevice()
	);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Md5Model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the Md5Shader.
	m_Md5Model->InitializeMd5Shader(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), screenWidth, screenHeight);

	m_Md5Model->MakeAABB(XMMatrixIdentity());


	////////////////////////
	// MAINSCENE1 OBJECTS //
	////////////////////////

	///////////
	// Floor //
	///////////

	// Initialize the model0 object. (Floor.obj)
	result = m_Model[0]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Floor.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/darkGreenGrass.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	/////////////////
	// Emvironment //
	/////////////////

	// Initialize the model1 object.
	result = m_Model[1]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Rock1.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/NatureMap.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model2 object.
	result = m_Model[2]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Rock2.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/NatureMap.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model3 object.
	result = m_Model[3]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Rock3.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/NatureMap.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model4 object.
	result = m_Model[4]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Rock4.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/NatureMap.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model5 object.
	result = m_Model[5]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Rock5.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/NatureMap.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model6 object.
	result = m_Model[6]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Rock6.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/NatureMap.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model7 object.
	result = m_Model[7]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Tree1.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/NatureMap.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model8 object.
	result = m_Model[8]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/PineTree1.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Nature_PineTree_RoseBush_Weeds.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model9 object.
	result = m_Model[9]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/PineTree2.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Nature_PineTree_RoseBush_Weeds.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model10 object.
	result = m_Model[10]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/PineTree3.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Nature_PineTree_RoseBush_Weeds.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model11 object.
	result = m_Model[11]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/RoseBush1.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Nature_PineTree_RoseBush_Weeds.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model12 object.
	result = m_Model[12]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/RoseBush2.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Nature_PineTree_RoseBush_Weeds.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model13 object.
	result = m_Model[13]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Weeds1.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Nature_PineTree_RoseBush_Weeds.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model14 object.
	result = m_Model[14]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Mushrooms1.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Nature_Mushrooms.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	//////////////////
	// Looting Gems //
	//////////////////

	// Initialize the model15 object.
	result = m_Model[15]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Emerald1.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Gems.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model16 object.
	result = m_Model[16]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Emerald2.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Gems.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model17 object.
	result = m_Model[17]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Emerald3.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Gems.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model18 object.
	result = m_Model[18]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Ruby1.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Gems.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model19 object.
	result = m_Model[19]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Ruby2.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Gems.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model20 object.
	result = m_Model[20]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Ruby3.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Gems.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model21 object.
	result = m_Model[21]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Sapphire1.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Gems.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model22 object.
	result = m_Model[22]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Sapphire2.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Gems.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model23 object.
	result = m_Model[23]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Sapphire3.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Gems.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model24 object.
	result = m_Model[24]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Amethyst1.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Gems.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model25 object.
	result = m_Model[25]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Amethyst2.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Gems.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model26 object.
	result = m_Model[26]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Amethyst3.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Gems.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	/////////////////
	// SciFiCrates //
	/////////////////

	// Initialize the model13 object.
	result = m_Model[27]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/SciFiCrates.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/crateTexture.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	/////////////////////////////
	// BoundingBox MAINSCENE 1 //
	/////////////////////////////

	for (int i = 1; i < CURRENTMODELNUM - CONSTRUCTIONMODELNUM; i++)
	{
		m_Model[i]->MakeAABB(XMMatrixIdentity());
	}


	////////////////////
	// Visual Effects //
	////////////////////

	// Fire
	result = m_Model[28]->InitializeFire(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/fireplane.txt", (WCHAR*)L"../GraduationProject v3.0/texture/fire01.dds", (WCHAR*)L"../GraduationProject v3.0/texture/noise01.dds", (WCHAR*)L"../GraduationProject v3.0/texture/alpha01.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fire model object.", L"Error", MB_OK);
		return false;
	}

	// Portal
	result = m_Model[29]->InitializeFire(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/fireplane.txt", (WCHAR*)L"../GraduationProject v3.0/texture/spin02.png", (WCHAR*)L"../GraduationProject v3.0/texture/soundwave.png", (WCHAR*)L"../GraduationProject v3.0/texture/alpha01.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fire model object.", L"Error", MB_OK);
		return false;
	}

	// Portal
	result = m_Model[30]->InitializeFire(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/fireplane.txt", (WCHAR*)L"../GraduationProject v3.0/texture/spin03.png", (WCHAR*)L"../GraduationProject v3.0/texture/soundwave2.png", (WCHAR*)L"../GraduationProject v3.0/texture/alpha01.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fire model object.", L"Error", MB_OK);
		return false;
	}


	//////////////////////////
	// MAIN SCENE 2 OBJECTS //
	//////////////////////////

	// ExtractablePalmTree1
	result = m_Model[31]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/PalmTreeExtractable1.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/colorfulMapDesert.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// ExtractablePalmTree2
	result = m_Model[32]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/PalmTreeExtractable2.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/colorfulMapDesert.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// ExtractablePalmTree3
	result = m_Model[33]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/PalmTreeExtractable3.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/colorfulMapDesert.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// PalmTreeGroup
	result = m_Model[34]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/PalmTreeGroup.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/colorfulMapDesert.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// CactusPlantLarge
	result = m_Model[35]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/CactusPlantLarge.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/colorfulMapDesert.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// CactusPlantSmall
	result = m_Model[36]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/CactusPlantSmall.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/colorfulMapDesert.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// DesertLongRock
	result = m_Model[37]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/DesertLongRock.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/colorfulMapDesert.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// DesertBigRock
	result = m_Model[38]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/DesertBigRock.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/colorfulMapDesert.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// DesertFatRock
	result = m_Model[39]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/DesertFatRock.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/colorfulMapDesert.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// DesertMiddleRock
	result = m_Model[40]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/DesertMiddleRock.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/colorfulMapDesert.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// DesertSmallRock
	result = m_Model[41]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/DesertSmallRock.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/colorfulMapDesert.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// PalmTree
	result = m_Model[42]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/PalmTree.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/colorfulMapDesert.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// PalmTreeCurved
	result = m_Model[43]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/PalmTreeCurved.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/colorfulMapDesert.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// DesertFloor
	result = m_Model[44]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/Floor.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/DesertTexture.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// WoodStackLoot 1
	result = m_Model[48]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/WoodStackLoot1.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Nature_PineTree_RoseBush_Weeds.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// WoodStackLoot 2
	result = m_Model[49]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/WoodStackLoot2.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Nature_PineTree_RoseBush_Weeds.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	
	// WoodStackLoot 3
	result = m_Model[50]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/WoodStackLoot3.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Nature_PineTree_RoseBush_Weeds.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// MarketTent
	result = m_Model[51]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/MarketTent.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/Nature_PineTree_RoseBush_Weeds.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	////////////////////
	// Collsion Boxes //
	////////////////////

	// Collision Box 1 (Cactus 1)
	result = m_Model[45]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/ExtractableCactusCollisionBox1.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/TransparentTexture.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Collision Box 2 (Cactus 2)
	result = m_Model[46]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/ExtractableCactusCollisionBox2.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/TransparentTexture.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Collision Box 3 (Cactus 3)
	result = m_Model[47]->Initialize(m_D3D->GetDevice(), (char*)"../GraduationProject v3.0/ExtractableCactusCollisionBox3.txt",
		(WCHAR*)L"../GraduationProject v3.0/Texture/TransparentTexture.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	/////////////////////////////
	// BoundingBox MAINSCENE 2 //
	/////////////////////////////

	for (int i = 1; i <= 50; i++)
	{
		for (int j = 15; j <= 30; j++)
			continue;

		m_Model[i]->MakeAABB(XMMatrixIdentity());
	}


	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the model objects.
	for (int i = 0; i < MAXMODELNUM; i++)
	{
		m_Model[i]->Shutdown();
		delete m_Model[i];
		m_Model[i] = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		for (int i = 0; i < LIGHTNUM; i++)
		{
			delete m_Light[i];
			m_Light[i] = 0;
		}
	}

	// Release the light objects.
	if (m_PointLight0)
	{
		delete m_PointLight0;
		m_PointLight0 = 0;
	}

	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the bitmap shader object.
	if (m_BitmapShader)
	{
		m_BitmapShader->Shutdown();
		delete m_BitmapShader;
		m_BitmapShader = 0;
	}

	// Release the bitmap objects.
	for (int i = 0; i < BITMAPNUM; i++)
	{
		if (m_Bitmap)
		{
			m_Bitmap[i]->Shutdown();
			delete m_Bitmap[i];
			m_Bitmap[i] = 0;
		}
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_Skybox)
	{
		m_Skybox->Shutdown();
		delete m_Skybox;
		m_Skybox = 0;
	}

	if (m_Raycast)
	{
		delete m_Raycast;
		m_Raycast = 0;
	}

	if (m_Md5Model)
	{
		delete m_Md5Model;
		m_Md5Model = 0;
	}

	// Release the shader manager object.
	if(m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame(HWND hwnd, int fps, int cpu, int obj, int poly, int screenX, int screenY, float frameTime, DIMOUSESTATE mouseState, bool isEnterPressed, bool isF5Pressed, bool isSpacePressed, bool isIPressed, bool isEPressed, bool is1Pressed, bool is2Pressed, bool is3Pressed, bool is4Pressed)
{
	// Clip the mouse cursor
	RECT rc2;
	POINT lt, rb;
	GetClientRect(hwnd, &rc2);
	lt.x = rc2.left; lt.y = rc2.top; rb.x = rc2.right; rb.y = rc2.bottom;
	ClientToScreen(hwnd, &lt); ClientToScreen(hwnd, &rb);
	rc2.left = lt.x; rc2.top = lt.y; rc2.right = rb.x; rc2.bottom = rb.y;
	ClipCursor(&rc2);


	///////////////////
	// Scene control //
	///////////////////

	// Title Scene to Controls Scene
	if (m_Game->GetSceneType() == SceneType::TITLE && isEnterPressed)
	{
		m_Sound->PlayWaveFile(6, false);
		m_Game->SetSceneType(SceneType::CONTROLS);
	}

	// Controls Scene to Main Scene 1
	if (m_Game->GetSceneType() == SceneType::CONTROLS && isSpacePressed)
	{
		m_Sound->PlayWaveFile(6, false);
		m_Game->SetSceneType(SceneType::MAIN1);

		m_Sound->isTitleBGMStart = false;
		m_Sound->isMainBGMStart = true;
		m_Sound->isEndingBGMStart = false;
	}

	// Main Scene 1 to Title Scene
	if (m_Game->GetSceneType() == SceneType::MAIN1 && isF5Pressed)
	{
		m_Sound->PlayWaveFile(6, false);
		m_Game->SetSceneType(SceneType::TITLE);

		m_Sound->isTitleBGMStart = true;
		m_Sound->isMainBGMStart = false;
		m_Sound->isEndingBGMStart = false;

		m_Camera->SetPosition(0.0f, 100.0f, 0.0f);

		for (int i = 0; i < LOOTINGMODELNUM; i++)
		{
			m_isLootModelRender[i] = true;
			m_Model[i + 15]->SetColCheckEnabled(true);
		}

		m_Game->SetEmeralCnt(0);
		m_Game->SetRubyCnt(0);
		m_Game->SetSapphCnt(0);
		m_Game->SetAmethCnt(0);

		m_Game->SetConsModelNum(1, 0);
		m_Game->SetConsModelNum(2, 0);

		while (!insPos.empty())
		{
			insPos.pop_back();
			insRot.pop_back();
		}

		m_Game->SetWoodStackCnt(0);

		palmTreeExTF1 = true;
		palmTreeExTF2 = true;
		palmTreeExTF3 = true;

		woodStackTF1 = true;
		woodStackTF2 = true;
		woodStackTF3 = true;
	}

	// Main Scene 1 to Main Scene 2
	if (m_Game->GetSceneType() == SceneType::MAIN1 && m_Game->GetConsModelNum(1) == 3)
	{
		m_Sound->PlayWaveFile(6, false);
		m_Game->SetSceneType(SceneType::MAIN2);

		m_Sound->isTitleBGMStart = false;
		m_Sound->isMainBGMStart = true;
		m_Sound->isEndingBGMStart = false;

		m_Camera->SetPosition(0.0f, 100.0f, 0.0f);

		for (int i = 0; i < LOOTINGMODELNUM; i++)
		{
			m_isLootModelRender[i] = true;
			m_Model[i + 15]->SetColCheckEnabled(true);
		}

		m_Game->SetEmeralCnt(0);
		m_Game->SetRubyCnt(0);
		m_Game->SetSapphCnt(0);
		m_Game->SetAmethCnt(0);

		m_Game->SetConsModelNum(1, 0);
		m_Game->SetConsModelNum(2, 0);

		while (!insPos.empty())
		{
			insPos.pop_back();
			insRot.pop_back();
		}

		m_Game->SetWoodStackCnt(0);

		palmTreeExTF1 = true;
		palmTreeExTF2 = true;
		palmTreeExTF3 = true;

		woodStackTF1 = true;
		woodStackTF2 = true;
		woodStackTF3 = true;
	}

	// Main Scene 2 to Title Scene
	if (m_Game->GetSceneType() == SceneType::MAIN2 && isF5Pressed)
	{
		m_Sound->PlayWaveFile(6, false);
		m_Game->SetSceneType(SceneType::TITLE);

		m_Sound->isTitleBGMStart = true;
		m_Sound->isMainBGMStart = false;
		m_Sound->isEndingBGMStart = false;

		m_Camera->SetPosition(0.0f, 100.0f, 0.0f);

		for (int i = 0; i < LOOTINGMODELNUM; i++)
		{
			m_isLootModelRender[i] = true;
			m_Model[i + 15]->SetColCheckEnabled(true);
		}

		m_Game->SetEmeralCnt(0);
		m_Game->SetRubyCnt(0);
		m_Game->SetSapphCnt(0);
		m_Game->SetAmethCnt(0);

		m_Game->SetConsModelNum(1, 0);
		m_Game->SetConsModelNum(2, 0);

		while (!insPos.empty())
		{
			insPos.pop_back();
			insRot.pop_back();
		}

		m_Game->SetWoodStackCnt(0);

		palmTreeExTF1 = true;
		palmTreeExTF2 = true;
		palmTreeExTF3 = true;

		woodStackTF1 = true;
		woodStackTF2 = true;
		woodStackTF3 = true;
	}

	// Main Scene 2 to Ending Scene
	if (m_Game->GetSceneType() == SceneType::MAIN2 && m_Game->GetConsModelNum(2) == 2)
	{
		m_Game->SetSceneType(SceneType::ENDING);

		m_Sound->isTitleBGMStart = false;
		m_Sound->isMainBGMStart = false;
		m_Sound->isEndingBGMStart = true;
	}

	// Ending Scene to Title Scene
	if (m_Game->GetSceneType() == SceneType::ENDING && isF5Pressed)
	{
		m_Sound->PlayWaveFile(6, false);
		m_Game->SetSceneType(SceneType::TITLE);

		m_Sound->isTitleBGMStart = true;
		m_Sound->isMainBGMStart = false;
		m_Sound->isEndingBGMStart = false;

		m_Camera->SetPosition(0.0f, 100.0f, 0.0f);

		for (int i = 0; i < LOOTINGMODELNUM; i++)
		{
			m_isLootModelRender[i] = true;
			m_Model[i + 15]->SetColCheckEnabled(true);
		}

		m_Game->SetEmeralCnt(0);
		m_Game->SetRubyCnt(0);
		m_Game->SetSapphCnt(0);
		m_Game->SetAmethCnt(0);

		m_Game->SetConsModelNum(1, 0);
		m_Game->SetConsModelNum(2, 0);

		while (!insPos.empty())
		{
			insPos.pop_back();
			insRot.pop_back();
		}

		m_Game->SetWoodStackCnt(0);

		palmTreeExTF1 = true;
		palmTreeExTF2 = true;
		palmTreeExTF3 = true;

		woodStackTF1 = true;
		woodStackTF2 = true;
		woodStackTF3 = true;
	}

	bool result;
	static float rotation = 0.0f;

	if (!checkFirst)
	{
		m_obj = obj;
		m_poly = poly;
		
		checkFirst = true;
	}

	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.001f * frameTime;
	if (rotation > 2 * (float)D3DX_PI)
	{
		rotation -= 2 * (float)D3DX_PI;
	}

	//// Set the frames per second.
	//result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	//if (!result)
	//{
	//	return false;
	//}
	//// Set the cpu usage.
	//result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
	//if (!result) return false;

	//result = m_Text->SetObject(m_obj, m_D3D->GetDeviceContext());
	//if (!result) return false;

	//result = m_Text->SetPolygon(m_poly, m_D3D->GetDeviceContext());
	//if (!result) return false;

	//result = m_Text->SetScreenSize(screenX, screenY, m_D3D->GetDeviceContext());
	//if (!result) return false;

	//result = m_Text->SetCameraPos(m_Camera->GetPosition(), m_D3D->GetDeviceContext());
	//if (!result) return false;

	//result = m_Text->SetCameraRot(m_Camera->GetRotation(), m_D3D->GetDeviceContext());
	//if (!result) return false;

	result = m_Text->SetEmeralCnt(m_Game->GetEmeralCnt(), m_D3D->GetDeviceContext());
	if (!result) return false;

	result = m_Text->SetRubyCnt(m_Game->GetRubyCnt(), m_D3D->GetDeviceContext());
	if (!result) return false;

	result = m_Text->SetSapphCnt(m_Game->GetSapphCnt(), m_D3D->GetDeviceContext());
	if (!result) return false;

	result = m_Text->SetAmethCnt(m_Game->GetAmethCnt(), m_D3D->GetDeviceContext());
	if (!result) return false;

	result = m_Text->SetWoodStackCnt(m_Game->GetWoodStackCnt(), m_D3D->GetDeviceContext());
	if (!result) return false;

	if (is1Pressed)
		m_Game->SetBuildType(BuildType::SCFICRATE);
	if (is2Pressed)
		m_Game->SetBuildType(BuildType::MARKETTENT);
	if (is3Pressed)
		m_Game->SetBuildType(BuildType::ENERGYCELL);
	if (is4Pressed)
		m_Game->SetBuildType(BuildType::MARKETTENTADVENCED);

	m_Camera->TickUpdate();

	// Render the graphics scene.
	result = Render(rotation, mouseState, frameTime, isIPressed, isEPressed);
	if(!result)
	{
		return false;
	}

	// Title Scene
	if (m_Game->GetSceneType() == SceneType::TITLE)
	{
		m_Sound->StopWaveFile(0);
		m_Sound->StopWaveFile(5);
		if (m_Sound->isTitleBGMStart)
			result = m_Sound->PlayWaveFile(4, true, /*-1500*/ -500);;
		m_Sound->isTitleBGMStart = false;
	}
	// Main Scene 1
	else if (m_Game->GetSceneType() == SceneType::MAIN1)
	{
		m_Sound->StopWaveFile(4);
		m_Sound->StopWaveFile(5);
		if (m_Sound->isMainBGMStart)
			result = m_Sound->PlayWaveFile(0, true, /*-1500*/ -300);;
		m_Sound->isMainBGMStart = false;
	}
	// Ending Scene
	else if (m_Game->GetSceneType() == SceneType::ENDING)
	{
		m_Sound->StopWaveFile(0);
		m_Sound->StopWaveFile(4);
		if (m_Sound->isEndingBGMStart)
			result = m_Sound->PlayWaveFile(5, true, /*-1500*/ -300);;
		m_Sound->isEndingBGMStart = false;
	}

	return true;
}


bool GraphicsClass::Render(float rotation, DIMOUSESTATE mouseState, float frameTime, bool isIPressed, bool isEPressed)
{
	D3DXMATRIX worldMatrix[MAXMODELNUM + 50], viewMatrix, projectionMatrix, translateMatrix, scaleMatrix;
	D3DXMATRIX insWorld[100];
	D3DXMATRIX bitmapWorld[BITMAPNUM];
	D3DXMATRIX orthoMatrix;
	D3DXVECTOR4 diffuseColor[1];
	D3DXVECTOR4 lightPosition[1];
	bool result;

	// Create the diffuse color array from the four light colors. (pointlight)
	diffuseColor[0] = m_PointLight0->GetDiffuseColor();

	// Create the light position array from the four light positions. (pointlight)
	lightPosition[0] = m_PointLight0->GetPosition();

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	///////////////////
	// CREATE SKYBOX //
	///////////////////

	D3DXMATRIX sphereWorld;
	D3DXMATRIX Scale;
	D3DXMATRIX Translation;

	D3DXMATRIX viewMatrixTmp;
	D3DXMATRIX projectionMatrixTmp;

	//Reset sphereWorld
	D3DXMatrixIdentity(&sphereWorld);
	//Define sphereWorld's world space matrix
	D3DXMatrixScaling(&Scale, 5.0f, 5.0f, 5.0f);
	//Make sure the sphere is always centered around camera
	D3DXMatrixTranslation(&Translation, m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z);
	//Set sphereWorld's world space using the transformations
	sphereWorld = Scale * Translation;

	m_Camera->GetViewMatrix(viewMatrixTmp);
	m_D3D->GetProjectionMatrix(projectionMatrixTmp);

	// return Cullmode from D3D11_CULL_NONE to D3D11_CULL_BACK
	m_Skybox->RenderSkyboxShader(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), sphereWorld, (D3DXMATRIX)viewMatrixTmp, (D3DXMATRIX)projectionMatrixTmp);
	D3D11_RASTERIZER_DESC rasterDesc;
	ID3D11RasterizerState* RSCullBack;
	ZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterDesc.CullMode = D3D11_CULL_BACK;
	m_D3D->GetDevice()->CreateRasterizerState(&rasterDesc, &RSCullBack);


	/////////////////////
	// RENDER MD5MODEL //
	/////////////////////

	//////////////////
	// Nuclear Suit //
	//////////////////

	D3DXMATRIX md5World;
	D3DXVECTOR3 trans;

	m_D3D->GetWorldMatrix(md5World);
	D3DXVec3Scale
	(
		&trans,
		&D3DXVECTOR3
		(
			m_Camera->GetLookAtVector().x * 10.0f,
			m_Camera->GetLookAtVector().y * 10.0f,
			m_Camera->GetLookAtVector().z * 10.0f
		),
		10.0f
	);

	m_charPos = trans;

	D3DXVec3Add(&trans, &m_Camera->GetPosition(), &trans);
	D3DXMatrixRotationY(&md5World, m_charRot.y + 180.0f * 0.0174532925f);
	D3DXMatrixTranslation(&translateMatrix, trans.x, 20.0f, trans.z);
	D3DXMatrixMultiply(&md5World, &md5World, &translateMatrix);

	m_Md5Model->DrawMd5Model(m_D3D->GetDeviceContext(), md5World, viewMatrix, projectionMatrix);

	//////////////////
	// MAIN SCENE 1 //
	//////////////////

	if (m_Game->GetSceneType() == SceneType::MAIN1)
	{

		///////////////////////
		// MODEL POSITIONING //
		///////////////////////

		///////////
		// Floor //
		///////////

		// Floor
		m_D3D->GetWorldMatrix(worldMatrix[0]);
		D3DXMatrixRotationY(&worldMatrix[0], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[0], &worldMatrix[0], &translateMatrix);
		m_Model[0]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[0]->GetIndexCount(), worldMatrix[0], viewMatrix, projectionMatrix,
			m_Model[0]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		/////////////////
		// Environment //
		/////////////////

		// Rock1
		m_D3D->GetWorldMatrix(worldMatrix[1]);
		D3DXMatrixRotationY(&worldMatrix[1], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[1], &worldMatrix[1], &translateMatrix);
		m_Model[1]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[1]->GetIndexCount(), worldMatrix[1], viewMatrix, projectionMatrix,
			m_Model[1]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		// Rock2
		m_D3D->GetWorldMatrix(worldMatrix[2]);
		D3DXMatrixRotationY(&worldMatrix[2], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[2], &worldMatrix[2], &translateMatrix);
		m_Model[2]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[2]->GetIndexCount(), worldMatrix[2], viewMatrix, projectionMatrix,
			m_Model[2]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		// Rock3
		m_D3D->GetWorldMatrix(worldMatrix[3]);
		D3DXMatrixRotationY(&worldMatrix[3], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[3], &worldMatrix[3], &translateMatrix);
		m_Model[3]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[3]->GetIndexCount(), worldMatrix[3], viewMatrix, projectionMatrix,
			m_Model[3]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		// Rock4
		m_D3D->GetWorldMatrix(worldMatrix[4]);
		D3DXMatrixRotationY(&worldMatrix[4], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[4], &worldMatrix[4], &translateMatrix);
		m_Model[4]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[4]->GetIndexCount(), worldMatrix[4], viewMatrix, projectionMatrix,
			m_Model[4]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		// Rock5
		m_D3D->GetWorldMatrix(worldMatrix[5]);
		D3DXMatrixRotationY(&worldMatrix[5], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[5], &worldMatrix[5], &translateMatrix);
		m_Model[5]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[5]->GetIndexCount(), worldMatrix[5], viewMatrix, projectionMatrix,
			m_Model[5]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		// Rock6
		m_D3D->GetWorldMatrix(worldMatrix[6]);
		D3DXMatrixRotationY(&worldMatrix[6], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[6], &worldMatrix[6], &translateMatrix);
		m_Model[6]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[6]->GetIndexCount(), worldMatrix[6], viewMatrix, projectionMatrix,
			m_Model[6]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		// Tree1
		m_D3D->GetWorldMatrix(worldMatrix[7]);
		D3DXMatrixRotationY(&worldMatrix[7], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[7], &worldMatrix[7], &translateMatrix);
		m_Model[7]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[7]->GetIndexCount(), worldMatrix[7], viewMatrix, projectionMatrix,
			m_Model[7]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		// PineTree1
		m_D3D->GetWorldMatrix(worldMatrix[8]);
		D3DXMatrixRotationY(&worldMatrix[8], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[8], &worldMatrix[8], &translateMatrix);
		m_Model[8]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[8]->GetIndexCount(), worldMatrix[8], viewMatrix, projectionMatrix,
			m_Model[8]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		// PineTree2
		m_D3D->GetWorldMatrix(worldMatrix[9]);
		D3DXMatrixRotationY(&worldMatrix[9], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[9], &worldMatrix[9], &translateMatrix);
		m_Model[9]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[9]->GetIndexCount(), worldMatrix[9], viewMatrix, projectionMatrix,
			m_Model[9]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		// PineTree3
		m_D3D->GetWorldMatrix(worldMatrix[10]);
		D3DXMatrixRotationY(&worldMatrix[10], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[10], &worldMatrix[10], &translateMatrix);
		m_Model[10]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[10]->GetIndexCount(), worldMatrix[10], viewMatrix, projectionMatrix,
			m_Model[10]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		// RoseBush1
		m_D3D->GetWorldMatrix(worldMatrix[11]);
		D3DXMatrixRotationY(&worldMatrix[11], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[11], &worldMatrix[11], &translateMatrix);
		m_Model[11]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[11]->GetIndexCount(), worldMatrix[11], viewMatrix, projectionMatrix,
			m_Model[11]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		// RoseBush2
		m_D3D->GetWorldMatrix(worldMatrix[12]);
		D3DXMatrixRotationY(&worldMatrix[12], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[12], &worldMatrix[12], &translateMatrix);
		m_Model[12]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[12]->GetIndexCount(), worldMatrix[12], viewMatrix, projectionMatrix,
			m_Model[12]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		// Weeds
		m_D3D->GetWorldMatrix(worldMatrix[13]);
		D3DXMatrixRotationY(&worldMatrix[13], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[13], &worldMatrix[13], &translateMatrix);
		m_Model[13]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[13]->GetIndexCount(), worldMatrix[13], viewMatrix, projectionMatrix,
			m_Model[13]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		// Mushrooms
		m_D3D->GetWorldMatrix(worldMatrix[14]);
		D3DXMatrixRotationY(&worldMatrix[14], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[14], &worldMatrix[14], &translateMatrix);
		m_Model[14]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[14]->GetIndexCount(), worldMatrix[14], viewMatrix, projectionMatrix,
			m_Model[14]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}


		//////////////////
		// Looting Gems //
		//////////////////

		// Emerald1
		m_D3D->GetWorldMatrix(worldMatrix[15]);
		D3DXMatrixRotationY(&worldMatrix[15], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[15], &worldMatrix[15], &translateMatrix);

		if (m_isLootModelRender[0])
		{
			m_Model[15]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[15]->GetIndexCount(), worldMatrix[15], viewMatrix, projectionMatrix,
				m_Model[15]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}

		// Emerald2
		m_D3D->GetWorldMatrix(worldMatrix[16]);
		D3DXMatrixRotationY(&worldMatrix[16], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[16], &worldMatrix[16], &translateMatrix);

		if (m_isLootModelRender[1])
		{
			m_Model[16]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[16]->GetIndexCount(), worldMatrix[16], viewMatrix, projectionMatrix,
				m_Model[16]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}

		// Emerald3
		m_D3D->GetWorldMatrix(worldMatrix[17]);
		D3DXMatrixRotationY(&worldMatrix[17], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[17], &worldMatrix[17], &translateMatrix);

		if (m_isLootModelRender[2])
		{
			m_Model[17]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[17]->GetIndexCount(), worldMatrix[17], viewMatrix, projectionMatrix,
				m_Model[17]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}

		// Ruby1
		m_D3D->GetWorldMatrix(worldMatrix[18]);
		D3DXMatrixRotationY(&worldMatrix[18], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[18], &worldMatrix[18], &translateMatrix);

		if (m_isLootModelRender[3])
		{
			m_Model[18]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[18]->GetIndexCount(), worldMatrix[18], viewMatrix, projectionMatrix,
				m_Model[18]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}

		// Ruby2
		m_D3D->GetWorldMatrix(worldMatrix[19]);
		D3DXMatrixRotationY(&worldMatrix[19], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[19], &worldMatrix[19], &translateMatrix);

		if (m_isLootModelRender[4])
		{
			m_Model[19]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[19]->GetIndexCount(), worldMatrix[19], viewMatrix, projectionMatrix,
				m_Model[19]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}

		// Ruby3
		m_D3D->GetWorldMatrix(worldMatrix[20]);
		D3DXMatrixRotationY(&worldMatrix[20], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[20], &worldMatrix[20], &translateMatrix);

		if (m_isLootModelRender[5])
		{
			m_Model[20]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[20]->GetIndexCount(), worldMatrix[20], viewMatrix, projectionMatrix,
				m_Model[20]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}

		// Sapphire1
		m_D3D->GetWorldMatrix(worldMatrix[21]);
		D3DXMatrixRotationY(&worldMatrix[21], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[21], &worldMatrix[21], &translateMatrix);

		if (m_isLootModelRender[6])
		{
			m_Model[21]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[21]->GetIndexCount(), worldMatrix[21], viewMatrix, projectionMatrix,
				m_Model[21]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}

		// Sapphire2
		m_D3D->GetWorldMatrix(worldMatrix[22]);
		D3DXMatrixRotationY(&worldMatrix[22], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[22], &worldMatrix[22], &translateMatrix);

		if (m_isLootModelRender[7])
		{
			m_Model[22]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[22]->GetIndexCount(), worldMatrix[22], viewMatrix, projectionMatrix,
				m_Model[22]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}

		// Sapphire3
		m_D3D->GetWorldMatrix(worldMatrix[23]);
		D3DXMatrixRotationY(&worldMatrix[23], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[23], &worldMatrix[23], &translateMatrix);

		if (m_isLootModelRender[8])
		{
			m_Model[23]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[23]->GetIndexCount(), worldMatrix[23], viewMatrix, projectionMatrix,
				m_Model[23]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}

		// Amethyst1
		m_D3D->GetWorldMatrix(worldMatrix[24]);
		D3DXMatrixRotationY(&worldMatrix[24], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[24], &worldMatrix[24], &translateMatrix);

		if (m_isLootModelRender[9])
		{
			m_Model[24]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[24]->GetIndexCount(), worldMatrix[24], viewMatrix, projectionMatrix,
				m_Model[24]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}

		// Amethyst2
		m_D3D->GetWorldMatrix(worldMatrix[25]);
		D3DXMatrixRotationY(&worldMatrix[25], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[25], &worldMatrix[25], &translateMatrix);

		if (m_isLootModelRender[10])
		{
			m_Model[25]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[25]->GetIndexCount(), worldMatrix[25], viewMatrix, projectionMatrix,
				m_Model[25]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}

		// Amethyst3
		m_D3D->GetWorldMatrix(worldMatrix[26]);
		D3DXMatrixRotationY(&worldMatrix[26], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[26], &worldMatrix[26], &translateMatrix);

		if (m_isLootModelRender[11])
		{
			m_Model[26]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[26]->GetIndexCount(), worldMatrix[26], viewMatrix, projectionMatrix,
				m_Model[26]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}

		for (int i = 15; i < 15 + LOOTINGMODELNUM; i++)
		{
			if (
				CollisionClass::BoundingBoxCollision
				(
					m_Md5Model->GetBoundingBoxMin(),
					m_Md5Model->GetBoundingBoxMax(),
					m_Model[i]->GetBoundingBoxMin(),
					m_Model[i]->GetBoundingBoxMax(),
					m_Model[i]->GetColCheckEnabled()
				)
				)
			{
				m_obj -= 1;
				m_poly -= 288;

				if (i >= 15 && i <= 17)
					m_Game->IncEmeralCnt();
				if (i >= 18 && i <= 20)
					m_Game->IncRubyCnt();
				if (i >= 21 && i <= 23)
					m_Game->IncSapphCnt();
				if (i >= 24 && i <= 26)
					m_Game->IncAmethCnt();

				m_isLootModelRender[i - 15] = false;
				m_Model[i]->SetColCheckEnabled(false);
				m_Sound->PlayWaveFile(3, false);
			}
		}


		////////////////////
		// Visual Effects //
		////////////////////

		D3DXVECTOR3 scrollSpeeds, scales;
		D3DXVECTOR2 distortion1, distortion2, distortion3;
		float distortionScale, distortionBias;

		scrollSpeeds = D3DXVECTOR3(1.3f, 2.1f, 2.3f);
		scales = D3DXVECTOR3(1.0f, 2.0f, 3.0f);

		distortion1 = D3DXVECTOR2(0.1f, 0.2f);
		distortion2 = D3DXVECTOR2(0.1f, 0.3f);
		distortion3 = D3DXVECTOR2(0.1f, 0.1f);

		distortionScale = 0.8f;
		distortionBias = 0.5f;

		m_D3D->TurnOnAlphaBlending();

		// Fire
		m_D3D->GetWorldMatrix(worldMatrix[28]);
		/*D3DXMatrixRotationY(&worldMatrix, rotation);*/
		D3DXMatrixTranslation(&translateMatrix, 1500.0f, 5484.0f, 2000.0f);
		D3DXMatrixMultiply(&worldMatrix[28], &worldMatrix[28], &translateMatrix);
		D3DXMatrixScaling(&scaleMatrix, 0.1f, 0.1f, 0.1f);
		D3DXMatrixMultiply(&worldMatrix[28], &worldMatrix[28], &scaleMatrix);

		m_Model[28]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderFireTextureShader(m_D3D->GetDeviceContext(), m_Model[28]->GetIndexCount(), worldMatrix[28], viewMatrix, projectionMatrix,
			m_Model[28]->GetTexture1(), m_Model[28]->GetTexture2(), m_Model[28]->GetTexture3(), frameTime, scrollSpeeds,
			scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
		if (!result)
		{
			return false;
		}

		// Portal Blue
		m_D3D->GetWorldMatrix(worldMatrix[29]);
		/*D3DXMatrixRotationY(&worldMatrix, rotation);*/
		D3DXMatrixTranslation(&translateMatrix, -1500.0f, 5484.0f, 1500.0f);
		D3DXMatrixMultiply(&worldMatrix[29], &worldMatrix[29], &translateMatrix);
		D3DXMatrixScaling(&scaleMatrix, 0.1f, 0.1f, 0.1f);
		D3DXMatrixMultiply(&worldMatrix[29], &worldMatrix[29], &scaleMatrix);

		m_Model[29]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderFireTextureShader(m_D3D->GetDeviceContext(), m_Model[29]->GetIndexCount(), worldMatrix[29], viewMatrix, projectionMatrix,
			m_Model[29]->GetTexture1(), m_Model[29]->GetTexture2(), m_Model[29]->GetTexture3(), frameTime, scrollSpeeds,
			scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
		if (!result)
		{
			return false;
		}

		// Portal Red
		m_D3D->GetWorldMatrix(worldMatrix[30]);
		/*D3DXMatrixRotationY(&worldMatrix, rotation);*/
		D3DXMatrixTranslation(&translateMatrix, 3500.0f, 5484.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[30], &worldMatrix[30], &translateMatrix);
		D3DXMatrixScaling(&scaleMatrix, 0.1f, 0.1f, 0.1f);
		D3DXMatrixMultiply(&worldMatrix[30], &worldMatrix[30], &scaleMatrix);

		m_Model[30]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderFireTextureShader(m_D3D->GetDeviceContext(), m_Model[30]->GetIndexCount(), worldMatrix[30], viewMatrix, projectionMatrix,
			m_Model[30]->GetTexture1(), m_Model[30]->GetTexture2(), m_Model[30]->GetTexture3(), frameTime, scrollSpeeds,
			scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
		if (!result)
		{
			return false;
		}

		m_D3D->TurnOffAlphaBlending();


		////////////////////////////
		//// Runtime Instance Obj //
		////////////////////////////

		////////////////
		// SciFiCrate //
		////////////////

		if (mouseState.rgbButtons[0] && !isLClicked && m_Game->GetBuildType() == BuildType::SCFICRATE)
		{
			if (m_Game->AbleToConstruct(1))
			{
				m_Game->ConstructCrate();

				isLClicked = true;
				m_constructAnimTrigger = true;

				m_obj += 1;
				m_poly += 184;

				m_Sound->PlayWaveFile(1, false, -200);

				D3DXVECTOR3 tmpInsPos;
				D3DXVECTOR3 transVec;
				D3DXVec3Scale
				(
					&transVec,
					&D3DXVECTOR3
					(
						m_Camera->GetLookAtVector().x * 10.0f,
						m_Camera->GetLookAtVector().y * 10.0f,
						m_Camera->GetLookAtVector().z * 10.0f
					),
					15.0f
				);

				D3DXVec3Add(&tmpInsPos, &m_Camera->GetPosition(), &transVec);

				/*insPos.push_back(m_Raycast->doRaycast(m_hwnd, m_Model[0]->getVertices(), m_Model[0]->getIndices(), worldMatrix[1], projectionMatrix, viewMatrix));*/
				insPos.push_back(tmpInsPos);
				insRot.push_back(m_charRot.y);
				//insRot.push_back(m_Camera->GetLookAtVector().y);
			}
		}

		if (mouseState.rgbButtons[1] && !isRClicked && !insPos.empty())
		{
			m_Game->DestructCrate();

			isRClicked = true;
			m_constructAnimTrigger = true;

			m_obj -= 1;
			m_poly -= 184;

			m_Sound->PlayWaveFile(2, false, -200);

			if (!insPos.empty())
				insPos.pop_back();
			if (!insRot.empty())
				insRot.pop_back();
		}

		if (m_constructAnimTrigger)
		{
			m_animTimeStack += frameTime * 0.005f;

			if (m_animTimeStack < m_Md5Model->getTotalAnimTime(1))
				AnimCharConstruct(frameTime);

			if (m_animTimeStack >= m_Md5Model->getTotalAnimTime(1))
			{
				m_animTimeStack = 0.0f;
				m_constructAnimTrigger = false;
			}
		}

		if (!mouseState.rgbButtons[0])
		{
			isLClicked = false;
		}

		if (!mouseState.rgbButtons[1])
		{
			isRClicked = false;
		}

		for (int i = 0; i < insPos.size(); i++)
		{
			m_D3D->GetWorldMatrix(insWorld[i]);
			D3DXMatrixRotationY(&insWorld[i], insRot[i]);
			//D3DXMatrixScaling(&scaleMatrix, 1.0f, 1.0f, 1.0f);
			//D3DXMatrixMultiply(&insMatrix, &insMatrix, &scaleMatrix);
			D3DXMatrixTranslation(&translateMatrix, insPos[i].x, /*insPos[i].y*/ 1.0f, insPos[i].z);
			D3DXMatrixMultiply(&insWorld[i], &insWorld[i], &translateMatrix);

			//m_Md5Model->MakeAABB((XMMATRIX)insWorld[i]);

			m_Model[27]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[27]->GetIndexCount(), insWorld[i], viewMatrix, projectionMatrix,
				m_Model[27]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}
	}


	//////////////////
	// MAIN SCENE 2 //
	//////////////////

	if (m_Game->GetSceneType() == SceneType::MAIN2)
	{
		if (mouseState.rgbButtons[1] && cactusCollision1 && !isRClicked)
		{
			isRClicked = true;
			m_Sound->PlayWaveFile(2, false);
			m_constructAnimTrigger = true;
			m_Game->IncExtractCnt(1);

			/*if(m_Game->GetExtractCnt(1) >= 3)
				cactusTF1 = false;*/
			palmTreeExTF1 = false;
			woodStackTF1 = true;
			m_Model[48]->SetColCheckEnabled(true);
			m_Model[31]->SetColCheckEnabled(false);
			m_Model[45]->SetColCheckEnabled(false);
		}

		if (mouseState.rgbButtons[1] && cactusCollision2 && !isRClicked)
		{
			isRClicked = true;
			m_Sound->PlayWaveFile(2, false);
			m_constructAnimTrigger = true;
			palmTreeExTF2 = false;
			m_Game->IncExtractCnt(2);

			/*if (m_Game->GetExtractCnt(2) >= 3)
				cactusTF2 = false;*/
			palmTreeExTF2 = false;
			woodStackTF2 = true;
			m_Model[49]->SetColCheckEnabled(true);
			m_Model[32]->SetColCheckEnabled(false);
			m_Model[46]->SetColCheckEnabled(false);
		}

		if (mouseState.rgbButtons[1] && cactusCollision3 && !isRClicked)
		{
			isRClicked = true;
			m_Sound->PlayWaveFile(2, false);
			m_constructAnimTrigger = true;
			palmTreeExTF3 = false;
			m_Game->IncExtractCnt(3);

			/*if (m_Game->GetExtractCnt(3) >= 3)
				cactusTF3 = false;*/
			palmTreeExTF3 = false;
			woodStackTF3 = true;
			m_Model[50]->SetColCheckEnabled(true);
			m_Model[33]->SetColCheckEnabled(false);
			m_Model[47]->SetColCheckEnabled(false);
		}

		if (m_constructAnimTrigger)
		{
			m_animTimeStack += frameTime * 0.005f;

			if (m_animTimeStack < m_Md5Model->getTotalAnimTime(1))
				AnimCharConstruct(frameTime);

			if (m_animTimeStack >= m_Md5Model->getTotalAnimTime(1))
			{
				m_animTimeStack = 0.0f;
				m_constructAnimTrigger = false;
			}
		}

		if (!mouseState.rgbButtons[1])
		{
			isRClicked = false;
		}

		if (palmTreeExTF1)
		{
			m_D3D->GetWorldMatrix(worldMatrix[51]);
			D3DXMatrixRotationY(&worldMatrix[51], 0.0f);
			D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
			D3DXMatrixMultiply(&worldMatrix[51], &worldMatrix[51], &translateMatrix);
			m_Model[31]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[31]->GetIndexCount(), worldMatrix[51], viewMatrix, projectionMatrix,
				m_Model[31]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}
		
		if (palmTreeExTF2)
		{
			m_D3D->GetWorldMatrix(worldMatrix[52]);
			D3DXMatrixRotationY(&worldMatrix[52], 0.0f);
			D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
			D3DXMatrixMultiply(&worldMatrix[52], &worldMatrix[52], &translateMatrix);
			m_Model[32]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[32]->GetIndexCount(), worldMatrix[52], viewMatrix, projectionMatrix,
				m_Model[32]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}
		
		if (palmTreeExTF3)
		{
			m_D3D->GetWorldMatrix(worldMatrix[53]);
			D3DXMatrixRotationY(&worldMatrix[53], 0.0f);
			D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
			D3DXMatrixMultiply(&worldMatrix[53], &worldMatrix[53], &translateMatrix);
			m_Model[33]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[33]->GetIndexCount(), worldMatrix[53], viewMatrix, projectionMatrix,
				m_Model[33]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}

		if (!palmTreeExTF1 && woodStackTF1)
		{
			m_D3D->GetWorldMatrix(worldMatrix[54]);
			D3DXMatrixRotationY(&worldMatrix[54], 0.0f);
			D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
			D3DXMatrixMultiply(&worldMatrix[54], &worldMatrix[54], &translateMatrix);
			m_Model[48]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[48]->GetIndexCount(), worldMatrix[54], viewMatrix, projectionMatrix,
				m_Model[48]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}

		if (!palmTreeExTF2 && woodStackTF2)
		{
			m_D3D->GetWorldMatrix(worldMatrix[55]);
			D3DXMatrixRotationY(&worldMatrix[55], 0.0f);
			D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
			D3DXMatrixMultiply(&worldMatrix[55], &worldMatrix[55], &translateMatrix);
			m_Model[49]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[49]->GetIndexCount(), worldMatrix[55], viewMatrix, projectionMatrix,
				m_Model[49]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}

		if (!palmTreeExTF3 && woodStackTF3)
		{
			m_D3D->GetWorldMatrix(worldMatrix[56]);
			D3DXMatrixRotationY(&worldMatrix[56], 0.0f);
			D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
			D3DXMatrixMultiply(&worldMatrix[56], &worldMatrix[56], &translateMatrix);
			m_Model[50]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[50]->GetIndexCount(), worldMatrix[56], viewMatrix, projectionMatrix,
				m_Model[50]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}
		
		for (int i = 34; i <= 43; i++)
		{
			m_D3D->GetWorldMatrix(worldMatrix[i]);
			D3DXMatrixRotationY(&worldMatrix[i], 0.0f);
			D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
			D3DXMatrixMultiply(&worldMatrix[i], &worldMatrix[i], &translateMatrix);
			m_Model[i]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[i]->GetIndexCount(), worldMatrix[i], viewMatrix, projectionMatrix,
				m_Model[i]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}

		m_D3D->GetWorldMatrix(worldMatrix[44]);
		D3DXMatrixRotationY(&worldMatrix[44], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[44], &worldMatrix[44], &translateMatrix);
		m_Model[44]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[44]->GetIndexCount(), worldMatrix[44], viewMatrix, projectionMatrix,
			m_Model[44]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		// Rock1
		m_D3D->GetWorldMatrix(worldMatrix[45]);
		D3DXMatrixRotationY(&worldMatrix[45], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[45], &worldMatrix[45], &translateMatrix);
		m_Model[1]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[1]->GetIndexCount(), worldMatrix[45], viewMatrix, projectionMatrix,
			m_Model[1]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		// Rock2
		m_D3D->GetWorldMatrix(worldMatrix[46]);
		D3DXMatrixRotationY(&worldMatrix[46], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[46], &worldMatrix[46], &translateMatrix);
		m_Model[2]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[2]->GetIndexCount(), worldMatrix[46], viewMatrix, projectionMatrix,
			m_Model[2]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		// Rock3
		m_D3D->GetWorldMatrix(worldMatrix[47]);
		D3DXMatrixRotationY(&worldMatrix[47], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[47], &worldMatrix[47], &translateMatrix);
		m_Model[3]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[3]->GetIndexCount(), worldMatrix[47], viewMatrix, projectionMatrix,
			m_Model[3]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		// Rock4
		m_D3D->GetWorldMatrix(worldMatrix[48]);
		D3DXMatrixRotationY(&worldMatrix[48], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[48], &worldMatrix[48], &translateMatrix);
		m_Model[4]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[4]->GetIndexCount(), worldMatrix[48], viewMatrix, projectionMatrix,
			m_Model[4]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		// Rock5
		m_D3D->GetWorldMatrix(worldMatrix[49]);
		D3DXMatrixRotationY(&worldMatrix[49], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[49], &worldMatrix[49], &translateMatrix);
		m_Model[5]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[5]->GetIndexCount(), worldMatrix[49], viewMatrix, projectionMatrix,
			m_Model[5]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		// Rock6
		m_D3D->GetWorldMatrix(worldMatrix[50]);
		D3DXMatrixRotationY(&worldMatrix[50], 0.0f);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix[50], &worldMatrix[50], &translateMatrix);
		m_Model[6]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[6]->GetIndexCount(), worldMatrix[50], viewMatrix, projectionMatrix,
			m_Model[6]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
		if (!result)
		{
			return false;
		}


		////////////////////////////
		//// Runtime Instance Obj //
		////////////////////////////

		/////////////////
		// Market Tent //
		/////////////////

		if (mouseState.rgbButtons[0] && !isLClicked && m_Game->GetBuildType() == BuildType::MARKETTENT && !cactusCollision1 && !cactusCollision2 && !cactusCollision3)
		{
			if (m_Game->AbleToConstruct(2))
			{
				m_Game->ConstructMarketTent();

				isLClicked = true;
				m_constructAnimTrigger = true;

				m_obj += 1;
				m_poly += 456;

				m_Sound->PlayWaveFile(1, false, -200);

				D3DXVECTOR3 tmpInsPos;
				D3DXVECTOR3 transVec;
				D3DXVec3Scale
				(
					&transVec,
					&D3DXVECTOR3
					(
						m_Camera->GetLookAtVector().x * 10.0f,
						m_Camera->GetLookAtVector().y * 10.0f,
						m_Camera->GetLookAtVector().z * 10.0f
					),
					25.0f
				);

				D3DXVec3Add(&tmpInsPos, &m_Camera->GetPosition(), &transVec);

				/*insPos.push_back(m_Raycast->doRaycast(m_hwnd, m_Model[0]->getVertices(), m_Model[0]->getIndices(), worldMatrix[1], projectionMatrix, viewMatrix));*/
				insPos.push_back(tmpInsPos);
				insRot.push_back(m_charRot.y);
				//insRot.push_back(m_Camera->GetLookAtVector().y);
			}
		}

		if (mouseState.rgbButtons[1] && !isRClicked && !insPos.empty() && !cactusCollision1 && !cactusCollision2 && !cactusCollision3)
		{
			m_Game->DestructTent();

			isRClicked = true;
			m_constructAnimTrigger = true;

			m_obj -= 1;
			m_poly -= 184;

			m_Sound->PlayWaveFile(2, false, -200);

			if (!insPos.empty())
				insPos.pop_back();
			if (!insRot.empty())
				insRot.pop_back();
		}

		if (!mouseState.rgbButtons[0])
		{
			isLClicked = false;
		}

		if (!mouseState.rgbButtons[1])
		{
			isRClicked = false;
		}

		for (int i = 0; i < insPos.size(); i++)
		{
			m_D3D->GetWorldMatrix(insWorld[i]);
			D3DXMatrixRotationY(&insWorld[i], insRot[i]);
			//D3DXMatrixScaling(&scaleMatrix, 1.0f, 1.0f, 1.0f);
			//D3DXMatrixMultiply(&insMatrix, &insMatrix, &scaleMatrix);
			D3DXMatrixTranslation(&translateMatrix, insPos[i].x, /*insPos[i].y*/ 1.0f, insPos[i].z);
			D3DXMatrixMultiply(&insWorld[i], &insWorld[i], &translateMatrix);

			//m_Md5Model->MakeAABB((XMMATRIX)insWorld[i]);

			m_Model[51]->Render(m_D3D->GetDeviceContext());
			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model[51]->GetIndexCount(), insWorld[i], viewMatrix, projectionMatrix,
				m_Model[51]->GetTexture(), m_Light[0]->GetDirection(), m_Light[0]->GetAmbientColor(), m_Light[0]->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light[0]->GetSpecularColor(), m_Light[0]->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}
	}


	//////////////////////
	// Bitmap Rendering //
	//////////////////////

	for(int i = 0; i < BITMAPNUM; i++)
		m_D3D->GetWorldMatrix(bitmapWorld[i]);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();


	//////////////////////////
	//// Popup UI Rendering //
	//////////////////////////

	if (m_Game->GetSceneType() == SceneType::MAIN1 || m_Game->GetSceneType() == SceneType::MAIN2)
	{
		// Inventory
		if (isIPressed && !isIOn)
		{
			isIOn = true;

			if (tfI)
				tfI = false;
			else
				tfI = true;
		}

		if (tfI)
		{
			// Put the bitmap(World Maker Ending img.png) vertex and index buffers on the graphics pipeline to prepare them for drawing.
			result = m_Bitmap[7]->Render(m_D3D->GetDeviceContext(), 523, 93);
			if (!result)
			{
				return false;
			}

			// Render the bitmap(World Maker Ending img.png) with the texture shader.
			result = m_BitmapShader->Render(m_D3D->GetDeviceContext(), m_Bitmap[7]->GetIndexCount(), bitmapWorld[7], m_BaseViewMatrix, orthoMatrix, m_Bitmap[7]->GetTexture());
			if (!result)
			{
				return false;
			}
		}

		if (!isIPressed)
			isIOn = false;


		// BuildMenu
		if (isEPressed && !isEOn)
		{
			isEOn = true;

			if (tfE)
				tfE = false;
			else
				tfE = true;
		}

		if (tfE)
		{
			// Put the bitmap(UI Build Menu2.png) vertex and index buffers on the graphics pipeline to prepare them for drawing.
			result = m_Bitmap[9]->Render(m_D3D->GetDeviceContext(), 0, 183);
			if (!result)
			{
				return false;
			}

			// Render the bitmap(UI Build Menu2.png) with the texture shader.
			result = m_BitmapShader->Render(m_D3D->GetDeviceContext(), m_Bitmap[9]->GetIndexCount(), bitmapWorld[9], m_BaseViewMatrix, orthoMatrix, m_Bitmap[9]->GetTexture());
			if (!result)
			{
				return false;
			}
		}

		if (!isEPressed)
			isEOn = false;
	}


	///////////////////
	// Main Stage UI //
	///////////////////

	if (m_Game->GetSceneType() == SceneType::MAIN1 || m_Game->GetSceneType() == SceneType::MAIN2)
	{
		if (m_Game->GetBuildType() == BuildType::SCFICRATE)
		{
			// Put the bitmap(UI Construction container SciFi crate.png) vertex and index buffers on the graphics pipeline to prepare them for drawing.
			result = m_Bitmap[0]->Render(m_D3D->GetDeviceContext(), 0, 661);
			if (!result)
			{
				return false;
			}

			// Render the bitmap(UI Construction container SciFi crate.png) with the texture shader.
			result = m_BitmapShader->Render(m_D3D->GetDeviceContext(), m_Bitmap[0]->GetIndexCount(), bitmapWorld[0], m_BaseViewMatrix, orthoMatrix, m_Bitmap[0]->GetTexture());
			if (!result)
			{
				return false;
			}
		}

		if (m_Game->GetBuildType() == BuildType::MARKETTENT)
		{
			// Put the bitmap(UI Construction container SciFi crate.png) vertex and index buffers on the graphics pipeline to prepare them for drawing.
			result = m_Bitmap[10]->Render(m_D3D->GetDeviceContext(), 0, 661);
			if (!result)
			{
				return false;
			}

			// Render the bitmap(UI Construction container SciFi crate.png) with the texture shader.
			result = m_BitmapShader->Render(m_D3D->GetDeviceContext(), m_Bitmap[10]->GetIndexCount(), bitmapWorld[10], m_BaseViewMatrix, orthoMatrix, m_Bitmap[10]->GetTexture());
			if (!result)
			{
				return false;
			}
		}

		if (m_Game->GetBuildType() == BuildType::ENERGYCELL)
		{
			// Put the bitmap(UI Construction container SciFi crate.png) vertex and index buffers on the graphics pipeline to prepare them for drawing.
			result = m_Bitmap[11]->Render(m_D3D->GetDeviceContext(), 0, 661);
			if (!result)
			{
				return false;
			}

			// Render the bitmap(UI Construction container SciFi crate.png) with the texture shader.
			result = m_BitmapShader->Render(m_D3D->GetDeviceContext(), m_Bitmap[11]->GetIndexCount(), bitmapWorld[11], m_BaseViewMatrix, orthoMatrix, m_Bitmap[11]->GetTexture());
			if (!result)
			{
				return false;
			}
		}

		if (m_Game->GetBuildType() == BuildType::MARKETTENTADVENCED)
		{
			// Put the bitmap(UI Construction container SciFi crate.png) vertex and index buffers on the graphics pipeline to prepare them for drawing.
			result = m_Bitmap[12]->Render(m_D3D->GetDeviceContext(), 0, 661);
			if (!result)
			{
				return false;
			}

			// Render the bitmap(UI Construction container SciFi crate.png) with the texture shader.
			result = m_BitmapShader->Render(m_D3D->GetDeviceContext(), m_Bitmap[12]->GetIndexCount(), bitmapWorld[12], m_BaseViewMatrix, orthoMatrix, m_Bitmap[12]->GetTexture());
			if (!result)
			{
				return false;
			}
		}

		m_D3D->TurnOnAlphaBlending();

		// Put the bitmap(UI Inventory HUD with Jewels.png) vertex and index buffers on the graphics pipeline to prepare them for drawing.
		result = m_Bitmap[1]->Render(m_D3D->GetDeviceContext(), 497, 827);
		if (!result)
		{
			return false;
		}

		// Render the bitmap(UI Inventory HUD with Jewels.png) with the texture shader.
		result = m_BitmapShader->Render(m_D3D->GetDeviceContext(), m_Bitmap[1]->GetIndexCount(), bitmapWorld[1], m_BaseViewMatrix, orthoMatrix, m_Bitmap[1]->GetTexture());
		if (!result)
		{
			return false;
		}
	}

	if (m_Game->GetSceneType() == SceneType::MAIN1)
	{
		// Put the bitmap(Tutorial instruction resized.png) vertex and index buffers on the graphics pipeline to prepare them for drawing.
		result = m_Bitmap[5]->Render(m_D3D->GetDeviceContext(), 1070, 30);
		if (!result)
		{
			return false;
		}

		// Render the bitmap(Tutorial instruction resized.png) with the texture shader.
		result = m_BitmapShader->Render(m_D3D->GetDeviceContext(), m_Bitmap[5]->GetIndexCount(), bitmapWorld[5], m_BaseViewMatrix, orthoMatrix, m_Bitmap[5]->GetTexture());
		if (!result)
		{
			return false;
		}
	}

	if (m_Game->GetSceneType() == SceneType::MAIN2)
	{
		// Put the bitmap(Tutorial instruction resized.png) vertex and index buffers on the graphics pipeline to prepare them for drawing.
		result = m_Bitmap[8]->Render(m_D3D->GetDeviceContext(), 1070, 30);
		if (!result)
		{
			return false;
		}

		// Render the bitmap(Tutorial instruction resized.png) with the texture shader.
		result = m_BitmapShader->Render(m_D3D->GetDeviceContext(), m_Bitmap[8]->GetIndexCount(), bitmapWorld[8], m_BaseViewMatrix, orthoMatrix, m_Bitmap[8]->GetTexture());
		if (!result)
		{
			return false;
		}
	}

	if (m_Game->GetEmeralCnt() > 0 && m_Game->GetRubyCnt() > 0 && m_Game->GetSapphCnt() > 0 && m_Game->GetAmethCnt() > 0 && m_Game->GetBuildType() == BuildType::SCFICRATE)
	{
		// Put the bitmap(Exclamation mark resized.png) vertex and index buffers on the graphics pipeline to prepare them for drawing.
		result = m_Bitmap[6]->Render(m_D3D->GetDeviceContext(), 187, 631);
		if (!result)
		{
			return false;
		}

		// Render the bitmap(Exclamation mark resized.png) with the texture shader.
		result = m_BitmapShader->Render(m_D3D->GetDeviceContext(), m_Bitmap[6]->GetIndexCount(), bitmapWorld[6], m_BaseViewMatrix, orthoMatrix, m_Bitmap[6]->GetTexture());
		if (!result)
		{
			return false;
		}
	}

	else if (m_Game->GetWoodStackCnt() > 0 && m_Game->GetBuildType() == BuildType::MARKETTENT)
	{
		// Put the bitmap(Exclamation mark resized.png) vertex and index buffers on the graphics pipeline to prepare them for drawing.
		result = m_Bitmap[6]->Render(m_D3D->GetDeviceContext(), 187, 631);
		if (!result)
		{
			return false;
		}

		// Render the bitmap(Exclamation mark resized.png) with the texture shader.
		result = m_BitmapShader->Render(m_D3D->GetDeviceContext(), m_Bitmap[6]->GetIndexCount(), bitmapWorld[6], m_BaseViewMatrix, orthoMatrix, m_Bitmap[6]->GetTexture());
		if (!result)
		{
			return false;
		}
	}
	
	m_D3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();


	////////////////////
	// Text Rendering //
	////////////////////

	m_D3D->GetWorldMatrix(worldMatrix[57]);
	D3DXMatrixTranslation(&translateMatrix, 0.0f, 20.0f, 0.0f);
	D3DXMatrixMultiply(&worldMatrix[57], &worldMatrix[57], &translateMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();
	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix[57], orthoMatrix);
	if (!result)
	{
		return false;
	}


	/////////////////////
	// Scene Rendering //
	/////////////////////

	// Title Scene (SceneType TITLE)
	if (m_Game->GetSceneType() == SceneType::TITLE)
	{
		// Put the bitmap(World Maker Title img.png) vertex and index buffers on the graphics pipeline to prepare them for drawing.
		result = m_Bitmap[2]->Render(m_D3D->GetDeviceContext(), 0, 0);
		if (!result)
		{
			return false;
		}

		// Render the bitmap(World Maker Title img.png) with the texture shader.
		result = m_BitmapShader->Render(m_D3D->GetDeviceContext(), m_Bitmap[2]->GetIndexCount(), bitmapWorld[2], m_BaseViewMatrix, orthoMatrix, m_Bitmap[2]->GetTexture());
		if (!result)
		{
			return false;
		}
	}

	// Controls Scene (SceneType CONTROLS)
	if (m_Game->GetSceneType() == SceneType::CONTROLS)
	{
		// Put the bitmap(World Maker Controls img.png) vertex and index buffers on the graphics pipeline to prepare them for drawing.
		result = m_Bitmap[3]->Render(m_D3D->GetDeviceContext(), 0, 0);
		if (!result)
		{
			return false;
		}

		// Render the bitmap(World Maker Controls img.png) with the texture shader.
		result = m_BitmapShader->Render(m_D3D->GetDeviceContext(), m_Bitmap[3]->GetIndexCount(), bitmapWorld[3], m_BaseViewMatrix, orthoMatrix, m_Bitmap[3]->GetTexture());
		if (!result)
		{
			return false;
		}
	}

	// Ending Scene (SceneType ENDING)
	if (m_Game->GetSceneType() == SceneType::ENDING)
	{
		// Put the bitmap(World Maker Ending img.png) vertex and index buffers on the graphics pipeline to prepare them for drawing.
		result = m_Bitmap[4]->Render(m_D3D->GetDeviceContext(), 0, 0);
		if (!result)
		{
			return false;
		}

		// Render the bitmap(World Maker Ending img.png) with the texture shader.
		result = m_BitmapShader->Render(m_D3D->GetDeviceContext(), m_Bitmap[4]->GetIndexCount(), bitmapWorld[4], m_BaseViewMatrix, orthoMatrix, m_Bitmap[4]->GetTexture());
		if (!result)
		{
			return false;
		}
	}

	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();
	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	//// Set the Start Camera Rotation.
	//if (isStart)
	//{
	//	m_Camera->SetRotation(20.0f, 0.0f, 0.0f);
	//	isStart = false;
	//}


	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

void GraphicsClass::MoveCameraAndChar(int key)
{
	D3DXVECTOR3 trans;
	D3DXMATRIX md5World;
	D3DXMATRIX translateMatrix;

	if (key == DIK_W)
	{
		m_Camera->FrontWalk(1.0f);

		D3DXMatrixIdentity(&md5World);

		D3DXVec3Scale
		(
			&trans,
			&D3DXVECTOR3
			(
				m_Camera->GetLookAtVector().x * 10.0f,
				m_Camera->GetLookAtVector().y * 10.0f,
				m_Camera->GetLookAtVector().z * 10.0f
			),
			10.0f
		);

		D3DXVec3Add(&trans, &m_Camera->GetPosition(), &trans);
		D3DXMatrixRotationY(&md5World, m_charRot.y + 180.0f * 0.0174532925f);
		D3DXMatrixTranslation(&translateMatrix, trans.x, 20.0f, trans.z);
		D3DXMatrixMultiply(&md5World, &md5World, &translateMatrix);

		m_Md5Model->MakeAABB((XMMATRIX)md5World);

		//charPos = m_Camera->GetPosition();

		if (m_Game->GetSceneType() == SceneType::MAIN1)
		{
			for (int i = 0; i < CURRENTMODELNUM - LOOTINGMODELNUM - CONSTRUCTIONMODELNUM; i++)
			{
				if (CollisionClass::BoundingBoxCollision(
					m_Md5Model->GetBoundingBoxMin(),
					m_Md5Model->GetBoundingBoxMax(),
					m_Model[i]->GetBoundingBoxMin(),
					m_Model[i]->GetBoundingBoxMax(),
					m_Model[i]->GetColCheckEnabled()))
				{
					m_Camera->FrontWalk(-2.0f);
				}
			}
		}

		if (m_Game->GetSceneType() == SceneType::MAIN2)
		{
			Main2CollisionControl(1);
		}
	}

	if (key == DIK_S)
	{
		m_Camera->FrontWalk(-1.0f);

		D3DXMatrixIdentity(&md5World);

		D3DXVec3Scale
		(
			&trans,
			&D3DXVECTOR3
			(
				m_Camera->GetLookAtVector().x * 10.0f,
				m_Camera->GetLookAtVector().y * 10.0f,
				m_Camera->GetLookAtVector().z * 10.0f
			),
			10.0f
		);

		D3DXVec3Add(&trans, &m_Camera->GetPosition(), &trans);
		D3DXMatrixRotationY(&md5World, m_charRot.y + 180.0f * 0.0174532925f);
		D3DXMatrixTranslation(&translateMatrix, trans.x, 20.0f, trans.z);
		D3DXMatrixMultiply(&md5World, &md5World, &translateMatrix);

		m_Md5Model->MakeAABB((XMMATRIX)md5World);

		//charPos = m_Camera->GetPosition();
		
		if (m_Game->GetSceneType() == SceneType::MAIN1)
		{
			for (int i = 0; i < CURRENTMODELNUM - LOOTINGMODELNUM - CONSTRUCTIONMODELNUM; i++)
			{
				if (CollisionClass::BoundingBoxCollision(
					m_Md5Model->GetBoundingBoxMin(),
					m_Md5Model->GetBoundingBoxMax(),
					m_Model[i]->GetBoundingBoxMin(),
					m_Model[i]->GetBoundingBoxMax(),
					m_Model[i]->GetColCheckEnabled()))
				{
					m_Camera->FrontWalk(+2.0f);
				}
			}
		}

		if (m_Game->GetSceneType() == SceneType::MAIN2)
		{
			Main2CollisionControl(2);
		}
	}

	if (key == DIK_A)
	{
		m_Camera->SideWalk(1.0f);

		D3DXMatrixIdentity(&md5World);

		D3DXVec3Scale
		(
			&trans,
			&D3DXVECTOR3
			(
				m_Camera->GetLookAtVector().x * 10.0f,
				m_Camera->GetLookAtVector().y * 10.0f,
				m_Camera->GetLookAtVector().z * 10.0f
			),
			10.0f
		);

		D3DXVec3Add(&trans, &m_Camera->GetPosition(), &trans);
		D3DXMatrixRotationY(&md5World, m_charRot.y + 180.0f * 0.0174532925f);
		D3DXMatrixTranslation(&translateMatrix, trans.x, 20.0f, trans.z);
		D3DXMatrixMultiply(&md5World, &md5World, &translateMatrix);

		m_Md5Model->MakeAABB((XMMATRIX)md5World);

		//charPos = m_Camera->GetPosition();
		
		if (m_Game->GetSceneType() == SceneType::MAIN1)
		{
			for (int i = 0; i < CURRENTMODELNUM - LOOTINGMODELNUM - CONSTRUCTIONMODELNUM; i++)
			{
				if (CollisionClass::BoundingBoxCollision(
					m_Md5Model->GetBoundingBoxMin(),
					m_Md5Model->GetBoundingBoxMax(),
					m_Model[i]->GetBoundingBoxMin(),
					m_Model[i]->GetBoundingBoxMax(),
					m_Model[i]->GetColCheckEnabled()))
				{
					m_Camera->SideWalk(-1.0f);
				}
			}
		}

		if (m_Game->GetSceneType() == SceneType::MAIN2)
		{
			Main2CollisionControl(3);
		}
	}
	if (key == DIK_D)
	{
		m_Camera->SideWalk(-1.0f);

		D3DXMatrixIdentity(&md5World);

		D3DXVec3Scale
		(
			&trans,
			&D3DXVECTOR3
			(
				m_Camera->GetLookAtVector().x * 10.0f,
				m_Camera->GetLookAtVector().y * 10.0f,
				m_Camera->GetLookAtVector().z * 10.0f
			),
			10.0f
		);

		D3DXVec3Add(&trans, &m_Camera->GetPosition(), &trans);
		D3DXMatrixRotationY(&md5World, m_charRot.y + 180.0f * 0.0174532925f);
		D3DXMatrixTranslation(&translateMatrix, trans.x, 20.0f, trans.z);
		D3DXMatrixMultiply(&md5World, &md5World, &translateMatrix);

		m_Md5Model->MakeAABB((XMMATRIX)md5World);

		//charPos = m_Camera->GetPosition();
		
		if (m_Game->GetSceneType() == SceneType::MAIN1)
		{
			for (int i = 0; i < CURRENTMODELNUM - LOOTINGMODELNUM - CONSTRUCTIONMODELNUM; i++)
			{
				if (CollisionClass::BoundingBoxCollision(
					m_Md5Model->GetBoundingBoxMin(),
					m_Md5Model->GetBoundingBoxMax(),
					m_Model[i]->GetBoundingBoxMin(),
					m_Model[i]->GetBoundingBoxMax(),
					m_Model[i]->GetColCheckEnabled()))
				{
					m_Camera->SideWalk(+1.0f);
				}
			}
		}

		if (m_Game->GetSceneType() == SceneType::MAIN2)
		{
			Main2CollisionControl(4);
		}
	}
}

void GraphicsClass::RotateCameraAndChar(float x, float y, float z)
{
	if (m_Game->GetSceneType() == SceneType::MAIN1)
	{
		for (int i = 0; i < CURRENTMODELNUM - LOOTINGMODELNUM - CONSTRUCTIONMODELNUM; i++)
		{
			if (CollisionClass::BoundingBoxCollision(
				m_Md5Model->GetBoundingBoxMin(),
				m_Md5Model->GetBoundingBoxMax(),
				m_Model[i]->GetBoundingBoxMin(),
				m_Model[i]->GetBoundingBoxMax(),
				m_Model[i]->GetColCheckEnabled()))
			{
				return;
			}
		}
	}

	if (m_Game->GetSceneType() == SceneType::MAIN2)
	{
		Main2CollisionControl(5);
	}

	m_Camera->SetRotation(x, y, z);
	m_charRot = m_Camera->GetRotation() * 0.0174532925f;
}

void GraphicsClass::MovePad(int key, float frametime)
{
	if (key == DIK_LEFT)
		if(m_movement > -150.0f)
			m_movement -= 0.5f * frametime;
	if (key == DIK_RIGHT)
		if(m_movement < 150.0f)
			m_movement += 0.5f * frametime;
}

void GraphicsClass::MovePadAI(float frametime)
{
	if (m_AImovement < -150.0f)
		plusMinus = 1;
	if (m_AImovement > 150.0f)
		plusMinus = -1;

	m_AImovement += 0.5f * plusMinus * frametime;	
}

void GraphicsClass::AnimCharWalk(float frametime)
{
	float timeFactor = 0.005f;	// You can speed up or slow down time by changing this
	m_Md5Model->UpdateMD5Model(frametime*timeFactor, 0, m_D3D->GetDeviceContext());
}

void GraphicsClass::AnimCharConstruct(float frametime)
{
	float timeFactor = 0.005f;	// You can speed up or slow down time by changing this
	m_Md5Model->UpdateMD5Model(frametime*timeFactor, 1, m_D3D->GetDeviceContext());
}

void GraphicsClass::Main2CollisionControl(int type)
{
	for (int i = 48; i <= 50; i++)
	{
		if (CollisionClass::BoundingBoxCollision(
			m_Md5Model->GetBoundingBoxMin(),
			m_Md5Model->GetBoundingBoxMax(),
			m_Model[i]->GetBoundingBoxMin(),
			m_Model[i]->GetBoundingBoxMax(),
			m_Model[i]->GetColCheckEnabled()))
		{
			if (i == 48)
			{
				woodStackTF1 = false;
				m_Model[i]->SetColCheckEnabled(false);
				m_Sound->PlayWaveFile(3, false);
				m_Game->IncWoodStackCnt();
			}	
			if (i == 49)
			{
				woodStackTF2 = false;
				m_Model[i]->SetColCheckEnabled(false);
				m_Sound->PlayWaveFile(3, false);
				m_Game->IncWoodStackCnt();
			}
			if (i == 50)
			{
				woodStackTF3 = false;
				m_Model[i]->SetColCheckEnabled(false);
				m_Sound->PlayWaveFile(3, false);
				m_Game->IncWoodStackCnt();
			}
		}
	}

	for (int i = 1; i <= 43; i++)
	{
		if (!palmTreeExTF1 && i == 31)
			continue;
		if (!palmTreeExTF2 && i == 32)
			continue;
		if (!palmTreeExTF3 && i == 33)
			continue;

		for (int j = 15; j <= 30; j++)
			continue;

		if (CollisionClass::BoundingBoxCollision(
			m_Md5Model->GetBoundingBoxMin(),
			m_Md5Model->GetBoundingBoxMax(),
			m_Model[i]->GetBoundingBoxMin(),
			m_Model[i]->GetBoundingBoxMax(),
			m_Model[i]->GetColCheckEnabled()))
		{
			if (type == 1)
				m_Camera->FrontWalk(-2.0f);
			else if (type == 2)
				m_Camera->FrontWalk(+2.0f);
			else if (type == 3)
				m_Camera->SideWalk(-1.0f);
			else if (type == 4)
				m_Camera->SideWalk(+1.0f);
			else
				return;
		}
	}

	if (CollisionClass::BoundingBoxCollision(
		m_Md5Model->GetBoundingBoxMin(),
		m_Md5Model->GetBoundingBoxMax(),
		m_Model[45]->GetBoundingBoxMin(),
		m_Model[45]->GetBoundingBoxMax(),
		m_Model[45]->GetColCheckEnabled()))
	{
		cactusCollision1 = true;
	}
	else
		cactusCollision1 = false;

	if (CollisionClass::BoundingBoxCollision(
		m_Md5Model->GetBoundingBoxMin(),
		m_Md5Model->GetBoundingBoxMax(),
		m_Model[46]->GetBoundingBoxMin(),
		m_Model[46]->GetBoundingBoxMax(),
		m_Model[46]->GetColCheckEnabled()))
	{
		cactusCollision2 = true;
	}
	else
		cactusCollision2 = false;

	if (CollisionClass::BoundingBoxCollision(
		m_Md5Model->GetBoundingBoxMin(),
		m_Md5Model->GetBoundingBoxMax(),
		m_Model[47]->GetBoundingBoxMin(),
		m_Model[47]->GetBoundingBoxMax(),
		m_Model[47]->GetColCheckEnabled()))
	{
		cactusCollision3 = true;
	}
	else
		cactusCollision3 = false;
}