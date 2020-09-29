#include "PositionMapManager.h"



PositionMapManager::PositionMapManager()
{
}


PositionMapManager::~PositionMapManager()
{
}

bool PositionMapManager::Initialize(char* positionMap, int countText)
{
	bool result;
	result = LoadPositionMap(positionMap);
	if (!result)
	{
		return false;
	}

	return true;
}

bool PositionMapManager::LoadPositionMap(char* filename)
{
	FILE* filePtr;
	int error;
	unsigned int count;
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	int imageSize, i, j, k, index;
	unsigned char* bitmapImage;
	unsigned int height, width;

	// Open the position map file in binary.
	error = fopen_s(&filePtr, filename, "rb");
	if (error != 0)
	{
		return false;
	}

	// Read in the file header.
	count = fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	if (count != 1)
	{
		return false;
	}

	// Read in the bitmap info header.
	count = fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	if (count != 1)
	{
		return false;
	}

	// Save the dimensions of the terrain.
	width = bitmapInfoHeader.biWidth;
	height = bitmapInfoHeader.biHeight;

	imageSize = width * height * 3;

	// Allocate memory for the bitmap image data.
	bitmapImage = new unsigned char[imageSize];
	if (!bitmapImage)
	{
		return false;
	}

	// Allocate memory for the bitmap image data.
	bitmapImage = new unsigned char[imageSize];
	if (!bitmapImage)
	{
		return false;
	}

	// Read in the bitmap image data.
	count = fread(bitmapImage, 1, imageSize, filePtr);
	if (count != imageSize)
	{
		return false;
	}

	// Close the file.
	error = fclose(filePtr);
	if (error != 0)
	{
		return false;
	}

	m_PositionMap = new PositionMapType[width * height];
	if (!m_PositionMap)
	{
		return false;
	}

	k = 0;
	posCount = 0;

	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			if (bitmapImage[k] == 0 && bitmapImage[k + 1] == 0 && bitmapImage[k + 2] == 0)
			{
				m_PositionMap[posCount].x = (float)i;
				m_PositionMap[posCount].y = 0;
				m_PositionMap[posCount].z = (float)j;
				posCount++;
			}

			k += 3;
		}
	}

	// Release the bitmap image data.
	delete[] bitmapImage;
	bitmapImage = 0;

	return true;
}

D3DXVECTOR3* PositionMapManager::getPositions(TerrainClass* m_Terrain)
{
	D3DXVECTOR3* positions = new D3DXVECTOR3[posCount];
	for (int i = 0; i < posCount; i++)
	{
		m_Terrain->GetHeightAtPosition(m_PositionMap[i].x, m_PositionMap[i].z, m_PositionMap[i].y);
		positions[i].x = m_PositionMap[i].x;
		positions[i].y = m_PositionMap[i].y - 1.5;
		positions[i].z = m_PositionMap[i].z;
	}

	return positions;
}

int PositionMapManager::getPositionCount()
{
	return posCount;
}
