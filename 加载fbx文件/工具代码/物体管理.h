#pragma once
#include<windows.h>
#include"..\���ߴ���\d3dx12.h"
#include"..\fbxģ�ͼ���Դ����\fbxģ�ͼ���-��̬ģ��.h"
#include"..\fbxģ�ͼ���Դ����\fbxģ�ͼ���-��̬ģ��.h"
#include"..\���ߴ���\�������ѹ���.h"

class C�������
{
public:
	map<wstring, C��̬����*> ��̬����;
	map<wstring, C��̬����*> ��̬����;

	C�������(ComPtr<ID3D12Device> �豸, ComPtr<ID3D12GraphicsCommandList> �������, C������Դ* ������Դ, C�������ѹ���* �������ѹ���);
	~C�������();
	void ���뾲̬����FBX(wstring ��������, const WCHAR* �ļ�·��, DXGI_FORMAT ������ʽ, float ��������);
	void ���붯̬����FBX(wstring ��������, const WCHAR* �ļ�·��, DXGI_FORMAT ������ʽ, float ��������);
	void ���뾲̬����MDS(wstring ��������, const WCHAR* �ļ�·��);
	void ���붯̬����MDD(wstring ��������, const WCHAR* �ļ�·��);
	void ɾ����̬����(wstring ��������);
	void ɾ����̬����(wstring ��������);
	//Sʰȡ��� �Ƿ�ѡ�о�̬(C��̬����* ����, UINT Ԫ��);
	//Sʰȡ��� �Ƿ�ѡ�ж�̬(C��̬����* ����, UINT Ԫ��);

private:
	ComPtr<ID3D12Device> �豸;
	ComPtr<ID3D12GraphicsCommandList> �������;
	C������Դ* ������Դ = nullptr;
	C�������ѹ���* �������ѹ��� = nullptr;
};