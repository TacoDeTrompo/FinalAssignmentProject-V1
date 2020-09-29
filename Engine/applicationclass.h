////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "inputclass.h"
#include "d3dclass.h"
#include "cameraclass.h"
#include "terrainclass.h"
#include "timerclass.h"
#include "positionclass.h"
#include "fpsclass.h"
#include "cpuclass.h"
#include "fontshaderclass.h"
#include "textclass.h"
#include "terrainshaderclass.h"
#include "watershaderclass.h"
#include "lightclass.h"
#include "billboardshaderclass.h"
#include "model.h"
#include "modelclass.h"
#include "skymodel.h"
#include "groupshaderclass.h"
#include "skyshaderclass.h"
#include "billboardsclass.h"
#include "skymodel.h"
#include "PositionMapManager.h"

#include "skydome.h"
#include "cube.h"
#include "plane.h"
#include "cylinder.h"
#include "cone.h"
#include "torus.h"
#include "sphere.h"
#include "lightshaderclass.h"

#include <thread>

////////////////////////////////////////////////////////////////////////////////
// Class name: ApplicationClass
////////////////////////////////////////////////////////////////////////////////
class ApplicationClass
{
public:
	ApplicationClass();
	ApplicationClass(const ApplicationClass&);
	~ApplicationClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

private:
	bool HandleInput(float);
	bool RenderGraphics();
	void MonkeySpawn();
	void BirdSpawn();
	void WinCountdown();
	void SpawnMonkeyAmmo();

	bool ResetGame();

	int m_projectileCount, m_bombCount, m_BirdCount, m_MonkeyCount, MonkeyAmmo;
	vector <D3DXVECTOR3> m_projectilePos, m_bombOriginalPos, m_MonkeyAmmoPos;
	vector <D3DXVECTOR4> m_bombPos, m_bombData, m_BirdData, m_MonkeyData, m_MonkeyAmmoData;
	vector <D3DXVECTOR3> m_projectileRot, m_bombRot;
	vector <D3DXVECTOR3> m_BirdPos, m_BirdRot, m_MonkeyPos, m_MonkeyRot;
	vector <D3DXVECTOR3> m_projectilePickup, m_BombPickup; 

	//Initialize parameters
	HINSTANCE* Instance;
	HWND* HWnd;
	int* screenWidthPtr;
	int* screenHeightPtr;

private:
	InputClass * m_Input;
	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	TerrainClass* m_Terrain, *m_Water;
	TimerClass* m_Timer;
	PositionClass* m_Position;
	FpsClass* m_Fps;
	CpuClass* m_Cpu;
	FontShaderClass* m_FontShader;
	TextClass* m_Text;
	TerrainShaderClass* m_TerrainShader;
	SkyShaderClass* m_SkyShader;
	WaterShaderClass* m_WaterShader;
	BillboardShaderClass* m_BillboardShader;
	LightClass* m_Light, *m_lightWater;
	ModelClass *m_Billboard[3], * m_sphere, *m_Projectile;
	sphere *m_hitS;
	SkyModel* m_sky;
	Model* m_Principal, *m_Cube, *m_Bird, *m_Monkey, *Projectile, *m_Bomb, *m_Casa, *m_Palm, *m_PalmStraight, *m_Rock;
	GroupShaderClass* m_GroupShader;
	LightShaderClass* m_sphereShader;
	PositionMapManager* m_PositionMap;
	PositionMapManager* m_PalmPositionMap;
	PositionMapManager* m_RockPositionMap;
	D3DXVECTOR3 tempPos, rotationPr;
	D3DXVECTOR3* billboardPositions, *palmPositions, *rockPositions, housePosition;
	std::thread *monkeySpwn, *birbSpwn, *winCount, *monkeySh;
	float contDisparos;
	float rotation2;
	bool cambiocamara1, cambiocamara2;
	bool menu;
	bool ganaroperder;
	bool *winorlose, *gameoverPtr;
	bool aaaa;
	bool gameover;
	bool zpressed;
	bool escpressed;
	bool paused;
	int weaponMode;
	int countdown;
	int life;
	float playerVaccel;
	float playerMaxSpeed;
	float playerSpeed;
	int coconutAmmo;
	int pineappleAmmo;
};

#endif