////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "applicationclass.h"
#include <math.h>
#include <chrono>
#include <ctime>
#include <thread>

ApplicationClass::ApplicationClass()
{
	m_Input = 0;
	m_Direct3D = 0;
	m_Camera = 0;
	m_Terrain = 0;
	m_Timer = 0;
	m_Position = 0;
	m_Fps = 0;
	m_Cpu = 0;
	m_FontShader = 0;
	m_Text = 0;
	m_TerrainShader = 0;
	m_Light = 0;
	m_lightWater = 0;
	m_sphere = 0;
	m_PositionMap = 0;
	m_PalmPositionMap = 0;
	m_RockPositionMap = 0;
	m_hitS;

	tempPos = D3DXVECTOR3(0, 0, 0);
	rotationPr = D3DXVECTOR3(0, 0, 0);
	housePosition = D3DXVECTOR3(160, 20, 153);

	m_projectileCount = 0;
	m_bombCount = 0;
	m_MonkeyCount = 0;
	m_BirdCount = 0;
	rotation2 = 0;
	countdown = 60;

	cambiocamara1 = false;
	cambiocamara2 = false;

	menu = false;
	ganaroperder = false;
	gameover = false;
	winorlose = &ganaroperder;
	gameoverPtr = &gameover;
	aaaa = false;
	zpressed = false;
	escpressed = false;
	paused = false;
	weaponMode = 0;

	playerVaccel = 0.005f;
	playerMaxSpeed = 0.015f;
	playerSpeed = 0.0f;

	contDisparos = 100;

	coconutAmmo = 50;
	pineappleAmmo = 10;
	MonkeyAmmo = 0;

	life = 100;
}


ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}


ApplicationClass::~ApplicationClass()
{
}

void ApplicationClass::MonkeySpawn()
{
	int seconds = 20;
	while (!gameover)
	{
		if (!paused)
		{
			if (seconds >= 20)
			{
				srand(((pineappleAmmo * coconutAmmo) + (m_MonkeyCount * m_BirdCount) + (m_bombCount * m_projectileCount) + contDisparos) / 3);
				int index = rand() % m_PalmPositionMap->getPositionCount();

				m_MonkeyPos.push_back(D3DXVECTOR3(palmPositions[index].x, palmPositions[index].y + 19, palmPositions[index].z));
				m_MonkeyRot.push_back(D3DXVECTOR3(0, 0, 0));
				m_MonkeyData.push_back(D3DXVECTOR4(0, 0, 0, 0));
				m_MonkeyCount++;

				seconds = 0;
			}
			else
			{
				seconds++;
			}

			std::chrono::milliseconds timespan(1000);
			std::this_thread::sleep_for(timespan);
		}
	}
}

void ApplicationClass::BirdSpawn()
{
	int seconds = 10;
	while (!gameover)
	{
		if (!paused)
		{
			if (seconds >= 10)
			{
				srand(((pineappleAmmo * coconutAmmo) + (m_MonkeyCount * m_BirdCount) + (m_bombCount * m_projectileCount) + contDisparos) / 3);
				float deegre = rand() % 360;
				float radian = deegre * 0.0174532925f;

				float x = 100 * cosf(radian);
				float y = 100 * sinf(radian);

				m_BirdPos.push_back(D3DXVECTOR3(housePosition.x + x, housePosition.y, housePosition.z + y));
				m_BirdRot.push_back(D3DXVECTOR3(0, 0, 0));
				m_BirdData.push_back(D3DXVECTOR4(0, 0, 0, 0));
				m_BirdCount++;

				seconds = 0;
			}
			else
			{
				seconds++;
			}

			std::chrono::milliseconds timespan(1000);
			std::this_thread::sleep_for(timespan);
		}
	}
}

void ApplicationClass::WinCountdown()
{
	std::chrono::milliseconds timespan(1000);
	std::this_thread::sleep_for(timespan);
	while (!gameover)
	{
		if (!paused)
		{
			countdown--;

			std::chrono::milliseconds timespan(1000);
			std::this_thread::sleep_for(timespan);
		}
	}
}

void ApplicationClass::SpawnMonkeyAmmo()
{
	while (!gameover)
	{
		if (!paused)
		{
			std::chrono::milliseconds timespan(1000);
			std::this_thread::sleep_for(timespan);

			for (int i = 0; i < m_MonkeyCount; i++)
			{
				m_MonkeyData[i].w++;

				if (m_MonkeyData[i].w > 5)
				{
					//Programar Disparo
					m_MonkeyAmmoPos.push_back(D3DXVECTOR3(m_MonkeyPos[i].x, m_MonkeyPos[i].y, m_MonkeyPos[i].z));
					m_MonkeyAmmoData.push_back(D3DXVECTOR4(0.5, m_MonkeyData[i].y, 0, 0));//x=Speed  y=Shooting angle   z=State  w=vSpeed
					MonkeyAmmo++;

					m_MonkeyData[i].w = 0;
				}
			}
		}
	}
}

bool ApplicationClass::ResetGame()
{
	/*for (int i = 0; i < m_MonkeyCount; i++)
	{
		delete m_MonkeyPos[i];
		delete m_MonkeyRot[i];
		delete m_MonkeyData[i];
	}*/
	m_MonkeyPos.clear();
	m_MonkeyRot.clear();
	m_MonkeyData.clear();
	m_MonkeyCount = 0;

	/*for (int i = 0; i < m_BirdCount; i++)
	{
		delete m_BirdPos[i];
		delete m_BirdRot[i];
		delete m_BirdData[i];
	}*/
	m_BirdPos.clear();
	m_BirdRot.clear();
	m_BirdData.clear();
	m_BirdCount = 0;

	/*for (int i = 0; i < m_projectileCount; i++)
	{
		delete m_projectilePos[i];
		delete m_projectileRot[i];
	}*/
	m_projectilePos.clear();
	m_projectileRot.clear();
	m_projectileCount = 0;

	/*for (int i = 0; i < m_bombCount; i++)
	{
		delete m_bombPos[i];
		delete m_bombOriginalPos[i];
		delete m_bombRot[i];
		delete m_bombData[i];
	}*/
	m_bombPos.clear();
	m_bombOriginalPos.clear();
	m_bombRot.clear();
	m_bombData.clear();
	m_bombCount = 0;

	tempPos = D3DXVECTOR3(0, 0, 0);
	rotationPr = D3DXVECTOR3(0, 0, 0);
	housePosition = D3DXVECTOR3(160, 20, 153);

	m_projectileCount = 0;
	m_bombCount = 0;
	m_MonkeyCount = 0;
	m_BirdCount = 0;
	rotation2 = 0;
	countdown = 60;

	cambiocamara1 = false;
	cambiocamara2 = false;

	menu = false;
	ganaroperder = false;
	gameover = false;
	winorlose = &ganaroperder;
	gameoverPtr = &gameover;
	aaaa = false;
	zpressed = false;
	paused = false;
	weaponMode = 0;

	playerVaccel = 0.005f;
	playerMaxSpeed = 0.015f;
	playerSpeed = 0.0f;

	contDisparos = 100;

	coconutAmmo = 50;
	pineappleAmmo = 10;
	MonkeyAmmo = 0;

	life = 100;

	bool result;
	float cameraX, cameraY, cameraZ;
	D3DXMATRIX baseViewMatrix;
	char videoCard[128];
	int videoMemory;

	m_Position->SetPosition(0, 0, 0);
	m_Position->SetRotation(0, 0, 0);

	/*Shutdown();

	bool result = Initialize(*Instance, *HWnd, *screenWidthPtr, *screenHeightPtr);
	if (!result)
	{
		return false;
	}*/
	/*monkeySpwn->~thread();
	birbSpwn->~thread();
	winCount->~thread();
	monkeySh->~thread();*/

	std::thread monkeySpawner(&ApplicationClass::MonkeySpawn, this);
	std::thread birdSpawner(&ApplicationClass::BirdSpawn, this);
	std::thread countdownWin(&ApplicationClass::WinCountdown, this);
	std::thread monkeyShoot(&ApplicationClass::SpawnMonkeyAmmo, this);
	monkeySpawner.detach();
	birdSpawner.detach();
	countdownWin.detach();
	monkeyShoot.detach();

	return true;
}

