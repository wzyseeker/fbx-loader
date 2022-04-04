#pragma once
#include"d3dx12.h"
#include<wrl.h>
#include"DDSTextureLoader.h"

using namespace DirectX;
using namespace Microsoft::WRL;

class C共享资源
{
public:
	ComPtr<ID3D12Resource> 白贴图 = nullptr;

	void 加载贴图();

	C共享资源(ComPtr<ID3D12Device> 设备, ComPtr<ID3D12GraphicsCommandList> 命令队列);
	~C共享资源();

private:
	ComPtr<ID3D12Device> 设备 = nullptr;
	ComPtr<ID3D12GraphicsCommandList> 命令队列 = nullptr;
	ComPtr<ID3D12Resource> 白贴图上传 = nullptr;
};