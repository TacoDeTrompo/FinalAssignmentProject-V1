#include "sphere.h"



sphere::sphere()
{
	radiongo = 0;
}

sphere::sphere(float ratio)
{
	radiongo = ratio;
}


sphere::~sphere()
{
}

void sphere::setRadiongo(float ratio)
{
	radiongo = ratio;
	Estrategia();
}

bool sphere::Estrategia() {
	int slices = 10;
	int stacks = 10;
	float ratio = 2.0;
	if (radiongo != 0)
	{
		ratio = radiongo;
	}
	float inicio = 0;
	float final = 1;

	m_vertexCount = slices * stacks;
	m_indexCount = (slices - 1)*(stacks - 1) * 6;

	//Create the vertex array
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
		return false;

	//Create the index array
	indices = new unsigned long[m_indexCount];
	if (!indices)
		return false;



	for (int i = 0; i < slices; i++)
	{
		for (int j = 0; j < stacks; j++)
		{
			int indice = (i * stacks + j);

			vertices[indice].position.x = ratio * cos(((double)j / (stacks - 1))*(D3DX_PI*(final - inicio)) + D3DX_PI * inicio - D3DX_PI / 2.0)*cos(2.0*D3DX_PI*(double)i / (slices - 1));
			vertices[indice].position.y = ratio * sin(((double)j / (stacks - 1))*(D3DX_PI*(final - inicio)) + D3DX_PI * inicio - D3DX_PI / 2.0);
			vertices[indice].position.z = ratio * cos(((double)j / (stacks - 1))*(D3DX_PI*(final - inicio)) + D3DX_PI * inicio - D3DX_PI / 2.0)*sin(2.0*D3DX_PI*(double)i / (slices - 1));

			vertices[indice].normal.x = cos(((double)j / (stacks - 1))*(D3DX_PI*(final - inicio)) + D3DX_PI * inicio - D3DX_PI / 2.0)* cos(2.0*D3DX_PI*(double)i / (slices - 1));
			vertices[indice].normal.y = sin(((double)j / (stacks - 1))*(D3DX_PI*(final - inicio)) + D3DX_PI * inicio - D3DX_PI / 2.0);
			vertices[indice].normal.z = cos(((double)j / (stacks - 1))*(D3DX_PI*(final - inicio)) + D3DX_PI * inicio - D3DX_PI / 2.0)* sin(2.0*D3DX_PI*(double)i / (slices - 1));

			vertices[indice].texture.x = (1 - (double)i / (stacks - 1));
			vertices[indice].texture.y = (1 - (double)j / (slices - 1));
		}
	}

	int index = 0, index1 = 0, index2 = 0, index3 = 0, index4 = 0;

	for (int i = 0; i < slices - 1; i++)
	{
		for (int j = 0; j < stacks - 1; j++)
		{
			index1 = (stacks *   i) + j;    // Bottom left.
			index2 = (stacks *   i) + (j + 1);  // Bottom right.
			index3 = (stacks * (i + 1)) + j;    // Upper left.
			index4 = (stacks * (i + 1)) + (j + 1);  // Upper right.

			indices[index++] = index1;
			indices[index++] = index2;
			indices[index++] = index4;

			indices[index++] = index1;
			indices[index++] = index4;
			indices[index++] = index3;
		}
	}
}
