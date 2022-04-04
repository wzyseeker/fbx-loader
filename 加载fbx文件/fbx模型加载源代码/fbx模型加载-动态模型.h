#pragma once

#ifndef FBXSDK_SHARED
#define FBXSDK_SHARED
#endif // !FBXSDK_SHARED

#include"..\���ߴ���\d3dx12.h"
#include<DirectXMath.h>
#include<DirectXCollision.h>
#include"..\FBX SDK\include\fbxsdk.h"
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

//����fbx��̬����------------------------------------------------------------------------
class C��̬����
{
public:
	struct S����֡
	{
		vector<XMFLOAT4X3> �����任;
		vector<XMFLOAT4X3> ����任;		//����任�������Ա任

		S����֡() {  };
		~S����֡()
		{
		};
	};
	struct S�������
	{
		wstring �������;
		float ԭʼʱ��;
		float ��ǰʱ��;
		float �ٶ�;
		vector<S����֡> ֡;
		bool �Ƿ�ѭ��;
		bool �Ƿ����;
		float ֡λ;

		S�������()
		{
			������� = L"";
			ԭʼʱ�� = 0;
			��ǰʱ�� = 0;
			�ٶ� = 1.0f;
			�Ƿ�ѭ�� = 1;
			�Ƿ���� = 0;
			֡λ = 0;
		};
		~S�������()
		{
		};
	};

	UINT �������� = 0;
	UINT �������� = 0;
	ComPtr<ID3D12Device> �豸 = nullptr;
	C��������* ���� = nullptr;
	UINT ���㲼�� = 0;
	wstring �������Ƽ�;

	ComPtr<ID3D12GraphicsCommandList> ������� = 0;
	UINT ���㵥Ԫ��С = 0;
	DXGI_FORMAT ������ʽ;
	float �������ϲ����Ƕ� = XM_PI / 12;
	float ��ͼ������������ = 0.00001;   //����ͬһ�����ƶ����¼������ͼλ�õ����

	vector<S�������> �������;
	UINT ��ǰ��� = 0;
	UINT �������� = 0;

	void ��������(UINT ����);
	void ����FBX�ļ�(const WCHAR* �ļ�·��, wstring �������Ƽ�, DXGI_FORMAT ������ʽ, float ��������);

	void ����mdd�ļ�(wstring �ļ�����);
	void ����mdd�ļ�(wstring �ļ�����, wstring �������Ƽ�);

	void ���������Ż���Ϣ(float �������ϲ����Ƕ�, float ��ͼ������������);
	void �趨�����ٶ�(UINT ���, float �ٶȱ���);
	void �趨�������(UINT ���);
	void �趨���֡λ��(UINT ���, float �ٷֱ�);
	void �趨����ģʽ(UINT ���, bool �Ƿ�ѭ��);
	bool ��⶯������(UINT ���);

	void ����ʱ��(float ʱ��仯);
	XMMATRIX* ��ȡ��ǰ�����任();
	XMMATRIX ��ȡ��ǰ����任(UINT ����);

	void �ͷ��ϴ���();

	C��̬����(ComPtr<ID3D12Device> �豸, ComPtr<ID3D12GraphicsCommandList> �������, C�������ѹ���* �������ѹ���, C������Դ* ������Դ);
	~C��̬����();

private:
	//fbx������Ϣ
	//�涨����Ϊ255ʱû�й���
	struct S����
	{
		XMFLOAT3 λ��;
		XMFLOAT3 ������;
		XMFLOAT2 ��������;
		float ����Ȩ��[3];
		UINT ������������[4];

		S����() 
		{ 
			ZeroMemory(this, sizeof(S����)); 
			����Ȩ��[0] = 1.0f;
		};
		~S����() {  };
	};
	struct SSRT�任
	{
		XMFLOAT3 λ��;
		XMFLOAT3 ��ת;
		XMFLOAT3 ����;

		SSRT�任()
		{
			λ�� = XMFLOAT3{ 0.0f,0.0f, 0.0f };
			��ת = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
			���� = XMFLOAT3{ 1.0f, 1.0f, 1.0f };
		}
		~SSRT�任() {};
	};
	struct S�ۺϱ任
	{
		SSRT�任 SRT�任;
		XMFLOAT3X3 ��ת;

		S�ۺϱ任()
		{
			��ת = XMFLOAT3X3
			{
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f
			};
		}
		~S�ۺϱ任()
		{
		}
	};
	struct S��������
	{
		S���� ����;
		UINT ����;

		S��������() { ���� = 0; };
		~S��������() { };
	};
	struct S������ƶ���
	{
		wstring ��������;
		vector<vector<S��������>> ���ƶ��㼯;

		S������ƶ���() 
		{
			�������� = L"";
		};
		~S������ƶ���()
		{
		};
	};
	struct S�Ż����㼯
	{
		UINT ����;
		S���� ����;

		S�Ż����㼯() { ���� = 0; };
		~S�Ż����㼯() { };
	};
	struct S�ϲ�������
	{
		UINT ������;
		vector<UINT> ��������;

