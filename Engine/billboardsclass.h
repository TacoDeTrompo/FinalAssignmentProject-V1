#pragma once
#include "modelclass.h"
class billboardsclass :
	public ModelClass
{
protected:
	bool Estrategia();
public:
	billboardsclass();
	~billboardsclass();

	static D3DXMATRIX generateWorldMAtrix(D3DXVECTOR3, D3DXVECTOR3);
};

