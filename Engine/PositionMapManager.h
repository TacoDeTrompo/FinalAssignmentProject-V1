#pragma once

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <stdio.h>

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"
#include "terrainclass.h"

class PositionMapManager
{
private:
	struct PositionMapType
	{
		float x, y, z;
	};
public:
	PositionMapManager();
	~PositionMapManager();
	bool Initialize(char*, int);
	D3DXVECTOR3* getPositions(TerrainClass*);
	int getPositionCount();
private:
	bool LoadPositionMap(char*);
	int posCount;
	PositionMapType* m_PositionMap;
};

