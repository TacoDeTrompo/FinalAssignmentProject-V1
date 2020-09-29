#include "cone.h"



cone::cone()
{
}


cone::~cone()
{
}

bool cone::Estrategia() {
	int index = 0;
	const float fullCircle = D3DX_PI * 2.0;
	int slices = 36;
	int height = 2;
	float ratio1 = 0.0;
	float ratio2 = 2.0;
	int numVertexInTwoTriangles = 6;
	int CantOfSections = 4;

	m_vertexCount = slices * CantOfSections;
	m_indexCount = slices * CantOfSections * numVertexInTwoTriangles;

	//Create the vertex array
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
		return false;

	//Create the index array
	indices = new unsigned long[m_indexCount];
	if (!indices)
		return false;

	for (int i = 0; i < CantOfSections; i++)
	{
		for (int j = 0; j < slices; j++)
		{
			float segment = (float)j / (slices - 1);

			switch (i)
			{
			case 0:
				vertices[index].position.x = ratio2 * cos(segment*fullCircle);
				vertices[index].position.y = -height / 2;
				vertices[index].position.z = ratio2 * sin(segment*fullCircle);

				vertices[index].texture.x = segment;
				vertices[index].texture.y = 1;
				break;
			case 1:
				vertices[index].position.x = ratio1 * cos(segment*fullCircle);
				vertices[index].position.y = height / 2;
				vertices[index].position.z = ratio1 * sin(segment*fullCircle);

				vertices[index].texture.x = segment;
				vertices[index].texture.y = 0;
				break;
			case 2:
				vertices[index].position.x = 0;
				vertices[index].position.y = -height / 2;
				vertices[index].position.z = 0;

				vertices[index].texture.x = segment;
				vertices[index].texture.y = 0;
				break;
			case 3:
				vertices[index].position.x = 0;
				vertices[index].position.y = height / 2;
				vertices[index].position.z = 0;

				vertices[index].texture.x = segment;
				vertices[index].texture.y = 1;
				break;
			}
			vertices[index].normal = vertices[index].position;
			index++;
		}
	}

	index = 0;
	int indexBottom = slices;

	for (int i = 0; i < CantOfSections - 1; i++)
	{
		for (int j = 0; j < slices - 1; j++)
		{
			int index1, index2, index3, index4;
			int indexPoint = slices * (i + 1);

			switch (i)
			{
			case 0:
				index1 = j;
				index2 = j + indexBottom;
				index3 = j + indexBottom + 1;
				index4 = j + 1;
				break;
			case 1:
				index1 = j + 1;
				index2 = j + indexPoint;
				index3 = j + indexPoint + 1;
				index4 = j;

				break;
			case 2:
				index1 = j + indexBottom;
				index2 = j + indexPoint;
				index3 = j + indexPoint + 1;
				index4 = j + indexBottom + 1;

				break;
			}

			indices[index++] = index1; //314
			indices[index++] = index3;
			indices[index++] = index4;

			indices[index++] = index1; //124
			indices[index++] = index2;
			indices[index++] = index3;
		}
	}

}
