#pragma once
#include<string>
#include<vector>
#include<map>
#include<DirectXMath.h>
#include<DirectXCollision.h>
#include<wrl.h>
#include"..\���ߴ���\�ڴ���.h"
#include"ģ����������.h"
#include"ģ�ͱ��ֽṹ.h"

using namespace std;
using namespace DirectX;
using namespace Microsoft::WRL;

struct Sʰȡ���
{
	UINT �Ƿ�ʰȡ;
	float ����;

	Sʰȡ���() {
		�Ƿ�ʰȡ = 0;
		���� = 0;
	}
	~Sʰȡ���() {};
};

//��������----------------------------------------------------------------
class C��������
{
public:
	struct S��Χ��
	{
		XMFLOAT3 ����ǰλ��;
		XMFLOAT3 �����;
		UINT ����;

		S��Χ��()
		{
			ZeroMemory(this, sizeof(S��Χ��));
		};
		~S��Χ��() {};
	};

	struct S����
	{
		wstring ��������;
		UINT ��ʼ����;
		UINT ��������;
		XMMATRIX �任;
		UINT ��������;
		UINT ����ͼ����;
		S���� ����;
		UINT ��Χ������;
		ComPtr<ID3D12Resource> ��Χ��;
		ComPtr<ID3D12Resource> ��Χ���ϴ�;
		ComPtr<ID3D12Resource> ʰȡ���;
		ComPtr<ID3D12Resource> ʰȡ����ϴ�;
		ComPtr<ID3D12Resource> ʰȡ�������;
		BoundingSphere ��Χ��;

		S����()
		{
			��ʼ���� = 0;
			�������� = 0;
			�任 = XMMatrixIdentity();
			�������� = 0;
			����ͼ���� = 0;
			��Χ�� = nullptr;
			��Χ���ϴ� = nullptr;
			��Χ������ = 0;
			ʰȡ��� = nullptr;
			ʰȡ����ϴ� = nullptr;
			ʰȡ������� = nullptr;
			ZeroMemory(&����, sizeof(S����));
			ZeroMemory(&��Χ��, sizeof(BoundingSphere));
		};
		~S����() 
		{ 

		};
	};

	vector<S����*> Ԫ��;
	vector<ComPtr<ID3D12Resource>> ����;
	vector<ComPtr<ID3D12Resource>> ������ͼ��;
	vector<ComPtr<ID3D12Resource>> �����ϴ�;
	vector<ComPtr<ID3D12Resource>> ������ͼ���ϴ�;

	ComPtr<ID3D12Resource> ��ͼ(UINT ����);
	ComPtr<ID3D12Resource> ������ͼ(UINT ����);
	void ���Ԫ��(S����* ����);
	void �ͷ��ϴ���();

	~C��������();
};