		S�ϲ�������() { ������ = 0; };
		~S�ϲ�������() { };
	};
	struct S��������
	{
		wstring ��������;
		UINT ��Ч����;

		S��������() { ��Ч���� = 0; };
		~S��������() { };
	};
	struct S��Ч������
	{
		wstring ��Ч������;
		vector<S��������> ����;

		S��Ч������() 
		{
			��Ч������ = L"";
		};
		~S��Ч������()
		{
		};
	};
	struct S����λ������
	{
		XMFLOAT3 λ��;
		int ֡��;

		S����λ������() { ZeroMemory(this, sizeof(S����λ������)); };
		~S����λ������() {  };
	};
	struct S������ת����
	{
		XMFLOAT3 ��ת;
		int ֡��;

		S������ת����() { ZeroMemory(this, sizeof(S������ת����)); };
		~S������ת����() {  };
	};
	struct S������������
	{
		XMFLOAT3 ����;
		int ֡��;

		S������������() { ZeroMemory(this, sizeof(S������������)); };
		~S������������() {  };
	};
	struct S������ɫ����
	{
		XMFLOAT3 ��ɫ;
		int ֡��;

		S������ɫ����() { ZeroMemory(this, sizeof(S������ɫ����)); };
		~S������ɫ����() {  };
	};
	struct S�����ƹ�����
	{
		float ǿ��;
		float ���;
		float ��;
		int ֡��;

		S�����ƹ�����() { ZeroMemory(this, sizeof(S�����ƹ�����)); };
		~S�����ƹ�����() {  };
	};
	struct S�������
	{
		XMFLOAT3 �Ӿ�����;
		XMFLOAT3 ��Դ����;
		XMFLOAT3 ����;
		int ֡��;

		S�������() { ZeroMemory(this, sizeof(S�������)); };
		~S�������() {  };
	};
	struct S������������
	{
		wstring ��������;
		vector<S����λ������> λ��;
		vector<S������ת����> ��ת;
		vector<S������������> ����;
		vector<S������ɫ����> ��ɫ;
		vector<S�����ƹ�����> �ƹ�����;

		S������������() 
		{
			�������� = L"";
		};
		~S������������()
		{
		};
	};
	struct S����������
	{
		wstring ����������;
		vector<S������������> ����;

		S����������() 
		{
			���������� = L"";
		};
		~S����������() { };
	};
	struct S����Ƭ������
	{
		wstring Ƭ������;
		vector<S����������> ������;
		vector<S��Ч������> ��Ч��;
		int ��ʼ֡;
		int ����֡;
		int ֡����;

		S����Ƭ������() 
		{
			Ƭ������ = L"";
			��ʼ֡ = 0;
			����֡ = 0;
			֡���� = 0;
		};
		~S����Ƭ������() { };
	};
	struct S��������
	{
		int ��ʼ֡;
		int ����֡;
		int ֡����;
		vector<S����Ƭ������> Ƭ��;

		S��������()
		{
			��ʼ֡ = 0;
			����֡ = 0;
			֡���� = 0;
		};
		~S��������() { };
	};
	struct S��������
	{
		vector<UINT> ������;
		vector<float> Ȩ����;
		wstring ��������;
		XMFLOAT3 ����ģ��λ��;
		XMFLOAT3 ����ģ����ת;
		XMFLOAT3 ����ģ������;
		XMFLOAT3 ��������λ��;
		XMFLOAT3 ����������ת;
		XMFLOAT3 ������������;
		XMMATRIX ����������ת����;

		S��������()
		{
			�������� = L"";
			����ģ��λ�� = { 0.0f, 0.0f, 0.0f };
			����ģ����ת = { 0.0f, 0.0f, 0.0f };
			����ģ������ = { 1.0f, 1.0f, 1.0f };
			��������λ�� = { 0.0f, 0.0f, 0.0f };
			����������ת = { 0.0f, 0.0f, 0.0f };
			������������ = { 1.0f, 1.0f, 1.0f };
		};
		~S��������() { };
	};
	struct S������Ƥ����
	{
		wstring ��������;
		vector<S��������> ����;

		S������Ƥ����() 
		{
			�������� = L"";
		};
		~S������Ƥ����()
		{
		}
	};
	struct S��Ƥ����
	{
		vector<S������Ƥ����> ��������;

		S��Ƥ����() {  };
		~S��Ƥ����() { };
	};
	struct S֡2
	{
		SSRT�任 �任;
		XMFLOAT3X3 ��ת;

		S֡2() 
		{
			��ת = XMFLOAT3X3
			{
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f
			};
		};
		~S֡2()
		{
		}
	};
	struct S�������2
	{
		vector<S֡2> ֡;

		S�������2() 
		{
		};
		~S�������2()
		{
		}
	};
	struct S�任�ڵ�
	{
		S�任�ڵ�* �ӽڵ�;
		S�任�ڵ�* ���ڵ�;
		UINT �ӽڵ�����;
		wstring �ڵ�����;
		SSRT�任 �任;
		XMFLOAT3 ԭʼλ��;
		XMFLOAT3 ԭʼ��ת;
		vector<S�������2> �������;
		XMMATRIX �������;
		XMFLOAT3 ��ʼ����λ��;
		XMFLOAT3X3 ��ʼ������ת;

