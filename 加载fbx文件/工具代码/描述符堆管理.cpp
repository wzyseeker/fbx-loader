#include"�������ѹ���.h"

C�������ѹ���::C�������ѹ���(ComPtr<ID3D12Device> �豸, C������Դ* ������Դ)
{
	this->�豸 = �豸;
	this->������Դ = ������Դ;
	������������С = �豸->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void C�������ѹ���::����srv������(ComPtr<ID3D12Resource> ��Դ, wstring ��Դ����, D3D12_SHADER_RESOURCE_VIEW_DESC* srv��Դ����)
{
	S��Դ����* ��Դ���� = new S��Դ����;
	��Դ����->���� = srv;
	��Դ����->��Դ���� = srv��Դ����;
	��Դ����->��Դ = ��Դ;

	this->��Դ����.insert(pair<wstring, S��Դ����*>(��Դ����, ��Դ����));
}

void C�������ѹ���::����uav������(ComPtr<ID3D12Resource> ��Դ, wstring ��Դ����, D3D12_UNORDERED_ACCESS_VIEW_DESC* uav��Դ����)
{
	S��Դ����* ��Դ���� = new S��Դ����;
	��Դ����->���� = uav;
	��Դ����->��Դ���� = uav��Դ����;
	��Դ����->��Դ = ��Դ;

	this->��Դ����.insert(pair<wstring, S��Դ����*>(��Դ����, ��Դ����));
}

void C�������ѹ���::������������()
{
	��������.Reset();

	D3D12_DESCRIPTOR_HEAP_DESC ������������ = {};
	������������.NumDescriptors = ��Դ����.size();
	������������.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	������������.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	�豸->CreateDescriptorHeap(&������������, IID_PPV_ARGS(&��������));

	CD3DX12_CPU_DESCRIPTOR_HANDLE chCPU������ = CD3DX12_CPU_DESCRIPTOR_HANDLE(��������->GetCPUDescriptorHandleForHeapStart());
	CD3DX12_GPU_DESCRIPTOR_HANDLE chGPU������ = CD3DX12_GPU_DESCRIPTOR_HANDLE(��������->GetGPUDescriptorHandleForHeapStart());

	map<wstring, S��Դ����*>::iterator it = ��Դ����.begin();

	for (int i = 0; i < ��Դ����.size(); i++)
	{
		switch (it->second->����)
		{
		case srv:
			�豸->CreateShaderResourceView(it->second->��Դ.Get(), (D3D12_SHADER_RESOURCE_VIEW_DESC*)it->second->��Դ����,
				chCPU������);

			it->second->hCPU������ = chCPU������;
			it->second->hGPU������ = chGPU������;

			chCPU������.Offset(1, ������������С);
			chGPU������.Offset(1, ������������С);
			break;

		case uav:
			�豸->CreateUnorderedAccessView(it->second->��Դ.Get(), nullptr, (D3D12_UNORDERED_ACCESS_VIEW_DESC*)it->second->��Դ����,
				chCPU������);

			it->second->hCPU������ = chCPU������;
			it->second->hGPU������ = chGPU������;

			chCPU������.Offset(1, ������������С);
			chGPU������.Offset(1, ������������С);
			break;
		}

		it++;
	}
}

int C�������ѹ���::����������()
{
	return ��Դ����.size();
}

void C�������ѹ���::ɾ��������(wstring ����������)
{
	delete ��Դ����[����������];
	��Դ����.erase(����������);
}

C�������ѹ���::~C�������ѹ���()
{
	map<wstring, S��Դ����*>::iterator it = ��Դ����.begin();

	for (int i = 0; i < ��Դ����.size(); i++)
	{
		delete it->second;
		it++;
	}
}