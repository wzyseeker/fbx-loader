#include"�������.h"

C�������::C�������(ComPtr<ID3D12Device> �豸, ComPtr<ID3D12GraphicsCommandList> �������, C������Դ* ������Դ, C�������ѹ���* �������ѹ���)
{
	this->�豸 = �豸;
	this->������� = �������;
	this->������Դ = ������Դ;
	this->�������ѹ��� = �������ѹ���;
}

void C�������::���뾲̬����FBX(wstring ��������, const WCHAR* �ļ�·��, DXGI_FORMAT ������ʽ, float ��������)
{
	��̬����.insert(pair<wstring, C��̬����*>(��������, 0));

	��̬����[��������] = new C��̬����(�豸, �������, �������ѹ���, ������Դ);
	��̬����[��������]->����FBX�ļ�(�ļ�·��, ��������, ������ʽ, ��������);
}

void C�������::���붯̬����FBX(wstring ��������, const WCHAR* �ļ�·��, DXGI_FORMAT ������ʽ, float ��������)
{
	��̬����.insert(pair<wstring, C��̬����*>(��������, 0));

	��̬����[��������] = new C��̬����(�豸, �������, �������ѹ���, ������Դ);
	��̬����[��������]->����FBX�ļ�(�ļ�·��, ��������, ������ʽ, ��������);
}

void C�������::���뾲̬����MDS(wstring ��������, const WCHAR* �ļ�·��)
{
	��̬����.insert(pair<wstring, C��̬����*>(��������, 0));

	��̬����[��������] = new C��̬����(�豸, �������, �������ѹ���, ������Դ);
	��̬����[��������]->����mds�ļ�(�ļ�·��, ��������);
}

void C�������::���붯̬����MDD(wstring ��������, const WCHAR* �ļ�·��)
{
	��̬����.insert(pair<wstring, C��̬����*>(��������, 0));

	��̬����[��������] = new C��̬����(�豸, �������, �������ѹ���, ������Դ);
	��̬����[��������]->����mdd�ļ�(�ļ�·��, ��������);
}

void C�������::ɾ����̬����(wstring ��������)
{
	delete ��̬����[��������];
	��̬����.erase(��������);
}

void C�������::ɾ����̬����(wstring ��������)
{
	delete ��̬����[��������];
	��̬����.erase(��������);
}

/*
Sʰȡ��� C�������::�Ƿ�ѡ�о�̬(C��̬����* ����, UINT Ԫ��)
{
	Sʰȡ��� �Ƿ�ѡ��;

	�������->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(����->����->Ԫ��[Ԫ��].ʰȡ���.Get(),
		D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_COPY_SOURCE));

	�������->CopyResource(����->����->Ԫ��[Ԫ��].ʰȡ�������.Get(), ����->����->Ԫ��[Ԫ��].ʰȡ���.Get());

	�������->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(����->����->Ԫ��[Ԫ��].ʰȡ���.Get(),
		D3D12_RESOURCE_STATE_COPY_SOURCE, D3D12_RESOURCE_STATE_UNORDERED_ACCESS));

	Sʰȡ���* map��Դ = nullptr;
	����->����->Ԫ��[Ԫ��].ʰȡ�������->Map(0, nullptr, (void**)&map��Դ);

	if (map��Դ->�Ƿ�ʰȡ == 1)
	{
		�Ƿ�ѡ��.�Ƿ�ʰȡ = 1;
		�Ƿ�ѡ��.���� = map��Դ->����;

		map��Դ->�Ƿ�ʰȡ = 0;
		����->����->Ԫ��[Ԫ��].ʰȡ����ϴ�->Map(0, nullptr, (void**)&map��Դ);

		�������->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(����->����->Ԫ��[Ԫ��].ʰȡ���.Get(),
			D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_COPY_DEST));

		�������->CopyResource(����->����->Ԫ��[Ԫ��].ʰȡ���.Get(), ����->����->Ԫ��[Ԫ��].ʰȡ����ϴ�.Get());

		�������->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(����->����->Ԫ��[Ԫ��].ʰȡ���.Get(),
			D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_UNORDERED_ACCESS));
	}
	else
	{
		�Ƿ�ѡ��.�Ƿ�ʰȡ = 0;
	}

	����->����->Ԫ��[Ԫ��].ʰȡ���->Unmap(0, nullptr);
		
	return �Ƿ�ѡ��;
}
*/

C�������::~C�������()
{
	map<wstring, C��̬����*>::iterator it��̬;

	it��̬ = ��̬����.begin();
	for (int i = 0; i < ��̬����.size(); i++)
	{
		delete (*it��̬).second;
		it��̬++;
	}

	map<wstring, C��̬����*>::iterator it��̬;

	it��̬ = ��̬����.begin();
	for (int i = 0; i < ��̬����.size(); i++)
	{
		delete (*it��̬).second;
		it��̬++;
	}
}