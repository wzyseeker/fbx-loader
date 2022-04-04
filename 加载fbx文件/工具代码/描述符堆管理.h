#pragma once
#include<wrl.h>
#include"d3dx12.h"
#include<vector>
#include<string>
#include<map>
#include"共享资源.h"

using namespace Microsoft::WRL;
using namespace std;

class C描述符堆管理
{
public:
	enum E类型
	{
		srv,
		uav
	};

	struct S资源描述
	{
		E类型 类型;
		void* 资源描述;
		ComPtr<ID3D12Resource> 资源;
		D3D12_CPU_DESCRIPTOR_HANDLE hCPU描述符;
		D3D12_GPU_DESCRIPTOR_HANDLE hGPU描述符;

		S资源描述()
		{
			资源描述 = nullptr;
			资源 = nullptr;
		}
		~S资源描述()
		{
			delete 资源描述;
		}
	};

	ComPtr<ID3D12DescriptorHeap> 描述符堆;
	map<wstring, S资源描述*> 资源描述;
	int 单个描述符大小 = 0;

	void 加入srv描述符(ComPtr<ID3D12Resource> 资源, wstring 资源名称, D3D12_SHADER_RESOURCE_VIEW_DESC* srv资源描述);
	void 加入uav描述符(ComPtr<ID3D12Resource> 资源, wstring 资源名称, D3D12_UNORDERED_ACCESS_VIEW_DESC* uav资源描述);
	void 生成描述符堆();  //在所有描述符加入完毕后使用
	void 删除描述符(wstring 描述符名称);
	int 描述符数量();

	C描述符堆管理(ComPtr<ID3D12Device> 设备, C共享资源* 共享资源);
	~C描述符堆管理();

private:
	ComPtr<ID3D12Device> 设备;
	C共享资源* 共享资源;
};