////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SKYMODEL_H_
#define _SKYMODEL_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
using namespace std;


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class SkyModel
{
protected:

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	SkyModel();
	SkyModel(const SkyModel&);
	~SkyModel();

	int countText;
	WCHAR** texture;

	bool Initialize(ID3D11Device*, WCHAR**, int);
	void Shutdown(int);
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView** GetTexture(int);

	//Función agregada
protected:
	//virtual bool Estrategia(VertexType*, unsigned long*);
	virtual bool Estrategia() = 0;
	VertexType* vertices;
	unsigned long* indices;
	int m_vertexCount, m_indexCount;


private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR**, int);
	void ReleaseTexture(int);

	bool LoadModel(char*);
	void ReleaseModel();

private:
	ID3D11Buffer * m_vertexBuffer, *m_indexBuffer;
	TextureClass** m_Texture;
	ModelType* m_model;
};

#endif