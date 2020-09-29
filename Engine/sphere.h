#pragma once
#include "modelclass.h"
class sphere :
	public ModelClass
{
public:
	sphere();
	sphere(float ratio);
	~sphere();
	void setRadiongo(float ratio);

protected:
	float radiongo;
	bool Estrategia();
};

