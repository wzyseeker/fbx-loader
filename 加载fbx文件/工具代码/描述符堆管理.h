#pragma once
#include<wrl.h>
#include"d3dx12.h"
#include<vector>
#include<string>
#include<map>
#include"������Դ.h"

using namespace Microsoft::WRL;
using namespace std;

class C�������ѹ���
{
public:
	enum E����
	{
		srv,
		uav
	};

	struct S��Դ����
	{
		E���� ����;
		void* ��Դ����;
		ComPtr<ID3D12Resource> ��Դ;
		D3D12_CPU_DESCRIPTOR_HANDLE hCPU������;
		D3D12_GPU_DESCRIPTOR_HANDLE hGPU������;

		S��Դ����()
		{
			��Դ���� = nullptr;
			��Դ = nullptr;
		}
		~S��Դ����()
		{
			delete ��Դ����;
		}
	};

	ComPtr<ID3D12DescriptorHeap> ��������;
	map<wstring, S��Դ����*> ��Դ����;
	int ������������С = 0;

	void ����srv������(ComPtr<ID3D12Resource> ��Դ, wstring ��Դ����, D3D12_SHADER_RESOURCE_VIEW_DESC* srv��Դ����);
	void ����uav������(ComPtr<ID3D12Resource> ��Դ, wstring ��Դ����, D3D12_UNORDERED_ACCESS_VIEW_DESC* uav��Դ����);
	void ������������();  //������������������Ϻ�ʹ��
	void ɾ��������(wstring ����������);
	int ����������();

	C�������ѹ���(ComPtr<ID3D12Device> �豸, C������Դ* ������Դ);
	~C�������ѹ���();

private:
	ComPtr<ID3D12Device> �豸;
	C������Դ* ������Դ;
};