#pragma once

#ifndef FBXSDK_SHARED
#define FBXSDK_SHARED
#endif // !FBXSDK_SHARED

#include"..\���ߴ���\d3dx12.h"
#include<DirectXMath.h>
#include<DirectXCollision.h>
#include<fbxsdk.h>
#include<vector>
#include<map>
#include<fstream>
#include<string>
#include<random>
#include<thread>
#include<wrl.h>
#include"..\���ߴ���\�ڴ���.h"
#include"��������.h"
#include"..\���ߴ���\������Դ.h"
#include"..\���ߴ���\�������ѹ���.h"
#include"..\���ߴ���\TextureLoader.h"
#include"..\���ߴ���\DDSTextureLoader.h"

#pragma comment(lib, "libfbxsdk.lib")

using namespace std;
using namespace DirectX;
using namespace Microsoft::WRL;

//����fbx�ļ�----------------------------------------------------
class C��̬����
{
public:
	UINT �������� = 0;
	UINT �������� = 0;
	ComPtr<ID3D12Device> �豸 = nullptr;
	C��������* ���� = nullptr;
	UINT ���㲼�� = 0;
	ComPtr<ID3D12GraphicsCommandList> ������� = nullptr;
	UINT ���㵥Ԫ��С = 0;
	DXGI_FORMAT ������ʽ{};
	float �������ϲ����Ƕ� = XM_PI / 12;
	float ��ͼ������������ = 0.00001;
	wstring �������Ƽ�;

	void ����FBX�ļ�(const WCHAR* �ļ�·��, wstring �������Ƽ�, DXGI_FORMAT ������ʽ, float ��������);
	void ��������(UINT ����);

	void ����mds�ļ�(wstring �ļ�����);
	void ����mds�ļ�(wstring �ļ�����, wstring �������Ƽ�);

	void �ͷ��ϴ���();  //�ڼ�����Դ�������ִ�к�ʹ��

	C��̬����(ComPtr<ID3D12Device> �豸, ComPtr<ID3D12GraphicsCommandList> �������, C�������ѹ���* �������ѹ���, C������Դ* ������Դ);
	~C��̬����();

private:
	struct S����
	{
		XMFLOAT3 λ��;
		XMFLOAT3 ������;
		XMFLOAT2 ��������;

		S����() { ZeroMemory(this, sizeof(S����)); };
		~S����() {  };
	};
	struct S��������
	{
		S���� ����;
		UINT ����;
		S��������* p��һ�ڵ�;

		S��������()
		{
			���� = 0;
			p��һ�ڵ� = 0;
		};
		~S��������() {  };
	};
	struct S�ϲ�������
	{
		UINT ������;
		vector<UINT> ��������;

		S�ϲ�������()
		{
			������ = 0;
		};
		~S�ϲ�������() {  };
	};
	struct S�Ż����㼯
	{
		UINT ����;
		S���� ����;

		S�Ż����㼯()
		{
			���� = 0;
		};
		~S�Ż����㼯() {  };
	};	
	struct S����λ
	{
		UINT x;
		UINT y;
		UINT z;
		UINT ǰ����;
		UINT ǰ����;
		UINT ǰ����;
		UINT ǰ����;
		UINT ������;
		UINT ������;
		UINT ������;
		UINT ������;


		S����λ()
		{
			ZeroMemory(this, sizeof(S����λ));
		}
		~S����λ() {};
	};
	struct S���ؿ�
	{
		bool*** ����;
		int �߸���[3];
		XMFLOAT3 ���½�λ��;
		float ���;

		S���ؿ�()
		{
			���� = 0;
			��� = 0;
			memset(�߸���, 0, 3);
			���½�λ�� = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
		}
		~S���ؿ�()
		{
			if (����)
			{
				for (int i = 0; i < �߸���[2]; i++)
				{
					for (int j = 0; j < �߸���[1]; j++)
					{
						delete[] ����[i][j];
					}
					delete[] ����[i];
				}
				delete[] ����;
			}
		}
	};
	struct S��Χ��
	{
		XMFLOAT3 ����ǰλ��;
		XMFLOAT3 �߳�;

		S��Χ��()
		{
			ZeroMemory(this, sizeof(S��Χ��));
		};
		~S��Χ��() {};
	};
	struct S��������
	{
		vector<wstring> ·����;  //����·��
		vector<S����> ���㼯;
		vector<UINT> ����;
		vector<USHORT> s����;
		vector<vector<S��Χ��>> ��Χ���;

		S��������() {};
		~S��������() {};
	};

	vector<S��������*> m���ƶ��㼯;
	vector<S�Ż����㼯> m�Ż����㼯;
	UINT m������� = 0;
	UINT m�������� = 0;
	vector<S�ϲ�������> m�ϲ�������;
	C������Դ* ������Դ = 0;
	random_device rd;
	vector<S���ؿ�*> m���ؿ�;
	ComPtr<ID3D12Resource> ���� = nullptr;
	ComPtr<ID3D12Resource> ���� = nullptr;
	ComPtr<ID3D12Resource> �����ϴ� = nullptr;
	ComPtr<ID3D12Resource> �����ϴ� = nullptr;
	S��������* s�������� = nullptr;
	D3D12_VERTEX_BUFFER_VIEW vbv;
	D3D12_INDEX_BUFFER_VIEW ibv;
	C�������ѹ���* �������ѹ��� = nullptr;

	//����������Ϣ
	void ���ؽڵ�(FbxNode* p�ڵ�);
	void ���ؽڵ�(FbxScene* pScene);
	void ��������(FbxNode* p����ڵ������);
	void ���ز���(FbxNode* p����ڵ�, C��������::S����* ����);
	void ���ز�������(FbxSurfaceMaterial* p�������, C��������::S����* ����);
	void ��������(FbxSurfaceMaterial* p�������, C��������::S����* ����);

	void ��������������();

	//�Ż�������ʱ��Ϣ
	void ��Ӷ���(S��������* p����ͷ, S����& ����, UINT ����);
	void �ͷ�����(S��������* p����ͷ);
	void �Ż�����();
	void �ϲ�����(S��������* p����ͷ, float ��Сcos�Ƕ�, float ���uv���);
	void �ͷźϲ���Ϣ();

	//���ػ�
	void ���ػ�(float ����);  //1��λһά����΢����
	static void ���ز����߳�(S��������* s��������, C��������* ����, vector<S���ؿ�*> m���ؿ�, XMFLOAT3 ������, UINT ���ؿ�����, UINT x, UINT y, UINT z);
	static void ���ز����߳�1(S��������* s��������, C��������* ����, vector<S���ؿ�*> m���ؿ�, XMFLOAT3 ������, UINT ���ؿ�����, UINT x, UINT y, UINT z);
	void ������Χ�򻺴�();
	void ������Χ��();
};