		S�任�ڵ�()
		{
			�ӽڵ� = 0;
			���ڵ� = 0;
			�ӽڵ����� = 0;
			�ڵ����� = L"";
			������� = XMMatrixIdentity();
			ԭʼλ�� = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
			ԭʼ��ת = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
			��ʼ����λ�� = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
			��ʼ������ת = XMFLOAT3X3
			{
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f,
			};
		};
		~S�任�ڵ�()
		{
			if (�ӽڵ�) delete[] �ӽڵ�;
		};
	};
	struct S��������
	{
		vector<S����> ���㼯;
		vector<UINT> ����;
		vector<USHORT> s����;
		vector<wstring> ·����;

		S��������() {};
		~S��������() 
		{
		};
	};
	struct S����
	{
		map<wstring, XMMATRIX> ������;
		map<wstring, XMMATRIX> ��ɫ����;
	};

	UINT m������� = 0;
	UINT m�������� = 0;
	vector<S������ƶ���> m������ƶ��㼯;
	vector<S�ϲ�������> m�ϲ�������;
	S��������* s�������� = nullptr;
	S����* ���㼯 = nullptr;
	vector<S�Ż����㼯> m�Ż����㼯;
	ComPtr<ID3D12Resource> ���� = nullptr;
	ComPtr<ID3D12Resource> ���� = nullptr;
	ComPtr<ID3D12Resource> �����ϴ� = nullptr;
	ComPtr<ID3D12Resource> �����ϴ� = nullptr;

	D3D12_VERTEX_BUFFER_VIEW vbv;
	D3D12_INDEX_BUFFER_VIEW ibv;
	C�������ѹ���* �������ѹ��� = nullptr;

	S��������* m�������� = nullptr;
	S��Ƥ����* m��Ƥ���� = nullptr;
	vector<wstring> m��������;
	vector<S�ۺϱ任> m�����任;
	S�任�ڵ�* m���ڵ� = nullptr;
	S����* ���� = nullptr;

	XMMATRIX s����任;
	XMMATRIX* s�����任 = nullptr;

	C������Դ* ������Դ = nullptr;

	//����������Ϣ
	void ���ؽڵ�(FbxNode* p�ڵ�);
	void ��������(FbxNode* p����ڵ�);
	void ���ع�����Ƥ��Ϣ(FbxNode* p����ڵ�);
	void ���ز���(FbxNode* p����ڵ�, C��������::S����* ����);
	void ���ز�������(FbxSurfaceMaterial* p�������, C��������::S����* ����);
	void ��������(FbxSurfaceMaterial* p�������, C��������::S����* ����);

	void ��������������();

	//�Ż�������ʱ��Ϣ
	void ��Ӷ���(UINT ���㼯����, S����* ����, UINT ����);
	void �ͷ�����(S��������* p����ͷ);
	void �Ż�����();
	void �ϲ�����(UINT ���ƶ��㼯, UINT ���ƶ�������, float ��Сcos�Ƕ�, float ���uv���);
	void �ͷźϲ�����������();
	void �ͷźϲ���Ϣ();

	void ���ض���(FbxScene* p����);
	void ������Ч��(FbxAudioLayer* p��Ч��, UINT ��Ч������, UINT Ƭ������);
	void ���ض�����(FbxAnimLayer* p������, FbxNode* p�ڵ�, UINT Ƭ������, UINT ����������);
	void ���ض���ͨ��(FbxAnimLayer* p������, FbxNode* p�ڵ�, UINT Ƭ������, UINT ����������, UINT ģ������);
	void ���ض���Ƭ��(FbxAnimStack* p����Ƭ��, FbxNode* p�ڵ�, UINT Ƭ������);
	void ������������(FbxAnimCurve* p����, FbxProperty* p����);
	void ���ع�������(FbxNode* p�����ڵ�);
	void ��������(FbxScene* p����);

	int �����־ת����(int ��־);
	int �㶨��־ת����(int ��־);
	int ����ģʽ��־ת����(int ��־);
	int ����Ȩ�ر�־ת����(int ��־);
	int �����ٶȱ�־ת����(int ��־);

	void �ϲ����嶯����Ϣ();
	void ���ز��(FbxScene* p����);
	void ���ز��(FbxNode* p�ڵ�, S�任�ڵ�& �ڵ�);
	void ���ع���λ����Ϣ();
	void ���ع���λ����Ϣ(S�任�ڵ�* �ڵ�, XMMATRIX �������);
	void �ϲ�������(S�任�ڵ�* �任�ڵ�);
	void ����������(wstring ��������, S�任�ڵ�*& Ŀ��ڵ�);
	void ����������(S�任�ڵ�* �任�ڵ�, wstring ��������, S�任�ڵ�*& Ŀ��ڵ�);
	void �趨�����(S�任�ڵ�* �任�ڵ�, UINT �������);
	void �趨֡��(S�任�ڵ�* �任�ڵ�, UINT �������, UINT ֡��);
};