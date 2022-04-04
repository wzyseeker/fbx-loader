#pragma once
#include<string>
#include<vector>
#include<map>
#include<DirectXMath.h>
#include<DirectXCollision.h>
#include<wrl.h>
#include"..\工具代码\内存检测.h"
#include"模型特征定义.h"
#include"模型表现结构.h"

using namespace std;
using namespace DirectX;
using namespace Microsoft::WRL;

struct S拾取输出
{
	UINT 是否拾取;
	float 距离;

	S拾取输出() {
		是否拾取 = 0;
		距离 = 0;
	}
	~S拾取输出() {};
};

//网格属性----------------------------------------------------------------
class C网格属性
{
public:
	struct S包围框
	{
		XMFLOAT3 左下前位置;
		XMFLOAT3 长宽高;
		UINT 所属;

		S包围框()
		{
			ZeroMemory(this, sizeof(S包围框));
		};
		~S包围框() {};
	};

	struct S属性
	{
		wstring 物体名称;
		UINT 起始索引;
		UINT 索引数量;
		XMMATRIX 变换;
		UINT 纹理索引;
		UINT 法线图索引;
		S材质 材质;
		UINT 包围框数量;
		ComPtr<ID3D12Resource> 包围框;
		ComPtr<ID3D12Resource> 包围框上传;
		ComPtr<ID3D12Resource> 拾取输出;
		ComPtr<ID3D12Resource> 拾取输出上传;
		ComPtr<ID3D12Resource> 拾取输出读回;
		BoundingSphere 包围球;

		S属性()
		{
			起始索引 = 0;
			索引数量 = 0;
			变换 = XMMatrixIdentity();
			纹理索引 = 0;
			法线图索引 = 0;
			包围框 = nullptr;
			包围框上传 = nullptr;
			包围框数量 = 0;
			拾取输出 = nullptr;
			拾取输出上传 = nullptr;
			拾取输出读回 = nullptr;
			ZeroMemory(&材质, sizeof(S材质));
			ZeroMemory(&包围球, sizeof(BoundingSphere));
		};
		~S属性() 
		{ 

		};
	};

	vector<S属性*> 元素;
	vector<ComPtr<ID3D12Resource>> 纹理集;
	vector<ComPtr<ID3D12Resource>> 法线贴图集;
	vector<ComPtr<ID3D12Resource>> 纹理集上传;
	vector<ComPtr<ID3D12Resource>> 法线贴图集上传;

	ComPtr<ID3D12Resource> 贴图(UINT 索引);
	ComPtr<ID3D12Resource> 法线贴图(UINT 索引);
	void 添加元素(S属性* 属性);
	void 释放上传堆();

	~C网格属性();
};
