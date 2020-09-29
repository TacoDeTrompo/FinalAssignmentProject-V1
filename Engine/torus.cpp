#include "torus.h"



torus::torus()
{
}


torus::~torus()
{
}

bool torus::Estrategia() {
	int index = 0;
	const float phix = D3DX_PI * 2.0;
	const float thetax = D3DX_PI;
	int slices = 36;
	int stacks = 36;
	float ratio1 = 2.0;
	float ratio2 = 1.0;
	int numVertexInTwoTriangles = 6;

	m_vertexCount = slices * stacks;
	m_indexCount = slices * stacks * numVertexInTwoTriangles;

	//Create the vertex array
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
		return false;

	//Create the index array
	indices = new unsigned long[m_indexCount];
	if (!indices)
		return false;

	for (int i = 0; i < stacks; i++)
	{
		float y = (float)i / (stacks - 1);
		for (int j = 0; j < slices; j++)
		{
			float x = (float)j / (slices - 1);

			vertices[index].position.x = (ratio1 + ratio2 * cos(x*phix)) * cos(y*phix);
			vertices[index].position.y = (ratio1 + ratio2 * cos(x*phix)) * sin(y*phix);
			vertices[index].position.z = ratio2 * sin(x*phix);

			vertices[index].texture.x = x;
			vertices[index].texture.y = y;

			vertices[index].normal = vertices[index].position;

			index++;
		}
	}


	index = 0;
	for (int i = 0; i < stacks - 1; i++)
	{
		for (int j = 0; j < slices - 1; j++)
		{
			int index1 = (slices *   i) + j;
			int index2 = (slices *   i) + (j + 1);
			int index3 = (slices * (i + 1)) + j;
			int index4 = (slices * (i + 1)) + (j + 1);

			indices[index++] = index1; //314
			indices[index++] = index3;
			indices[index++] = index4;

			indices[index++] = index1; //124
			indices[index++] = index4;
			indices[index++] = index2;
		}
	}
}