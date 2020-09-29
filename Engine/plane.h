#pragma once
#include "modelclass.h"
class plane :
	public ModelClass
{
public:
	plane();
	~plane();

protected:
	bool Estrategia();
};

