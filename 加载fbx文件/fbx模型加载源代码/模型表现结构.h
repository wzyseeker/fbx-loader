#pragma once
#include"..\���ߴ���\d3dx12.h"
#include<DirectXMath.h>

using namespace std;
using namespace DirectX;

struct S���� 
{
	XMFLOAT4 ������;
	XMFLOAT4 �Է���;
	XMFLOAT4 ������;
	float �����;
	float �߹⼶��;
	float ��͸����;
	float pad;

	S����() { ZeroMemory(this, sizeof(S����)); }
	~S����() {  };
};

struct S�����Դ 
{
	XMFLOAT4 ��ɫ;
	XMFLOAT4 ����;

	S�����Դ() { ZeroMemory(this, sizeof(S�����Դ)); }
	~S�����Դ() {  };
};