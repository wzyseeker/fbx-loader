#include"描述符堆管理.h"

C描述符堆管理::C描述符堆管理(ComPtr<ID3D12Device> 设备, C共享资源* 共享资源)
{
	this->设备 = 设备;
	this->共享资源 = 共享资源;
	单个描述符大小 = 设备->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void C描述符堆管理::加入srv描述符(ComPtr<ID3D12Resource> 资源, wstring 资源名称, D3D12_SHADER_RESOURCE_VIEW_DESC* srv资源描述)
{
	S资源描述* 资源描述 = new S资源描述;
	资源描述->类型 = srv;
	资源描述->资源描述 = srv资源描述;
	资源描述->资源 = 资源;

	this->资源描述.insert(pair<wstring, S资源描述*>(资源名称, 资源描述));
}

void C描述符堆管理::加入uav描述符(ComPtr<ID3D12Resource> 资源, wstring 资源名称, D3D12_UNORDERED_ACCESS_VIEW_DESC* uav资源描述)
{
	S资源描述* 资源描述 = new S资源描述;
	资源描述->类型 = uav;
	资源描述->资源描述 = uav资源描述;
	资源描述->资源 = 资源;

	this->资源描述.insert(pair<wstring, S资源描述*>(资源名称, 资源描述));
}

void C描述符堆管理::生成描述符堆()
{
	描述符堆.Reset();

	D3D12_DESCRIPTOR_HEAP_DESC 描述符堆描述 = {};
	描述符堆描述.NumDescriptors = 资源描述.size();
	描述符堆描述.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	描述符堆描述.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	设备->CreateDescriptorHeap(&描述符堆描述, IID_PPV_ARGS(&描述符堆));

	CD3DX12_CPU_DESCRIPTOR_HANDLE chCPU描述符 = CD3DX12_CPU_DESCRIPTOR_HANDLE(描述符堆->GetCPUDescriptorHandleForHeapStart());
	CD3DX12_GPU_DESCRIPTOR_HANDLE chGPU描述符 = CD3DX12_GPU_DESCRIPTOR_HANDLE(描述符堆->GetGPUDescriptorHandleForHeapStart());

	map<wstring, S资源描述*>::iterator it = 资源描述.begin();

	for (int i = 0; i < 资源描述.size(); i++)
	{
		switch (it->second->类型)
		{
		case srv:
			设备->CreateShaderResourceView(it->second->资源.Get(), (D3D12_SHADER_RESOURCE_VIEW_DESC*)it->second->资源描述,
				chCPU描述符);

			it->second->hCPU描述符 = chCPU描述符;
			it->second->hGPU描述符 = chGPU描述符;

			chCPU描述符.Offset(1, 单个描述符大小);
			chGPU描述符.Offset(1, 单个描述符大小);
			break;

		case uav:
			设备->CreateUnorderedAccessView(it->second->资源.Get(), nullptr, (D3D12_UNORDERED_ACCESS_VIEW_DESC*)it->second->资源描述,
				chCPU描述符);

			it->second->hCPU描述符 = chCPU描述符;
			it->second->hGPU描述符 = chGPU描述符;

			chCPU描述符.Offset(1, 单个描述符大小);
			chGPU描述符.Offset(1, 单个描述符大小);
			break;
		}

		it++;
	}
}

int C描述符堆管理::描述符数量()
{
	return 资源描述.size();
}

void C描述符堆管理::删除描述符(wstring 描述符名称)
{
	delete 资源描述[描述符名称];
	资源描述.erase(描述符名称);
}

C描述符堆管理::~C描述符堆管理()
{
	map<wstring, S资源描述*>::iterator it = 资源描述.begin();

	for (int i = 0; i < 资源描述.size(); i++)
	{
		delete it->second;
		it++;
	}
}