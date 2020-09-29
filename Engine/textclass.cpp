///////////////////////////////////////////////////////////////////////////////
// Filename: textclass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "textclass.h"


TextClass::TextClass()
{
	m_Font = 0;
	m_sentence1 = 0;		// MENU
	m_sentence2 = 0;		// OPCION1: REINICIAR
	m_sentence3 = 0;		// OPCION2: SALIR
	m_sentence4 = 0;		// MENSAJE HAS GANADO
	m_sentence5 = 0;		// MENSAJE HAS PERDIDO
	m_sentence6 = 0;		// HP
	m_sentence7 = 0;		// Coconuts
	m_sentence8 = 0;		// Pineapples
	m_sentence9 = 0;
	m_sentence10 = 0;
	m_Number0 = 0;
	m_Number1 = 0;
	m_Number2 = 0;
	m_Number3 = 0;
	m_Number4 = 0;
	m_Number5 = 0;
	m_Number6 = 0;
	m_Number7 = 0;
	m_Number8 = 0;
	m_Number9 = 0;
}


TextClass::TextClass(const TextClass& other)
{
}


TextClass::~TextClass()
{
}


bool TextClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, HWND hwnd, int screenWidth, int screenHeight, 
						   D3DXMATRIX baseViewMatrix)
{
	bool result;


	// Store the screen width and height for calculating pixel location during the sentence updates.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Store the base view matrix for 2D text rendering.
	m_baseViewMatrix = baseViewMatrix;

	// Create the font object.
	m_Font = new FontClass;
	if(!m_Font)
	{
		return false;
	}

	// Initialize the font object.
	result = m_Font->Initialize(device, "../Engine/data/fontdata.txt", L"../Engine/data/font.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the font object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the first sentence.
	result = InitializeSentence(&m_sentence1, 150, device);
	if(!result)
	{
		return false;
	}

	// Initialize the second sentence.
	result = InitializeSentence(&m_sentence2, 150, device);
	if(!result)
	{
		return false;
	}

	// Initialize the third sentence.
	result = InitializeSentence(&m_sentence3, 150, device);
	if(!result)
	{
		return false;
	}

	// Initialize the fourth sentence.
	result = InitializeSentence(&m_sentence4, 150, device);
	if(!result)
	{
		return false;
	}

	// Initialize the fifth sentence.
	result = InitializeSentence(&m_sentence5, 150, device);
	if(!result)
	{
		return false;
	}

	// Initialize the sixth sentence.
	result = InitializeSentence(&m_sentence6, 150, device);
	if(!result)
	{
		return false;
	}

	// Initialize the seventh sentence.
	result = InitializeSentence(&m_sentence7, 150, device);
	if(!result)
	{
		return false;
	}

	// Initialize the eighth sentence.
	result = InitializeSentence(&m_sentence8, 150, device);
	if(!result)
	{
		return false;
	}

	// Initialize the ninth sentence.
	result = InitializeSentence(&m_sentence9, 150, device);
	if(!result)
	{
		return false;
	}

	// Initialize the tenth sentence.
	result = InitializeSentence(&m_sentence10, 150, device);
	if(!result)
	{
		return false;
	}

	result = InitializeSentence(&m_Number0, 150, device);
	if (!result)
	{
		return false;
	}

	result = InitializeSentence(&m_Number1, 150, device);
	if (!result)
	{
		return false;
	}

	result = InitializeSentence(&m_Number2, 150, device);
	if (!result)
	{
		return false;
	}

	result = InitializeSentence(&m_Number3, 150, device);
	if (!result)
	{
		return false;
	}

	result = InitializeSentence(&m_Number4, 150, device);
	if (!result)
	{
		return false;
	}

	result = InitializeSentence(&m_Number5, 150, device);
	if (!result)
	{
		return false;
	}

	result = InitializeSentence(&m_Number6, 150, device);
	if (!result)
	{
		return false;
	}

	result = InitializeSentence(&m_Number7, 150, device);
	if (!result)
	{
		return false;
	}

	result = InitializeSentence(&m_Number8, 150, device);
	if (!result)
	{
		return false;
	}

	result = InitializeSentence(&m_Number9, 150, device);
	if (!result)
	{
		return false;
	}

	char dataString[150];
	strcpy(dataString, "MENU");
	result = UpdateSentence(m_sentence1, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	strcpy(dataString, "REINICIAR");
	result = UpdateSentence(m_sentence2, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	strcpy(dataString, "SALIR");
	result = UpdateSentence(m_sentence3, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	strcpy(dataString, "GANASTE");
	result = UpdateSentence(m_sentence4, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	strcpy(dataString, "PERDISTE");
	result = UpdateSentence(m_sentence5, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	strcpy(dataString, "HP");
	result = UpdateSentence(m_sentence6, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	strcpy(dataString, "Coconuts");
	result = UpdateSentence(m_sentence7, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	strcpy(dataString, "Pineapples");
	result = UpdateSentence(m_sentence8, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	strcpy(dataString, "0");
	result = UpdateSentence(m_Number0, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	strcpy(dataString, "1");
	result = UpdateSentence(m_Number1, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	strcpy(dataString, "2");
	result = UpdateSentence(m_Number2, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	strcpy(dataString, "3");
	result = UpdateSentence(m_Number3, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	strcpy(dataString, "4");
	result = UpdateSentence(m_Number4, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	strcpy(dataString, "5");
	result = UpdateSentence(m_Number5, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	strcpy(dataString, "6");
	result = UpdateSentence(m_Number6, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	strcpy(dataString, "7");
	result = UpdateSentence(m_Number7, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	strcpy(dataString, "8");
	result = UpdateSentence(m_Number8, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	strcpy(dataString, "9");
	result = UpdateSentence(m_Number9, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}


void TextClass::Shutdown()
{
	// Release the font object.
	if(m_Font)
	{
		m_Font->Shutdown();
		delete m_Font;
		m_Font = 0;
	}

	// Release the sentences.
	ReleaseSentence(&m_sentence1);
	ReleaseSentence(&m_sentence2);
	ReleaseSentence(&m_sentence3);
	ReleaseSentence(&m_sentence4);
	ReleaseSentence(&m_sentence5);
	ReleaseSentence(&m_sentence6);
	ReleaseSentence(&m_sentence7);
	ReleaseSentence(&m_sentence8);
	ReleaseSentence(&m_sentence9);
	ReleaseSentence(&m_sentence10);
	ReleaseSentence(&m_Number0);
	ReleaseSentence(&m_Number1);
	ReleaseSentence(&m_Number2);
	ReleaseSentence(&m_Number3);
	ReleaseSentence(&m_Number4);
	ReleaseSentence(&m_Number5);
	ReleaseSentence(&m_Number6);
	ReleaseSentence(&m_Number7);
	ReleaseSentence(&m_Number8);
	ReleaseSentence(&m_Number9);

	return;
}


bool TextClass::Render(ID3D11DeviceContext* deviceContext, FontShaderClass* FontShader, D3DXMATRIX worldMatrix, D3DXMATRIX orthoMatrix, bool menu, bool gameover, bool ganaroperder, int life, int cocoAmmo, int pineAmmo, int timer)
{
	bool result;
	D3DXMATRIX scall, MC, transtext;
	char dataString[150];
	
	if (menu)
	{
		D3DXMatrixScaling(&scall, 3.0f, 3.0f, 0.0f);
		D3DXMatrixTranslation(&transtext, -200.0f, 200.0f, 0.0f);
		MC = scall * transtext;
		// Draw the sentences.
		result = RenderSentence(m_sentence1, deviceContext, FontShader, MC, orthoMatrix);
		if (!result)
		{
			return false;
		}

		D3DXMatrixScaling(&scall, 3.0f, 3.0f, 0.0f);
		D3DXMatrixTranslation(&transtext, -200.0f, 150.0f, 0.0f);
		MC = scall * transtext;
		result = RenderSentence(m_sentence2, deviceContext, FontShader, MC, orthoMatrix);
		if (!result)
		{
			return false;
		}

		D3DXMatrixScaling(&scall, 3.0f, 3.0f, 0.0f);
		D3DXMatrixTranslation(&transtext, -200.0f, 100.0f, 0.0f);
		MC = scall * transtext;
		result = RenderSentence(m_sentence3, deviceContext, FontShader, MC, orthoMatrix);
		if (!result)
		{
			return false;
		}
	}

	if (gameover)
	{
		D3DXMatrixScaling(&scall, 4.0f, 4.0f, 0.0f);
		D3DXMatrixTranslation(&transtext, -100.0f, 0.0f, 0.0f);
		MC = scall * transtext;

		if (ganaroperder)
		{
			result = RenderSentence(m_sentence4, deviceContext, FontShader, MC, orthoMatrix);
			if (!result)
			{
				return false;
			}
		}
		else
		{
			result = RenderSentence(m_sentence5, deviceContext, FontShader, MC, orthoMatrix);
			if (!result)
			{
				return false;
			}
		}
	}

	if (!menu && !gameover)
	{
		D3DXMatrixScaling(&scall, 3.0f, 3.0f, 0.0f);
		D3DXMatrixTranslation(&transtext, -350.0f, -230.0f, 0.0f);
		MC = scall * transtext;
		result = RenderSentence(m_sentence6, deviceContext, FontShader, MC, orthoMatrix);
		if (!result)
		{
			return false;
		}

		_itoa_s(life, dataString, 10);
		result = UpdateSentence(m_Number0, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
		if (!result)
		{
			return false;
		}
		D3DXMatrixScaling(&scall, 3.0f, 3.0f, 0.0f);
		D3DXMatrixTranslation(&transtext, -250.0f, -230.0f, 0.0f);
		MC = scall * transtext;
		result = RenderSentence(m_Number0, deviceContext, FontShader, MC, orthoMatrix);
		if (!result)
		{
			return false;
		}

		D3DXMatrixScaling(&scall, 3.0f, 3.0f, 0.0f);
		D3DXMatrixTranslation(&transtext, 150.0f, -170.0f, 0.0f);
		MC = scall * transtext;
		result = RenderSentence(m_sentence7, deviceContext, FontShader, MC, orthoMatrix);
		if (!result)
		{
			return false;
		}

		_itoa_s(cocoAmmo, dataString, 10);
		result = UpdateSentence(m_Number1, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
		if (!result)
		{
			return false;
		}
		D3DXMatrixScaling(&scall, 3.0f, 3.0f, 0.0f);
		D3DXMatrixTranslation(&transtext, 325.0f, -170.0f, 0.0f);
		MC = scall * transtext;
		result = RenderSentence(m_Number1, deviceContext, FontShader, MC, orthoMatrix);
		if (!result)
		{
			return false;
		}

		D3DXMatrixScaling(&scall, 3.0f, 3.0f, 0.0f);
		D3DXMatrixTranslation(&transtext, 150.0f, -230.0f, 0.0f);
		MC = scall * transtext;
		result = RenderSentence(m_sentence8, deviceContext, FontShader, MC, orthoMatrix);
		if (!result)
		{
			return false;
		}

		_itoa_s(pineAmmo, dataString, 10);
		result = UpdateSentence(m_Number2, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
		if (!result)
		{
			return false;
		}
		D3DXMatrixScaling(&scall, 3.0f, 3.0f, 0.0f);
		D3DXMatrixTranslation(&transtext, 325.0f, -230.0f, 0.0f);
		MC = scall * transtext;
		result = RenderSentence(m_Number2, deviceContext, FontShader, MC, orthoMatrix);
		if (!result)
		{
			return false;
		}

		_itoa_s(timer, dataString, 10);
		result = UpdateSentence(m_Number3, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
		if (!result)
		{
			return false;
		}
		D3DXMatrixScaling(&scall, 5.0f, 5.0f, 0.0f);
		D3DXMatrixTranslation(&transtext, -25.0f, 290.0f, 0.0f);
		MC = scall * transtext;
		result = RenderSentence(m_Number3, deviceContext, FontShader, MC, orthoMatrix);
		if (!result)
		{
			return false;
		}
	}

	

	//D3DXMatrixScaling(&scall, 3.0f, 3.0f, 0.0f);
	//D3DXMatrixTranslation(&transtext, -200.0f, 200.0f, 0.0f);
	//MC = scall * transtext;
	//result = RenderSentence(m_sentence7, deviceContext, FontShader, MC, orthoMatrix);
	//if(!result)
	//{
	//	return false;
	//}
	//
	//D3DXMatrixScaling(&scall, 3.0f, 3.0f, 0.0f);
	//D3DXMatrixTranslation(&transtext, 200.0f, -200.0f, 0.0f);
	//MC = scall * transtext;
	//result = RenderSentence(m_sentence8, deviceContext, FontShader, MC, orthoMatrix);
	//if(!result)
	//{
	//	return false;
	//}
	//
	//D3DXMatrixScaling(&scall, 3.0f, 3.0f, 0.0f);
	//D3DXMatrixTranslation(&transtext, 200.0f, 200.0f, 0.0f);
	//MC = scall * transtext;
	//result = RenderSentence(m_sentence9, deviceContext, FontShader, MC, orthoMatrix);
	//if(!result)
	//{
	//	return false;
	//}
	//D3DXMatrixScaling(&scall, 3.0f, 3.0f, 0.0f);
	//D3DXMatrixTranslation(&transtext, -200.0f, -200.0f, 0.0f);
	//MC = scall * transtext;
	//result = RenderSentence(m_sentence10, deviceContext, FontShader, MC, orthoMatrix);
	//if(!result)
	//{
	//	return false;
	//}

	return true;
}


bool TextClass::InitializeSentence(SentenceType** sentence, int maxLength, ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;


	// Create a new sentence object.
	*sentence = new SentenceType;
	if(!*sentence)
	{
		return false;
	}

	// Initialize the sentence buffers to null.
	(*sentence)->vertexBuffer = 0;
	(*sentence)->indexBuffer = 0;

	// Set the maximum length of the sentence.
	(*sentence)->maxLength = maxLength;

	// Set the number of vertices in the vertex array.
	(*sentence)->vertexCount = 6 * maxLength;

	// Set the number of indexes in the index array.
	(*sentence)->indexCount = (*sentence)->vertexCount;

	// Create the vertex array.
	vertices = new VertexType[(*sentence)->vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[(*sentence)->indexCount];
	if(!indices)
	{
		return false;
	}

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * (*sentence)->vertexCount));

	// Initialize the index array.
	for(i=0; i<(*sentence)->indexCount; i++)
	{
		indices[i] = i;
	}

	// Set up the description of the dynamic vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * (*sentence)->vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &(*sentence)->vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * (*sentence)->indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &(*sentence)->indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the vertex array as it is no longer needed.
	delete [] vertices;
	vertices = 0;

	// Release the index array as it is no longer needed.
	delete [] indices;
	indices = 0;

	return true;
}


bool TextClass::UpdateSentence(SentenceType* sentence, char* text, int positionX, int positionY, float red, float green, float blue,
							   ID3D11DeviceContext* deviceContext)
{
	int numLetters;
	VertexType* vertices;
	float drawX, drawY;
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;


	// Store the color of the sentence.
	sentence->red = red;
	sentence->green = green;
	sentence->blue = blue;

	// Get the number of letters in the sentence.
	numLetters = (int)strlen(text);

	// Check for possible buffer overflow.
	if(numLetters > sentence->maxLength)
	{
		return false;
	}

	// Create the vertex array.
	vertices = new VertexType[sentence->vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * sentence->vertexCount));

	// Calculate the X and Y pixel position on the screen to start drawing to.

	// Use the font class to build the vertex array from the sentence text and sentence draw location.
	//drawX = (float)(((m_screenWidth / 2) * -1) + positionX);
	//drawY = (float)((m_screenHeight / 2) - positionY);

	drawX = 0;
	drawY = 0;
	

	m_Font->BuildVertexArray((void*)vertices, text, drawX, drawY);

	// Lock the vertex buffer so it can be written to.
	result = deviceContext->Map(sentence->vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the vertex buffer.
	verticesPtr = (VertexType*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * sentence->vertexCount));

	// Unlock the vertex buffer.
	deviceContext->Unmap(sentence->vertexBuffer, 0);

	// Release the vertex array as it is no longer needed.
	delete [] vertices;
	vertices = 0;

	return true;
}


void TextClass::ReleaseSentence(SentenceType** sentence)
{
	if(*sentence)
	{
		// Release the sentence vertex buffer.
		if((*sentence)->vertexBuffer)
		{
			(*sentence)->vertexBuffer->Release();
			(*sentence)->vertexBuffer = 0;
		}

		// Release the sentence index buffer.
		if((*sentence)->indexBuffer)
		{
			(*sentence)->indexBuffer->Release();
			(*sentence)->indexBuffer = 0;
		}

		// Release the sentence.
		delete *sentence;
		*sentence = 0;
	}

	return;
}


bool TextClass::RenderSentence(SentenceType* sentence, ID3D11DeviceContext* deviceContext, FontShaderClass* FontShader, D3DXMATRIX worldMatrix, 
							   D3DXMATRIX orthoMatrix)
{
	unsigned int stride, offset;
	D3DXVECTOR4 pixelColor;
	bool result;


	// Set vertex buffer stride and offset.
    stride = sizeof(VertexType); 
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &sentence->vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(sentence->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Create a pixel color vector with the input sentence color.
	pixelColor = D3DXVECTOR4(sentence->red, sentence->green, sentence->blue, 1.0f);

	// Render the text using the font shader.
	result = FontShader->Render(deviceContext, sentence->indexCount, worldMatrix, m_baseViewMatrix, orthoMatrix, m_Font->GetTexture(), pixelColor);
	if(!result)
	{
		false;
	}

	return true;
}


bool TextClass::SetVideoCardInfo(char* videoCardName, int videoCardMemory, ID3D11DeviceContext* deviceContext)
{
	char dataString[150];
	bool result;
	char tempString[16];
	char memoryString[32];


	// Setup the video card name string.
	strcpy_s(dataString, "Video Card: ");
	strcat_s(dataString, videoCardName);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence1, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	// Truncate the memory value to prevent buffer over flow.
	if(videoCardMemory > 9999999)
	{
		videoCardMemory = 9999999;
	}

	// Convert the video memory integer value to a string format.
	_itoa_s(videoCardMemory, tempString, 10);

	// Setup the video memory string.
	strcpy_s(memoryString, "Video Memory: ");
	strcat_s(memoryString, tempString);
	strcat_s(memoryString, " MB");

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence2, memoryString, 10, 30, 1.0f, 1.0f, 1.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	return true;
}


bool TextClass::SetFps(int fps, ID3D11DeviceContext* deviceContext)
{
	char tempString[16];
	char fpsString[16];
	bool result;


	// Truncate the fps to prevent a buffer over flow.
	if(fps > 9999)
	{
		fps = 9999;
	}

	// Convert the fps integer to string format.
	_itoa_s(fps, tempString, 10);

	// Setup the fps string.
	strcpy_s(fpsString, "Fps: ");
	strcat_s(fpsString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence3, fpsString, 10, 70, 0.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	return true;
}


bool TextClass::SetCpu(int cpu, ID3D11DeviceContext* deviceContext)
{
	char tempString[16];
	char cpuString[16];
	bool result;


	// Convert the cpu integer to string format.
	_itoa_s(cpu, tempString, 10);

	// Setup the cpu string.
	strcpy_s(cpuString, "Cpu: ");
	strcat_s(cpuString, tempString);
	strcat_s(cpuString, "%");

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence4, cpuString, 10, 90, 0.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	return true;
}


bool TextClass::SetCameraPosition(float posX, float posY, float posZ, ID3D11DeviceContext* deviceContext)
{
	int positionX, positionY, positionZ;
	char tempString[16];
	char dataString[16];
	bool result;


	// Convert the position from floating point to integer.
	positionX = (int)posX;
	positionY = (int)posY;
	positionZ = (int)posZ;

	// Truncate the position if it exceeds either 9999 or -9999.
	if(positionX > 9999) { positionX = 9999; }
	if(positionY > 9999) { positionY = 9999; }
	if(positionZ > 9999) { positionZ = 9999; }

	if(positionX < -9999) { positionX = -9999; }
	if(positionY < -9999) { positionY = -9999; }
	if(positionZ < -9999) { positionZ = -9999; }

	// Setup the X position string.
	_itoa_s(positionX, tempString, 10);
	strcpy_s(dataString, "X: ");
	strcat_s(dataString, tempString);

	result = UpdateSentence(m_sentence5, dataString, 10, 130, 0.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}
	
	// Setup the Y position string.
	_itoa_s(positionY, tempString, 10);
	strcpy_s(dataString, "Y: ");
	strcat_s(dataString, tempString);

	result = UpdateSentence(m_sentence6, dataString, 10, 150, 0.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	// Setup the Z position string.
	_itoa_s(positionZ, tempString, 10);
	strcpy_s(dataString, "Z: ");
	strcat_s(dataString, tempString);

	result = UpdateSentence(m_sentence7, dataString, 10, 170, 0.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	return true;
}


bool TextClass::SetCameraRotation(float rotX, float rotY, float rotZ, ID3D11DeviceContext* deviceContext)
{
	int rotationX, rotationY, rotationZ;
	char tempString[16];
	char dataString[16];
	bool result;


	// Convert the rotation from floating point to integer.
	rotationX = (int)rotX;
	rotationY = (int)rotY;
	rotationZ = (int)rotZ;

	// Setup the X rotation string.
	_itoa_s(rotationX, tempString, 10);
	strcpy_s(dataString, "rX: ");
	strcat_s(dataString, tempString);

	result = UpdateSentence(m_sentence8, dataString, 10, 210, 0.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	// Setup the Y rotation string.
	_itoa_s(rotationY, tempString, 10);
	strcpy_s(dataString, "rY: ");
	strcat_s(dataString, tempString);

	result = UpdateSentence(m_sentence9, dataString, 10, 230, 0.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	// Setup the Z rotation string.
	_itoa_s(rotationZ, tempString, 10);
	strcpy_s(dataString, "rZ: ");
	strcat_s(dataString, tempString);

	result = UpdateSentence(m_sentence10, dataString, 10, 250, 0.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	return true;
}