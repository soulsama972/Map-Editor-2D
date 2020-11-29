#pragma once
#pragma warning (push)
#pragma warning (disable : 26495)
#pragma warning (disable : 4005)
#include<windows.h>
#include<iostream>
#include<string>
#include<fstream>
#include"Math.hpp"
#include"utill.hpp"
#include<D3D11.h>
#include<D3DX11.h>


#pragma warning(pop)

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")







template<typename T>
class Model11
{
public:
	~Model11();
	Model11() = default;

	void AddInstance(T in);
	void ClearInstance();

	void Draw();
	void InitBuffer(ID3D11Device* dev, ID3D11DeviceContext* devcon, void* pVertex, void* pIndex, UINT vertexLen, UINT indexLen, UINT maxInstance,D3D11_PRIMITIVE_TOPOLOGY topology, UINT vertexByteWidth, UINT instanceByteWidth);
	void InitializeShaders(const char* vertexSrcFile, const char* vertexFunctionMainName, const char* pixelSrcFile, const char* pixelFunctionMainName, D3D11_INPUT_ELEMENT_DESC* InputElementDesc, UINT32 InputElementDescCount);

protected:
	ID3D11InputLayout* layout = 0;
	ID3D11VertexShader* vertexShader = 0;
	ID3D11PixelShader* pixelShader = 0;

private:
	T* instance = nullptr;
	void CleanUp();

	ID3D11Buffer* vertexBuffer = 0;
	ID3D11Buffer* indexBuffer = 0;
	ID3D11Buffer* instanceBuffer = 0;

	UINT maxInstance = 0;
	UINT instanceCount = 0;

	UINT indexLen = 0;
	UINT vertexLen = 0;
	UINT vertexStride = 0;
	UINT instanceStride = 0;

	ID3D11Device* dev = 0;
	ID3D11DeviceContext* devcon = 0;

	D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
};



template<typename T>
Model11<T>::~Model11()
{
	CleanUp();
}

template<typename T>
void Model11<T>::InitBuffer(ID3D11Device* dev, ID3D11DeviceContext* devcon,void * pVertex, void* pIndex,UINT vertexLen,UINT indexLen,UINT maxInstance, D3D11_PRIMITIVE_TOPOLOGY topology,UINT vertexByteWidth,UINT instanceByteWidth)
{

	this->dev = dev;
	this->devcon = devcon;
	this->indexLen = indexLen;
	this->vertexLen = vertexLen;
	this->topology = topology;

	this->maxInstance = maxInstance;
	this->instance = new T[maxInstance];

	this->vertexStride = vertexByteWidth;
	this->instanceStride = instanceByteWidth;
	CheckAlloc(instance)

	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc, instanceBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = vertexByteWidth * vertexLen;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = pVertex;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	CheckFAILED(dev->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer))
	
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned int) * indexLen;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = pIndex;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	CheckFAILED(dev->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer))

	instanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	instanceBufferDesc.ByteWidth = instanceByteWidth * maxInstance;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	// Create the instance buffer.
	CheckFAILED(dev->CreateBuffer(&instanceBufferDesc, NULL, &instanceBuffer))
}

template<typename T>
void Model11<T>::InitializeShaders(const char* vertexSrcFile, const char* vertexFunctionMainName, const char* pixelSrcFile, const char* pixelFunctionMainName, D3D11_INPUT_ELEMENT_DESC* InputElementDesc, UINT32 InputElementDescCount)
{
	HRESULT result = 0;
	ID3D10Blob* vertexShaderBuffer = 0;
	ID3D10Blob* pixelShaderBuffer = 0;
	ID3D10Blob* errorMessage = 0;
	unsigned int numElements = 0;

	auto OutputShaderErrorMessage = [](ID3D10Blob * errorMessage, HWND hwnd)
	{
		char* compileErrors;
		size_t bufferSize, i;
		std::ofstream fout;


		// Get a pointer to the error message text buffer.
		compileErrors = (char*)(errorMessage->GetBufferPointer());

		// Get the length of the message.
		bufferSize = errorMessage->GetBufferSize();

		// Open a file to write the error message to.
		fout.open("shader-error.txt");

		// Write out the error message.
		for (i = 0; i < bufferSize; i++)
		{
			fout << compileErrors[i];
		}

		// Close the file.
		fout.close();

		// Release the error message.
		errorMessage->Release();
		errorMessage = 0;

		// Pop a message up on the screen to notify the user to check the text file for compile errors.
		MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", L"", MB_OK);
	};

	result = D3DX11CompileFromFileA(vertexSrcFile, 0, 0,vertexFunctionMainName, "vs_5_0", 0, 0, 0, &vertexShaderBuffer, &errorMessage, 0);
	if (FAILED(result))
	{
		if (errorMessage)
			OutputShaderErrorMessage(errorMessage, 0);
		else
			MessageBox(0, L"", L"Missing Shader vertex", MB_OK);
		exit(-1);
	}

	result = D3DX11CompileFromFileA(pixelSrcFile, 0, 0, pixelFunctionMainName, "ps_5_0", 0, 0, 0, &pixelShaderBuffer, &errorMessage, 0);
	if (FAILED(result))
	{

		MessageBox(0, L"", L"error Shader pixel ", MB_OK);
		exit(-1);
	}
	result = dev->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &vertexShader);
	if (FAILED(result))
	{
		MessageBox(0, L"", L"create Shader vertex ", MB_OK);
		exit(-1);
	}
	// Create the pixel shader from the buffer.
	CheckFAILED(dev->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &pixelShader))

	// Create the vertex input layout.
	CheckFAILED(dev->CreateInputLayout(InputElementDesc,InputElementDescCount, vertexShaderBuffer->GetBufferPointer(),vertexShaderBuffer->GetBufferSize(), &layout))
	SafeDelete(vertexShaderBuffer);
	SafeDelete(pixelShaderBuffer);
}



template<typename T>
void Model11<T>::Model11::CleanUp()
{
	SafeDelete(indexBuffer);
	SafeDelete(vertexBuffer);
	SafeDelete(instanceBuffer);
	SafeDelete(vertexShader);
	SafeDelete(pixelShader);
	SafeDelete(layout);
	SafeDeletePtrArr(instance)


}

template<typename T>
void Model11<T>::AddInstance(T in)
{
	if (instanceCount < maxInstance)
	{
		instance[instanceCount++] = in;
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		void* dataPtr;
		unsigned int bufferNumber = 0;
		devcon->Map(instanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		dataPtr = mappedResource.pData;

		memcpy(dataPtr, instance, (UINT)instanceStride * (UINT)instanceCount);

		devcon->Unmap(instanceBuffer, 0);
	}
}

template<typename T>
void Model11<T>::ClearInstance()
{
	instanceCount = 0;
}

template<typename T>
void Model11<T>::Model11::Draw()
{
	unsigned int stride[] = { vertexStride,instanceStride };
	unsigned int offset[] = { 0,0 };
	ID3D11Buffer* bufferPointers[] = { vertexBuffer ,instanceBuffer };
;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	devcon->IASetVertexBuffers(0, 2, bufferPointers, stride, offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	devcon->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	devcon->IASetPrimitiveTopology(topology);

	// Set the vertex input layout.
	devcon->IASetInputLayout(layout);

	// Set the vertex and pixel shaders that will be used to render.
	devcon->VSSetShader(vertexShader, NULL, 0);
	devcon->PSSetShader(pixelShader, NULL, 0);
	
	
	// Render.
	devcon->DrawIndexedInstanced(indexLen, instanceCount, 0, 0, 0);
}