bool ApplicationClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	Instance = &hinstance;
	HWnd = &hwnd;
	screenWidthPtr = &screenWidth;
	screenHeightPtr = &screenHeight;

	bool result;
	float cameraX, cameraY, cameraZ;
	D3DXMATRIX baseViewMatrix;
	char videoCard[128];
	int videoMemory;


	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_Direct3D = new D3DClass;
	if (!m_Direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize DirectX 11.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(0, 0, -1);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Set the initial position of the camera.
	cameraX = 157.0f;
	cameraY = 18.0f;
	cameraZ = 149.0f;

	m_Camera->SetPosition(cameraX, cameraY, cameraZ);

	m_PositionMap = new PositionMapManager;
	result = m_PositionMap->Initialize("../Engine/data/positionmap.bmp", 0);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize PositionMapManager", L"Error", MB_OK);
		return false;
	}

	m_PalmPositionMap = new PositionMapManager;
	result = m_PalmPositionMap->Initialize("../Engine/data/palmpositionmap.bmp", 0);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize PositionMapManager", L"Error", MB_OK);
		return false;
	}

	m_RockPositionMap = new PositionMapManager;
	result = m_RockPositionMap->Initialize("../Engine/data/rockpositionmap.bmp", 0);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize PositionMapManager", L"Error", MB_OK);
		return false;
	}

	m_Billboard[0] = new billboardsclass;
	if (!m_Billboard[0]) {
		return false;
	}

	int textureCount = 2;
	WCHAR** filenames = new WCHAR*[textureCount];
	filenames[0] = L"../Engine/data/tree.png";
	filenames[1] = L"../Engine/data/treeNormal.png";
	
	// Initialize the model object.
	result = m_Billboard[0]->Initialize(m_Direct3D->GetDevice(), filenames, textureCount);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_Billboard[1] = new billboardsclass;
	if (!m_Billboard[1]) {
		return false;
	}

	textureCount = 2;
	filenames = new WCHAR*[textureCount];
	filenames[0] = L"../Engine/data/tree2.png";
	filenames[1] = L"../Engine/data/tree2Normal.png";

	// Initialize the model object.
	result = m_Billboard[1]->Initialize(m_Direct3D->GetDevice(), filenames, textureCount);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	m_Billboard[2] = new billboardsclass;
	if (!m_Billboard[2]) {
		return false;
	}

	textureCount = 2;
	filenames = new WCHAR*[textureCount];
	filenames[0] = L"../Engine/data/tree3.png";
	filenames[1] = L"../Engine/data/tree3Normal.png";

	// Initialize the model object.
	result = m_Billboard[2]->Initialize(m_Direct3D->GetDevice(), filenames, textureCount);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the water objetc.
	m_Water = new TerrainClass;
	if (!m_Water) 
	{
		return false;
	}

	// Initialize the water objetc.
	m_Water->countText = 3;
	m_Water->texture = new WCHAR*[m_Water->countText];
	m_Water->texture[0] = L"../Engine/data/waterDiffuse.jpg";
	m_Water->texture[1] = L"../Engine/data/waterNormal.png"; 
	m_Water->texture[2] = L"../Engine/data/waterSpecular.png";

	result = m_Water->Initialize(m_Direct3D->GetDevice(), "../Engine/data/waterHeightmap.bmp", m_Water->texture, m_Water->countText);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain object.
	m_Terrain = new TerrainClass;
	if (!m_Terrain)
	{
		return false;
	}

	m_Terrain->countText = 7;
	m_Terrain->texture = new WCHAR*[m_Terrain->countText];
	m_Terrain->texture[0] = L"../Engine/data/dirt01.dds";
	m_Terrain->texture[1] = L"../Engine/data/grass.jpg";
	m_Terrain->texture[2] = L"../Engine/data/fire.jpg";
	m_Terrain->texture[3] = L"../Engine/data/rock.jpg";
	m_Terrain->texture[4] = L"../Engine/data/beach.bmp";
	m_Terrain->texture[5] = L"../Engine/data/water.jpg";
	m_Terrain->texture[6] = L"../Engine/data/alpha4.jpg";
	
	// Initialize the terrain object.
	result = m_Terrain->Initialize(m_Direct3D->GetDevice(), "../Engine/data/heightmap02.bmp", m_Terrain->texture, m_Terrain->countText);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}
	billboardPositions = m_PositionMap->getPositions(m_Terrain);
	palmPositions = m_PalmPositionMap->getPositions(m_Terrain);
	rockPositions = m_RockPositionMap->getPositions(m_Terrain);

	// Create the timer object.
	m_Timer = new TimerClass;
	if(!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if(!m_Position)
	{
		return false;
	}

	// Set the initial position of the viewer to the same as the initial camera position.
	m_Position->SetPosition(cameraX, cameraY, cameraZ);

	// Create the fps object.
	m_Fps = new FpsClass;
	if(!m_Fps)
	{
		return false;
	}

	// Initialize the fps object.
	m_Fps->Initialize();

	// Create the cpu object.
	m_Cpu = new CpuClass;
	if(!m_Cpu)
	{
		return false;
	}

	// Initialize the cpu object.
	m_Cpu->Initialize();

	// Create the font shader object.
	m_FontShader = new FontShaderClass;
	if(!m_FontShader)
	{
		return false;
	}

	// Initialize the font shader object.
	result = m_FontShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the text object.
	m_Text = new TextClass;
	if(!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	// Retrieve the video card information.
	m_Direct3D->GetVideoCardInfo(videoCard, videoMemory);

	// Set the video card information in the text object.
	//result = m_Text->SetVideoCardInfo(videoCard, videoMemory, m_Direct3D->GetDeviceContext());
	//if(!result)
	//{
	//	MessageBox(hwnd, L"Could not set video card info in the text object.", L"Error", MB_OK);
	//	return false;
	//}

	// Create the terrain shader object.
	m_TerrainShader = new TerrainShaderClass;
	if(!m_TerrainShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_TerrainShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}

	m_sky = new skydome;
	if (!m_sky) {
		return false;
	}

	m_sky->countText = 2;
	m_sky->texture = new WCHAR*[m_sky->countText];
	m_sky->texture[0] = L"../Engine/data/skydome.jpg";
	m_sky->texture[1] = L"../Engine/data/skydome2.jpg";

	// Initialize the model object.
	result = m_sky->Initialize(m_Direct3D->GetDevice(), m_sky->texture, m_sky->countText);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create luz.
	m_SkyShader = new SkyShaderClass;
	if (!m_SkyShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_SkyShader->Initialize(m_Direct3D->GetDevice(), hwnd, L"../Engine/skydome.vs", L"../Engine/skydome.ps");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain shader object.
	m_BillboardShader = new BillboardShaderClass;
	if (!m_BillboardShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_BillboardShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the water shader object.
	m_WaterShader = new WaterShaderClass;
	if (!m_WaterShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_WaterShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}

	m_Cube = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/cube", "cube.obj");
	m_Cube->SetCollider(AXISALIGNEDBOUNGINGBOX);
	m_Bird = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/Bird", "Bird.obj");
	m_Bird->SetBSMulRadius(4);
	m_Monkey = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/MM3D_Monkey", "monkey.obj");
	Projectile = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/coconut", "Coconut.obj");
	m_Bomb = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/Pinnaple", "Pineapple.obj");
	m_Casa = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/Casa", "Casa.obj");
	m_Casa->SetCollider(AXISALIGNEDBOUNGINGBOX);
	m_Principal = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/drone3", "MQ-27.obj");
	//m_Palm = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/RealPalmBended", "Palm.obj");
	m_PalmStraight = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/RealPalmStraight", "PalmFixed.obj");
	m_Rock = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/rock", "newRock.obj");


	m_Projectile = new sphere;
	if (!m_Projectile)
		return false;

	textureCount = 1;
	filenames = new WCHAR*[textureCount];
	filenames[0] = L"../Engine/data/fire.jpg";

	// Initialize the model object.
	//result = m_Projectile->Initialize(m_Direct3D->GetDevice(), filenames, textureCount);
	result = m_Projectile->Initialize(m_Direct3D->GetDevice(), "", L"../Engine/data/fire.jpg");
	
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain shader object.
	m_GroupShader = new GroupShaderClass;
	if (!m_GroupShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_GroupShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.05f, 0.05f, 0.05f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(-0.5f, -1.0f, 0.0f);
	
	m_lightWater = new LightClass;
	if (!m_lightWater)
	{
		return false;
	}
	m_lightWater->SetAmbientColor(0.05f, 0.05f, 0.05f, 1.0f);
	m_lightWater->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_lightWater->SetDirection(0.0f, 1.0f, 0.0f);


	m_sphere = new cylinder;
	if (!m_sphere) {
		return false;
	}

	m_hitS = new sphere;
	if (!m_hitS) {
		return false;
	}


	result = m_hitS->Initialize(m_Direct3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/2k_sun.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model object.
	result = m_sphere->Initialize(m_Direct3D->GetDevice(), "data/obj/girl.obj", L"../Engine/data/water.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create luz.
	m_sphereShader = new LightShaderClass;
	if (!m_sphereShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_sphereShader->Initialize(m_Direct3D->GetDevice(), hwnd, L"../Engine/light.vs", L"../Engine/light.ps");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	std::thread monkeySpawner(&ApplicationClass::MonkeySpawn, this);
	std::thread birdSpawner(&ApplicationClass::BirdSpawn, this);
	std::thread countdownWin(&ApplicationClass::WinCountdown, this);
	std::thread monkeyShoot(&ApplicationClass::SpawnMonkeyAmmo, this);
	monkeySpwn = &monkeySpawner;
	birbSpwn = &birdSpawner;
	winCount = &countdownWin;
	monkeySh = &monkeyShoot;
	monkeySpawner.detach();
	birdSpawner.detach();
	countdownWin.detach();
	monkeyShoot.detach();

	return true;
}

void ApplicationClass::Shutdown()
{
	// Release the model object.
	if (m_sphere)
	{
		m_sphere->Shutdown();
		delete m_sphere;
		m_sphere = 0;
	}

	// Release the sky shader object.
	if (m_sphereShader)
	{
		m_sphereShader->Shutdown();
		delete m_sphereShader;
		m_sphereShader = 0;
	}


	// Release the model object.
	if (m_sky)
	{
		m_sky->Shutdown(m_sky->countText);
		delete m_sky;
		m_sky = 0;
	}

	// Release the sky shader object.
	if (m_SkyShader)
	{
		m_SkyShader->Shutdown();
		delete m_SkyShader;
		m_SkyShader = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	if (m_lightWater)
	{
		delete m_lightWater;
		m_lightWater = 0;
	}

	// Release the terrain shader object.
	if(m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		delete m_TerrainShader;
		m_TerrainShader = 0;
	}

	// Release the text object.
	if(m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the font shader object.
	if(m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	// Release the cpu object.
	if(m_Cpu)
	{
		m_Cpu->Shutdown();
		delete m_Cpu;
		m_Cpu = 0;
	}

	// Release the fps object.
	if(m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}

	// Release the position object.
	if(m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the timer object.
	if(m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the terrain object.
	if(m_Terrain)
	{
		m_Terrain->Shutdown(m_Terrain->countText);
		delete m_Terrain;
		m_Terrain = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the Direct3D object.
	if(m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	// Release the input object.
	if(m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}


bool ApplicationClass::Frame()
{
	bool result;


	// Read the user input.
	result = m_Input->Frame();
	if(!result)
	{
		return false;
	}
	
	// Check if the user pressed escape and wants to exit the application.
	if(m_Input->IsEscapePressed() == true)
	{
		if (!escpressed)
		{
			if (gameover)
			{
				result = ResetGame();
				if (!result)
				{
					return false;
				}
				gameover = false;
			}
			else
			{
				return false;
			}
		}
		escpressed = true;
	}
	else
	{
		escpressed = false;
	}

	//if (m_Input->IsAPressed() == true)
	//{
	//	gameover = !gameover;
	//}
	//
	//if (m_Input->IsZPressed() == true)
	//{
	//	ganaroperder = !ganaroperder;
	//}

	// Update the system stats.
	m_Timer->Frame();
	m_Fps->Frame();
	m_Cpu->Frame();

	// Update the FPS value in the text object.
	//result = m_Text->SetFps(m_Fps->GetFps(), m_Direct3D->GetDeviceContext());
	//if(!result)
	//{
	//	return false;
	//}
	
	// Update the CPU usage value in the text object.
	//result = m_Text->SetCpu(m_Cpu->GetCpuPercentage(), m_Direct3D->GetDeviceContext());
	//if (!result)
	//{
	//	return false;
	//}
	
	// Do the frame input processing.
	result = HandleInput(m_Timer->GetTime());
	if(!result)
	{
		return false;
	}

	// Render the graphics.
	result = RenderGraphics();
	if(!result)
	{
		return false;
	}

	return result;
}


bool ApplicationClass::HandleInput(float frameTime)
{
	bool keyDown, result, type;
	float posX, posY, posZ, rotX, rotY, rotZ;
	int mouseX, mouseY;

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_Input->IsAPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = m_Input->IsDPressed();
	m_Position->TurnRight(keyDown);

	keyDown = m_Input->IsWPressed();
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsSPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsSpacePressed();
	if (keyDown)
	{
		if (playerSpeed < playerMaxSpeed)
		{
			playerSpeed += playerVaccel;
		}
		m_Position->MoveUpward(keyDown, playerVaccel, playerMaxSpeed, playerSpeed);
	}
	else
	{
		if (playerSpeed > 0.0f)
		{
			playerSpeed -= playerVaccel;
		}
		else
		{
			playerSpeed = 0.0f;
		}
		m_Position->MoveDownward(!keyDown);
	}

	keyDown = m_Input->IsZPressed();
	if (keyDown)
	{
		if (!zpressed)
		{
			if (weaponMode == 0)
			{
				weaponMode = 1;
			}
			else if (weaponMode == 1)
			{
				weaponMode = 0;
			}
			zpressed = true;
		}
	}
	else
	{
		zpressed = false;
	}
	

	keyDown = m_Input->IsCPressed();
	if (keyDown)
		cambiocamara1 = true;
	if (!keyDown)
		cambiocamara2 = true;
	if (cambiocamara1 == true && cambiocamara2 == true)
	{
		m_Position->ChangeCameraType(keyDown);
		cambiocamara1 = false;
		cambiocamara2 = false;
	}

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);
	m_Position->GetCameraType(type);

	float tempPosY = posY;

	m_Input->GetMouseLocation(mouseX, mouseY);

	// Set the position of the camera.
	m_Terrain->GetHeightAtPosition(posX, posZ, tempPosY);

	if (posY < tempPosY)
	{
		posY = tempPosY;
	}

	m_Camera->SetPosition(posX, posY, posZ);
	if(m_Position->SetCameraType())
		m_Camera->SetRotation(rotX, rotY, 0);
	else {

		m_Camera->SetRotation(mouseY, mouseX, 0);
	}
	m_Camera->SetCameraType(type);

	// Update the position values in the text object.
	//result = m_Text->SetCameraPosition(posX, posY, posZ, m_Direct3D->GetDeviceContext());
	//if(!result)
	//{
	//	return false;
	//}
	//
	//// Update the rotation values in the text object.
	//result = m_Text->SetCameraRotation(rotX, rotY, rotZ, m_Direct3D->GetDeviceContext());
	//if(!result)
	//{
	//	return false;
	//}

	keyDown = m_Input->IsLeftClickPressed();
	if (keyDown == true && contDisparos >= 100)
	{
		if (weaponMode == 0 && coconutAmmo > 0)
		{
			m_projectileCount++;

			m_projectilePos.push_back(D3DXVECTOR3(posX, posY, posZ));
			m_projectileRot.push_back(D3DXVECTOR3(rotX, rotY, rotZ));
			coconutAmmo -= 1;
		}
		else if (weaponMode == 1 && pineappleAmmo > 0)
		{
			m_bombCount++;

			m_bombPos.push_back(D3DXVECTOR4(posX, posY, posZ, 0));
			m_bombOriginalPos.push_back(D3DXVECTOR3(posX, posY, posZ));
			m_bombData.push_back(D3DXVECTOR4(0, 0, 0, 0));
			m_bombRot.push_back(D3DXVECTOR3(rotX, rotY, rotZ));
			pineappleAmmo -= 1;
		}
		
		contDisparos = 0;
	}
	else
	{
		contDisparos+=2;
	}

	keyDown = m_Input->IsRightClickPressed();
	if (keyDown == true && contDisparos >= 100)
	{
		if (weaponMode == 0 && coconutAmmo > 0)
		{
			m_projectileCount++;

			m_projectilePos.push_back(D3DXVECTOR3(posX, posY, posZ));
			m_projectileRot.push_back(D3DXVECTOR3(rotX, rotY, rotZ));
			coconutAmmo -= 1;
		}
		else if (weaponMode == 1 && pineappleAmmo > 0)
		{
			m_bombCount++;

			m_bombPos.push_back(D3DXVECTOR4(posX, posY, posZ, 0));
			m_bombOriginalPos.push_back(D3DXVECTOR3(posX, posY, posZ));
			m_bombData.push_back(D3DXVECTOR4(0, 0, 0, 0));
			m_bombRot.push_back(D3DXVECTOR3(rotX, rotY, rotZ));
			pineappleAmmo -= 1;
		}

		contDisparos = 0;
	}
	else
	{
		contDisparos += 2;
	}

	return true;
}


bool ApplicationClass::RenderGraphics()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	D3DXMATRIX skyWM, skyRY, skyRZ, skyRX, skyS, skyT;
	bool result;
	if (!gameover)
	{

		// Clear the scene.
		m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

		// Generate the view matrix based on the camera's position.
		m_Camera->Render();

		// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
		m_Direct3D->GetWorldMatrix(worldMatrix);
		m_Camera->GetViewMatrix(viewMatrix);
		m_Direct3D->GetProjectionMatrix(projectionMatrix);
		m_Direct3D->GetOrthoMatrix(orthoMatrix);
		m_Direct3D->GetWorldMatrix(skyWM);
		m_Direct3D->GetWorldMatrix(skyRY);
		m_Direct3D->GetWorldMatrix(skyRZ);
		m_Direct3D->GetWorldMatrix(skyRX);
		m_Direct3D->GetWorldMatrix(skyS);
		m_Direct3D->GetWorldMatrix(skyT);

		D3DXMATRIX transla, rotat;
		static D3DXMATRIX tempprincipalWorldMatrix, principalWorldMatrix;
		D3DXVECTOR3 position = D3DXVECTOR3(157, 18, 150);
		D3DXVECTOR3 tempPosition = position;
		D3DXVECTOR3 rotacion = D3DXVECTOR3(0, 0, 0);
		D3DXMATRIX scale1;
		float yaw, pitch, roll;

		m_Position->GetPosition(position.x, position.y, position.z);
		m_Position->GetRotation(rotacion.x, rotacion.y, rotacion.z);

		pitch = rotacion.x * 0.0174532925f;
		yaw = (rotacion.y + 270.0) * 0.0174532925f;
		roll = rotacion.z * 0.0174532925f;

		m_Terrain->GetHeightAtPosition(position.x, position.z, tempPosition.y);

		if (position.y < tempPosition.y)
		{
			position.y = tempPosition.y;
			m_Position->SetPosition(position.x, position.y, position.z);
		}
		else
		{
			m_Position->SetPosition(position.x, position.y, position.z);
		}

		if (!m_Principal->Collides(m_Cube)) {
			//principalWorldMatrix = tempprincipalWorldMatrix;
			m_Position->GetPosition(tempPos.x, tempPos.y, tempPos.z);
		}
		else
		{
			//tempprincipalWorldMatrix = tempprincipalWorldMatrix;
			m_Position->SetPosition(tempPos.x, tempPos.y, tempPos.z);
		}

		if (!m_Principal->Collides(m_Casa)) {
			//principalWorldMatrix = tempprincipalWorldMatrix;
			m_Position->GetPosition(tempPos.x, tempPos.y, tempPos.z);
		}
		else
		{
			//tempprincipalWorldMatrix = tempprincipalWorldMatrix;
			m_Position->SetPosition(tempPos.x, tempPos.y, tempPos.z);
		}



		//m_Terrain->GetHeightAtPosition(position.x, position.z, position.y);

		D3DXMatrixTranslation(&transla, position.x, position.y, position.z);
		D3DXMatrixRotationYawPitchRoll(&rotat, yaw, 0, 0);
		float scaleDrone = 0.01f;
		D3DXMatrixScaling(&scale1, scaleDrone, scaleDrone, scaleDrone);

		tempprincipalWorldMatrix = rotat * transla;

		m_Principal->UpdateColliders(tempprincipalWorldMatrix);

		//m_Principal->SetBSMulRadius(scaleDrone);

		principalWorldMatrix = tempprincipalWorldMatrix;

		//if (!m_Principal->Collides(m_Cup)) {	// no hay colisión
		//	principalWorldMatrix = tempprincipalWorldMatrix;
		//	
		//}
		//else
		//{
		//	tempprincipalWorldMatrix = tempprincipalWorldMatrix;
		//}

		// sky
		static float rotation = 0.0f;
		static D3DXVECTOR3 skyPosition = D3DXVECTOR3(0, 0, 0);
		m_Position->GetPosition(skyPosition.x, skyPosition.y, skyPosition.z);
		// Update the rotation variable each frame.
		rotation += (float)D3DX_PI * 0.000001f;
		if (rotation > 360.0f)
		{
			rotation -= 360.0f;
		}
		D3DXMatrixScaling(&skyS, 150, 150, 150);
		D3DXMatrixRotationY(&skyRY, rotation);
		D3DXMatrixRotationX(&skyRX, D3DXToRadian(180.0f));
		D3DXMatrixTranslation(&skyT, skyPosition.x, skyPosition.y, skyPosition.z);
		skyWM = skyS * skyRX * skyRY * skyRZ * skyT;


		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		m_Direct3D->TurnZBufferOff();
		m_sky->Render(m_Direct3D->GetDeviceContext());
		result = m_SkyShader->Render(m_Direct3D->GetDeviceContext(), m_sky->GetIndexCount(), skyWM, viewMatrix, projectionMatrix,
			m_sky->GetTexture(m_sky->countText), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_sky->countText);
		if (!result)
		{
			return false;
		}
		m_Direct3D->TurnZBufferOn();

		for (auto& group : *m_Principal->GetGroupList())
		{
			group.Render(m_Direct3D->GetDeviceContext());
			result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), principalWorldMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
			if (!result)
			{
				return false;
			}
		}

		rotation2 += 0.01;
		D3DXMATRIX trans4, scale4, rotcupY4, ex3WorldMatrix;
		D3DXMatrixTranslation(&trans4, housePosition.x, housePosition.y, housePosition.z);
		D3DXMatrixRotationX(&rotcupY4, 0);
		D3DXMatrixRotationYawPitchRoll(&rotcupY4, 1.5708, 0, 3.14159);
		D3DXMatrixScaling(&scale4, 0.1, 0.1, 0.1);
		ex3WorldMatrix = scale4 * rotcupY4 * trans4;
		for (auto& group : *m_Casa->GetGroupList())
		{
			group.Render(m_Direct3D->GetDeviceContext());
			result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), ex3WorldMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
			if (!result)
				return false;
		}
		m_Casa->UpdateColliders(ex3WorldMatrix);

		rotation2 += 0.01;
		D3DXMATRIX trans, scale, rotcupY, cupWorldMatrix;
		D3DXMatrixTranslation(&trans, 161, 20, 135);
		D3DXMatrixRotationX(&rotcupY, rotation2);
		D3DXMatrixScaling(&scale, 2.1f, 1, 3.8f);
		cupWorldMatrix = scale * trans;
		m_Cube->UpdateColliders(cupWorldMatrix);
		/*for (auto &group : *m_Cube->GetGroupList())
		{
			group.Render(m_Direct3D->GetDeviceContext());
			result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), cupWorldMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
			if (!result)
				return false;
		}*/



		rotation2 += 0.01;
		for (int i = 0; i < m_BirdCount; i++)
		{
			if (m_BirdData[i].x == 0)
			{
				D3DXMATRIX trans2, transrot, scale21, birdrotMatrix, ex1WorldMatrix;

				D3DXVECTOR3 move = D3DXVECTOR3(0, 0, 0.1);

				pitch = m_BirdRot[i].x * 0.0174532925f;
				yaw = m_BirdRot[i].y * 0.0174532925f;
				roll = m_BirdRot[i].z * 0.0174532925f;

				D3DXVECTOR3 temp = housePosition - m_BirdPos[i];
				float angle = atan2(temp.x, temp.z);

				D3DXMatrixRotationYawPitchRoll(&transrot, angle, 0, 0);

				D3DXVECTOR4 transformed;
				D3DXVec3Transform(&transformed, &move, &transrot);

				m_BirdPos[i].x += transformed.x;
				m_BirdPos[i].y += transformed.y;
				m_BirdPos[i].z += transformed.z;

				D3DXMatrixRotationYawPitchRoll(&birdrotMatrix, angle, pitch, roll);
				D3DXMatrixTranslation(&trans2, m_BirdPos[i].x, m_BirdPos[i].y, m_BirdPos[i].z);
				D3DXMatrixScaling(&scale21, 4, 4, 4);

				ex1WorldMatrix = scale21 * birdrotMatrix * trans2;

				for (auto& group : *m_Bird->GetGroupList())
				{
					group.Render(m_Direct3D->GetDeviceContext());
					result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), ex1WorldMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
					if (!result)
						return false;
				}

				m_Bird->UpdateColliders(ex1WorldMatrix);

				if (m_Principal->Collides(m_Bird))
				{
					life -= 20;

					m_BirdData[i].x = 5;
				}

				if (m_Cube->Collides(m_Bird))
				{
					ganaroperder = false;

					gameover = true;
				}

				if (m_Casa->Collides(m_Bird))
				{
					ganaroperder = false;

					gameover = true;
				}
			}
		}

		rotation2 += 0.01;
		for (int i = 0; i < m_MonkeyCount; i++)
		{
			if (m_MonkeyData[i].x == 0)
			{
				D3DXMATRIX trans3, scale3, monkeyRotMatrix, ex2WorldMatrix;

				pitch = m_MonkeyRot[i].x * 0.0174532925f;
				yaw = m_MonkeyRot[i].y * 0.0174532925f;
				roll = m_MonkeyRot[i].z * 0.0174532925f;

				D3DXVECTOR3 playerPosition;
				m_Position->GetPosition(playerPosition.x, playerPosition.y, playerPosition.z);
				D3DXVECTOR3 temp = playerPosition - m_MonkeyPos[i];
				yaw = atan2(temp.x, temp.z);

				m_MonkeyData[i].y = yaw;

				D3DXMatrixRotationYawPitchRoll(&monkeyRotMatrix, yaw, pitch, roll);
				D3DXMatrixTranslation(&trans3, m_MonkeyPos[i].x, m_MonkeyPos[i].y, m_MonkeyPos[i].z);
				D3DXMatrixScaling(&scale3, 1, 1, 1);

				ex2WorldMatrix = scale3 * monkeyRotMatrix * trans3;

				for (auto& group : *m_Monkey->GetGroupList())
				{
					group.Render(m_Direct3D->GetDeviceContext());
					result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), ex2WorldMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
					if (!result)
						return false;
				}

				m_Monkey->UpdateColliders(ex2WorldMatrix);

				if (m_Principal->Collides(m_Monkey))
				{
					life -= 60;

					m_MonkeyData[i].x = 5;
				}
			}
			else if (m_MonkeyData[i].x == 1)
			{
				int mouseX, mouseY;
				m_Input->GetMouseLocation(mouseX, mouseY);
				srand(((pineappleAmmo * coconutAmmo) + (m_MonkeyCount * m_BirdCount) + (m_bombCount * m_projectileCount) * mouseX) * mouseY);
				m_MonkeyData[i].x = rand() % 100 + 1;
				if (m_MonkeyData[i].x > 50)
				{
					m_MonkeyData[i].x = 3;
				}
				else
				{
					m_MonkeyData[i].x = 2;
				}
			}
			else if (m_MonkeyData[i].x == 2)
			{
				D3DXMATRIX rotatPro, proWorldMatrix, scalP, transP;

				pitch = m_MonkeyRot[i].x * 0.0174532925f;
				yaw = m_MonkeyRot[i].y * 0.0174532925f;
				roll = m_MonkeyRot[i].z * 0.0174532925f;

				D3DXMatrixTranslation(&transP, m_MonkeyPos[i].x, m_MonkeyPos[i].y + 4, m_MonkeyPos[i].z);
				float scalePr = 0.01f;
				D3DXMatrixScaling(&scalP, scalePr, scalePr, scalePr);
				proWorldMatrix = scalP * transP;

				for (auto& group : *Projectile->GetGroupList())
				{
					group.Render(m_Direct3D->GetDeviceContext());
					result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), proWorldMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
					if (!result)
					{
						return false;
					}
				}

				Projectile->UpdateColliders(proWorldMatrix);

				Projectile->SetBSMulRadius(scalePr);

				if (m_Principal->Collides(Projectile))
				{
					coconutAmmo += 5;

					m_MonkeyData[i].x = 4;
				}
			}
			else if (m_MonkeyData[i].x == 3)
			{
				D3DXMATRIX rotatPro, proWorldMatrix, scalP, transP;

				pitch = m_MonkeyRot[i].x * 0.0174532925f;
				yaw = m_MonkeyRot[i].y * 0.0174532925f;
				roll = m_MonkeyRot[i].z * 0.0174532925f;

				D3DXMatrixTranslation(&transP, m_MonkeyPos[i].x, m_MonkeyPos[i].y + 4, m_MonkeyPos[i].z);
				float scalePr = 0.04f;
				D3DXMatrixScaling(&scalP, scalePr, scalePr, scalePr);
				proWorldMatrix = scalP * transP;

				for (auto& group : *m_Bomb->GetGroupList())
				{
					group.Render(m_Direct3D->GetDeviceContext());
					result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), proWorldMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
					if (!result)
					{
						return false;
					}
				}

				m_Bomb->UpdateColliders(proWorldMatrix);

				m_Bomb->SetBSMulRadius(scalePr);

				if (m_Principal->Collides(m_Bomb))
				{
					pineappleAmmo += 2;

					m_MonkeyData[i].x = 4;
				}
			}
		}

		for (int i = 0; i < m_projectileCount; i++)
		{
			D3DXMATRIX rotatPro, proWorldMatrix, scalP, transP;

			D3DXVECTOR3 move = D3DXVECTOR3(0, 0, 0.5);

			pitch = m_projectileRot[i].x * 0.0174532925f;
			yaw = m_projectileRot[i].y * 0.0174532925f;
			roll = m_projectileRot[i].z * 0.0174532925f;

			D3DXMatrixRotationYawPitchRoll(&rotatPro, yaw, 0, 0);


			D3DXVECTOR4 transformed;
			D3DXVec3Transform(&transformed, &move, &rotatPro);

			D3DXMATRIX rotboi;

			//D3DXMatrixRotationZ(&rotboi, rotationPr.y);

			m_projectilePos[i].x += transformed.x;
			m_projectilePos[i].y += transformed.y;
			m_projectilePos[i].z += transformed.z;

			D3DXMatrixTranslation(&transP, m_projectilePos[i].x, m_projectilePos[i].y, m_projectilePos[i].z);
			float scalePr = 0.005f;
			D3DXMatrixScaling(&scalP, scalePr, scalePr, scalePr);
			proWorldMatrix = scalP * rotatPro * transP;

			//result = m_sphereShader->Render(m_Direct3D->GetDeviceContext(), m_Projectile->GetIndexCount(), proWorldMatrix, viewMatrix, projectionMatrix, m_Projectile->GetTexture(),
			//	m_Light->GetDirection(), m_Light->GetDiffuseColor());

			for (auto& group : *Projectile->GetGroupList())
			{
				group.Render(m_Direct3D->GetDeviceContext());
				result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), proWorldMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
				if (!result)
				{
					return false;
				}
			}

			Projectile->UpdateColliders(proWorldMatrix);

			Projectile->SetBSMulRadius(scalePr);

			for (int h = 0; h < m_MonkeyCount; h++)
			{
				D3DXMATRIX trans3, scale3, monkeyRotMatrix, ex2WorldMatrix;

				pitch = m_MonkeyRot[h].x * 0.0174532925f;
				yaw = m_MonkeyRot[h].y * 0.0174532925f;
				roll = m_MonkeyRot[h].z * 0.0174532925f;

				D3DXMatrixRotationYawPitchRoll(&monkeyRotMatrix, yaw, pitch, roll);
				D3DXMatrixTranslation(&trans3, m_MonkeyPos[h].x, m_MonkeyPos[h].y, m_MonkeyPos[h].z);
				D3DXMatrixScaling(&scale3, 1, 1, 1);

				ex2WorldMatrix = scale3 * monkeyRotMatrix * trans3;

				m_Monkey->UpdateColliders(ex2WorldMatrix);

				if (Projectile->Collides(m_Monkey))
				{
					m_MonkeyData[h].x = 1;
				}
			}

			for (int h = 0; h < m_BirdCount; h++)
			{
				D3DXMATRIX trans2, scale21, birdrotMatrix, ex1WorldMatrix;

				pitch = m_BirdRot[h].x * 0.0174532925f;
				yaw = m_BirdRot[h].y * 0.0174532925f;
				roll = m_BirdRot[h].z * 0.0174532925f;

				D3DXMatrixRotationYawPitchRoll(&birdrotMatrix, yaw, pitch, roll);
				D3DXMatrixTranslation(&trans2, m_BirdPos[h].x, m_BirdPos[h].y, m_BirdPos[h].z);
				D3DXMatrixScaling(&scale21, 4, 4, 4);

				ex1WorldMatrix = scale21 * birdrotMatrix * trans2;

				m_Bird->UpdateColliders(ex1WorldMatrix);

				if (Projectile->Collides(m_Bird))
				{
					m_BirdData[h].x = 1;
				}
			}

			/*if (Projectile->Collides(m_Cube))
			{
				ganaroperder = true;

				gameover = true;
			}*/

			if (!result)
			{
				return false;
			}
		}
		for (int i = 0; i < m_bombCount; i++)
		{
			D3DXMATRIX rotatPro, proWorldMatrix, scalP, transP;

			D3DXVECTOR3 move;
			float vel = 0.5f;
			float parabolic_angle = 45.0f;
			float rad = parabolic_angle * (3.14159265358979323846 / 180);
			float gravity = 0.025f;

			pitch = m_bombRot[i].x * 0.0174532925f;
			yaw = m_bombRot[i].y * 0.0174532925f;
			roll = m_bombRot[i].z * 0.0174532925f;

			D3DXMatrixRotationYawPitchRoll(&rotatPro, yaw, 0, 0);
			//vel = 0.5f;
			if (m_bombData[i].w == 0)
			{
				m_bombData[i].x = vel;
				m_bombData[i].w = 1;
			}

			float vy = m_bombData[i].x * sinf(rad);
			float vx = vel * cosf(rad);
			m_bombData[i].x -= gravity;


			move = D3DXVECTOR3(0, vy, vx);

			D3DXVECTOR4 transformed;
			D3DXVec3Transform(&transformed, &move, &rotatPro);

			D3DXMATRIX rotboi;

			//D3DXMatrixRotationZ(&rotboi, rotationPr.y);

			m_bombPos[i].x += transformed.x;
			m_bombPos[i].y += transformed.y;
			m_bombPos[i].z += transformed.z;

			D3DXMatrixTranslation(&transP, m_bombPos[i].x, m_bombPos[i].y, m_bombPos[i].z);
			float scalePr = 0.02f;
			D3DXMatrixScaling(&scalP, scalePr, scalePr, scalePr);
			proWorldMatrix = scalP * rotatPro * transP;

			for (auto& group : *m_Bomb->GetGroupList())
			{
				group.Render(m_Direct3D->GetDeviceContext());
				result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), proWorldMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
				if (!result)
				{
					return false;
				}
			}

			m_Bomb->UpdateColliders(proWorldMatrix);

			m_Bomb->SetBSMulRadius(scalePr + m_bombData[i].y);

			for (int h = 0; h < m_MonkeyCount; h++)
			{
				D3DXMATRIX trans3, scale3, monkeyRotMatrix, ex2WorldMatrix;

				pitch = m_MonkeyRot[h].x * 0.0174532925f;
				yaw = m_MonkeyRot[h].y * 0.0174532925f;
				roll = m_MonkeyRot[h].z * 0.0174532925f;

				D3DXMatrixRotationYawPitchRoll(&monkeyRotMatrix, yaw, pitch, roll);
				D3DXMatrixTranslation(&trans3, m_MonkeyPos[h].x, m_MonkeyPos[h].y, m_MonkeyPos[h].z);
				D3DXMatrixScaling(&scale3, 1, 1, 1);

				ex2WorldMatrix = scale3 * monkeyRotMatrix * trans3;

				m_Monkey->UpdateColliders(ex2WorldMatrix);

				if (m_Bomb->Collides(m_Monkey))
				{
					m_MonkeyData[h].x = 1;

					m_bombData[i].y = 0.5;
				}
			}

			for (int h = 0; h < m_BirdCount; h++)
			{
				D3DXMATRIX trans2, scale21, birdrotMatrix, ex1WorldMatrix;

				pitch = m_BirdRot[h].x * 0.0174532925f;
				yaw = m_BirdRot[h].y * 0.0174532925f;
				roll = m_BirdRot[h].z * 0.0174532925f;

				D3DXMatrixRotationYawPitchRoll(&birdrotMatrix, yaw, pitch, roll);
				D3DXMatrixTranslation(&trans2, m_BirdPos[h].x, m_BirdPos[h].y, m_BirdPos[h].z);
				D3DXMatrixScaling(&scale21, 4, 4, 4);

				ex1WorldMatrix = scale21 * birdrotMatrix * trans2;

				m_Bird->UpdateColliders(ex1WorldMatrix);

				if (m_Bomb->Collides(m_Bird))
				{
					m_BirdData[h].x = 1;

					m_bombData[i].y = 0.5;
				}
			}

			if (m_Bomb->Collides(m_Cube))
			{
				m_bombData[i].y = 0.5;
			}

			if (m_Bomb->Collides(m_Casa))
			{
				m_bombData[i].y = 0.5;
			}

			if (!result)
			{
				return false;
			}
		}

		for (int i = 0; i < MonkeyAmmo; i++)
		{
			if (m_MonkeyAmmoData[i].z < 2)
			{
				D3DXMATRIX rotatPro, proWorldMatrix, scalP, transP;

				D3DXVECTOR3 move;
				float vel = 0.5f;
				float parabolic_angle = 45.0f;
				float rad = parabolic_angle * (3.14159265358979323846 / 180);
				float gravity = 0.025f;

				pitch = 0;
				yaw = m_MonkeyAmmoData[i].y;
				roll = 0;

				D3DXMatrixRotationYawPitchRoll(&rotatPro, yaw, 0, 0);

				if (m_MonkeyAmmoData[i].z == 0)
				{
					m_MonkeyAmmoData[i].w = m_MonkeyAmmoData[i].x;
					m_MonkeyAmmoData[i].z = 1;
				}

				float vy = m_MonkeyAmmoData[i].w * sinf(rad);
				float vx = m_MonkeyAmmoData[i].x * cosf(rad);
				m_MonkeyAmmoData[i].w -= gravity;

				move = D3DXVECTOR3(0, vy, vx);

				D3DXVECTOR4 transformed;
				D3DXVec3Transform(&transformed, &move, &rotatPro);

				m_MonkeyAmmoPos[i].x += transformed.x;
				m_MonkeyAmmoPos[i].y += transformed.y;
				m_MonkeyAmmoPos[i].z += transformed.z;

				D3DXMatrixTranslation(&transP, m_MonkeyAmmoPos[i].x, m_MonkeyAmmoPos[i].y, m_MonkeyAmmoPos[i].z);
				float scalePr = 0.005f;
				D3DXMatrixScaling(&scalP, scalePr, scalePr, scalePr);
				proWorldMatrix = scalP * rotatPro * transP;

				for (auto& group : *Projectile->GetGroupList())
				{
					group.Render(m_Direct3D->GetDeviceContext());
					result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), proWorldMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
					if (!result)
					{
						return false;
					}
				}

				Projectile->UpdateColliders(proWorldMatrix);

				Projectile->SetBSMulRadius(scalePr);

				if (Projectile->Collides(m_Principal))
				{
					life -= 30;

					m_MonkeyAmmoData[i].z = 2;
				}
			}
		}

		// Render the terrain buffers.
		m_Terrain->Render(m_Direct3D->GetDeviceContext());

		// Render the terrain using the terrain shader.
		result = m_TerrainShader->Render(m_Direct3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Light->GetDirection(), m_Terrain->GetTexture(m_Terrain->countText), m_Terrain->countText);
		if (!result)
		{
			return false;
		}

		// Render the sphere buffers.
		m_sphere->Render(m_Direct3D->GetDeviceContext());

		// Render the sphere using the terrain shader.
		result = m_sphereShader->Render(m_Direct3D->GetDeviceContext(), m_sphere->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_sphere->GetTexture(),
			m_Light->GetDirection(), m_Light->GetDiffuseColor());
		if (!result)
		{
			return false;
		}

		int posCount = 0;
		int pos_divider = m_PositionMap->getPositionCount() / 3;
		// Render the terrain buffers.
		m_Billboard[0]->Render(m_Direct3D->GetDeviceContext());
		for (int i = 0; i < pos_divider; i++)
		{
			if (posCount < m_PositionMap->getPositionCount())
			{
				// Render the terrain using the terrain shader.
				result = m_BillboardShader->Render(m_Direct3D->GetDeviceContext(), m_Billboard[0]->GetIndexCount(), billboardsclass::generateWorldMAtrix(m_Camera->GetPosition(), billboardPositions[posCount]), viewMatrix, projectionMatrix,
					m_Billboard[0]->GetTexture2(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), D3DXVECTOR4(1, 1, 1, 1), 10);
				if (!result)
				{
					return false;
				}
			}
			posCount++;
		}
		// Render the terrain buffers.
		m_Billboard[1]->Render(m_Direct3D->GetDeviceContext());
		for (int i = 0; i < pos_divider; i++)
		{
			if (posCount < m_PositionMap->getPositionCount())
			{
				// Render the terrain using the terrain shader.
				result = m_BillboardShader->Render(m_Direct3D->GetDeviceContext(), m_Billboard[1]->GetIndexCount(), billboardsclass::generateWorldMAtrix(m_Camera->GetPosition(), billboardPositions[posCount]), viewMatrix, projectionMatrix,
					m_Billboard[1]->GetTexture2(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), D3DXVECTOR4(1, 1, 1, 1), 10);
				if (!result)
				{
					return false;
				}
			}
			posCount++;
		}
		// Render the terrain buffers.
		m_Billboard[2]->Render(m_Direct3D->GetDeviceContext());
		for (int i = 0; i < pos_divider; i++)
		{
			if (posCount < m_PositionMap->getPositionCount())
			{
				// Render the terrain using the terrain shader.
				result = m_BillboardShader->Render(m_Direct3D->GetDeviceContext(), m_Billboard[2]->GetIndexCount(), billboardsclass::generateWorldMAtrix(m_Camera->GetPosition(), billboardPositions[posCount]), viewMatrix, projectionMatrix,
					m_Billboard[2]->GetTexture2(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), D3DXVECTOR4(1, 1, 1, 1), 10);
				if (!result)
				{
					return false;
				}
			}
			posCount++;
		}

		D3DXMATRIX wms, wmt;
		m_Direct3D->GetWorldMatrix(wms);
		m_Direct3D->GetWorldMatrix(wmt);
		D3DXMatrixScaling(&wms, 5, 5, 5);
		D3DXMatrixTranslation(&wmt, -205.0f, -20.0f, -215.0f);

		// Render the terrain buffers.
		m_Water->Render(m_Direct3D->GetDeviceContext());

		// Render the terrain using the terrain shader.
		result = m_WaterShader->Render(m_Direct3D->GetDeviceContext(), m_Water->GetIndexCount(), wms * wmt, viewMatrix, projectionMatrix,
			m_Water->GetTexture(m_Water->countText), m_lightWater->GetDirection(), m_lightWater->GetDiffuseColor(), m_Camera->GetPosition(), D3DXVECTOR4(0.9, 0.3, 0.3, 1), 10);

		if (!result)
		{
			return false;
		}

		int palmCount = m_PalmPositionMap->getPositionCount();
		for (int i = 0; i < palmCount; i++)
		{
			D3DXMATRIX trans5, scale5, rotcupY5, palmWorldMatrix;
			D3DXMatrixTranslation(&trans5, palmPositions[i].x, palmPositions[i].y, palmPositions[i].z);
			D3DXMatrixRotationX(&rotcupY5, 4.71239);
			D3DXMatrixScaling(&scale5, 0.3, 0.3, 0.3);
			palmWorldMatrix = scale5 * rotcupY5 * trans5;
			for (auto& group : *m_PalmStraight->GetGroupList())
			{
				group.Render(m_Direct3D->GetDeviceContext());
				result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), palmWorldMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
				if (!result)
					return false;
			}
			m_PalmStraight->UpdateColliders(palmWorldMatrix);
		}

		int rockCount = m_RockPositionMap->getPositionCount();
		for (int i = 0; i < rockCount; i++)
		{
			D3DXMATRIX trans6, scale6, rotcupY6, rockWorldMatrix;
			D3DXMatrixTranslation(&trans6, rockPositions[i].x, rockPositions[i].y + 1, rockPositions[i].z);
			D3DXMatrixRotationX(&rotcupY6, 4.71239);
			D3DXMatrixScaling(&scale6, 3, 3, 3);
			rockWorldMatrix = scale6 * rotcupY6 * trans6;

			for (auto& group : *m_Rock->GetGroupList())
			{
				group.Render(m_Direct3D->GetDeviceContext());
				result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), rockWorldMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
				if (!result)
					return false;
			}
			m_Rock->UpdateColliders(rockWorldMatrix);
		}
		if (life <= 0)
		{
			ganaroperder = false;

			gameover = true;
		}

		if (countdown < 0)
		{
			ganaroperder = true;

			gameover = true;

			countdown = 0;
		}
	}

	// Turn off the Z buffer to begin all 2D rendering.
	m_Direct3D->TurnZBufferOff();
		
	// Turn on the alpha blending before rendering the text. 
	m_Direct3D->TurnOnAlphaBlending();


	result = m_Text->Render(m_Direct3D->GetDeviceContext(), m_FontShader, worldMatrix, orthoMatrix, menu, gameover, ganaroperder, life, coconutAmmo, pineappleAmmo, countdown);
	if(!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	//m_Direct3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_Direct3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}