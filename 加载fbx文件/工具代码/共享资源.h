#pragma once
#include"d3dx12.h"
#include<wrl.h>
#include"DDSTextureLoader.h"

using namespace DirectX;
using namespace Microsoft::WRL;

class C������Դ
{
public:
	ComPtr<ID3D12Resource> ����ͼ = nullptr;

	void ������ͼ();

	C������Դ(ComPtr<ID3D12Device> �豸, ComPtr<ID3D12GraphicsCommandList> �������);
	~C������Դ();

private:
	ComPtr<ID3D12Device> �豸 = nullptr;
	ComPtr<ID3D12GraphicsCommandList> ������� = nullptr;
	ComPtr<ID3D12Resource> ����ͼ�ϴ� = nullptr;
};