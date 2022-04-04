#pragma once
#include"..\工具代码\d3dx12.h"
#include<DirectXMath.h>

using namespace std;
using namespace DirectX;

struct S材质 
{
	XMFLOAT4 漫反射;
	XMFLOAT4 自发光;
	XMFLOAT4 环境光;
	float 光泽度;
	float 高光级别;
	float 不透明度;
	float pad;

	S材质() { ZeroMemory(this, sizeof(S材质)); }
	~S材质() {  };
};

struct S方向光源 
{
	XMFLOAT4 颜色;
	XMFLOAT4 方向;

	S方向光源() { ZeroMemory(this, sizeof(S方向光源)); }
	~S方向光源() {  };
};