#pragma once

#ifndef FBXSDK_SHARED
#define FBXSDK_SHARED
#endif // !FBXSDK_SHARED

#include"..\工具代码\d3dx12.h"
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
#include"..\工具代码\内存检测.h"
#include"网格属性.h"
#include"..\工具代码\共享资源.h"
#include"..\工具代码\描述符堆管理.h"
#include"..\工具代码\TextureLoader.h"
#include"..\工具代码\DDSTextureLoader.h"

#pragma comment(lib, "libfbxsdk.lib")

using namespace std;
using namespace DirectX;
using namespace Microsoft::WRL;

//加载fbx文件----------------------------------------------------
class C静态物体
{
public:
	UINT 顶点数量 = 0;
	UINT 索引数量 = 0;
	ComPtr<ID3D12Device> 设备 = nullptr;
	C网格属性* 属性 = nullptr;
	UINT 顶点布局 = 0;
	ComPtr<ID3D12GraphicsCommandList> 命令队列 = nullptr;
	UINT 顶点单元大小 = 0;
	DXGI_FORMAT 索引格式{};
	float 法向量合并最大角度 = XM_PI / 12;
	float 贴图顶点采样最大间隔 = 0.00001;
	wstring 物体名称键;

	void 加载FBX文件(const WCHAR* 文件路径, wstring 物体名称键, DXGI_FORMAT 索引格式, float 体素粒度);
	void 绘制网格(UINT 属性);

	void 导出mds文件(wstring 文件名称);
	void 导入mds文件(wstring 文件名称, wstring 物体名称键);

	void 释放上传堆();  //在加载资源命令队列执行后使用

	C静态物体(ComPtr<ID3D12Device> 设备, ComPtr<ID3D12GraphicsCommandList> 命令队列, C描述符堆管理* 描述符堆管理, C共享资源* 共享资源);
	~C静态物体();

private:
	struct S顶点
	{
		XMFLOAT3 位置;
		XMFLOAT3 法向量;
		XMFLOAT2 纹理坐标;

		S顶点() { ZeroMemory(this, sizeof(S顶点)); };
		~S顶点() {  };
	};
	struct S顶点索引
	{
		S顶点 顶点;
		UINT 索引;
		S顶点索引* p下一节点;

		S顶点索引()
		{
			索引 = 0;
			p下一节点 = 0;
		};
		~S顶点索引() {  };
	};
	struct S合并索引集
	{
		UINT 主索引;
		vector<UINT> 副索引集;

		S合并索引集()
		{
			主索引 = 0;
		};
		~S合并索引集() {  };
	};
	struct S优化顶点集
	{
		UINT 索引;
		S顶点 顶点;

		S优化顶点集()
		{
			索引 = 0;
		};
		~S优化顶点集() {  };
	};	
	struct S体素位
	{
		UINT x;
		UINT y;
		UINT z;
		UINT 前上左;
		UINT 前上右;
		UINT 前下左;
		UINT 前下右;
		UINT 后上左;
		UINT 后上右;
		UINT 后下左;
		UINT 后下右;


		S体素位()
		{
			ZeroMemory(this, sizeof(S体素位));
		}
		~S体素位() {};
	};
	struct S体素块
	{
		bool*** 体素;
		int 边个数[3];
		XMFLOAT3 左下角位置;
		float 间隔;

		S体素块()
		{
			体素 = 0;
			间隔 = 0;
			memset(边个数, 0, 3);
			左下角位置 = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
		}
		~S体素块()
		{
			if (体素)
			{
				for (int i = 0; i < 边个数[2]; i++)
				{
					for (int j = 0; j < 边个数[1]; j++)
					{
						delete[] 体素[i][j];
					}
					delete[] 体素[i];
				}
				delete[] 体素;
			}
		}
	};
	struct S包围框
	{
		XMFLOAT3 左下前位置;
		XMFLOAT3 边长;

		S包围框()
		{
			ZeroMemory(this, sizeof(S包围框));
		};
		~S包围框() {};
	};
	struct S备用资料
	{
		vector<wstring> 路径集;  //材质路径
		vector<S顶点> 顶点集;
		vector<UINT> 索引;
		vector<USHORT> s索引;
		vector<vector<S包围框>> 包围框块;

		S备用资料() {};
		~S备用资料() {};
	};

	vector<S顶点索引*> m控制顶点集;
	vector<S优化顶点集> m优化顶点集;
	UINT m顶点计数 = 0;
	UINT m索引计数 = 0;
	vector<S合并索引集> m合并索引集;
	C共享资源* 共享资源 = 0;
	random_device rd;
	vector<S体素块*> m体素块;
	ComPtr<ID3D12Resource> 顶点 = nullptr;
	ComPtr<ID3D12Resource> 索引 = nullptr;
	ComPtr<ID3D12Resource> 顶点上传 = nullptr;
	ComPtr<ID3D12Resource> 索引上传 = nullptr;
	S备用资料* s备用资料 = nullptr;
	D3D12_VERTEX_BUFFER_VIEW vbv;
	D3D12_INDEX_BUFFER_VIEW ibv;
	C描述符堆管理* 描述符堆管理 = nullptr;

	//加载物体信息
	void 加载节点(FbxNode* p节点);
	void 加载节点(FbxScene* pScene);
	void 加载网格(FbxNode* p网格节点存描述);
	void 加载材质(FbxNode* p网格节点, C网格属性::S属性* 属性);
	void 加载材质属性(FbxSurfaceMaterial* p表面材质, C网格属性::S属性* 属性);
	void 加载纹理(FbxSurfaceMaterial* p表面材质, C网格属性::S属性* 属性);

	void 生成纹理描述符();

	//优化顶点临时信息
	void 添加顶点(S顶点索引* p链表头, S顶点& 顶点, UINT 索引);
	void 释放链表(S顶点索引* p链表头);
	void 优化顶点();
	void 合并顶点(S顶点索引* p链表头, float 最小cos角度, float 最大uv间隔);
	void 释放合并信息();

	//体素化
	void 体素化(float 粒度);  //1单位一维含有微粒数
	static void 体素采样线程(S备用资料* s备用资料, C网格属性* 属性, vector<S体素块*> m体素块, XMFLOAT3 采样点, UINT 体素块索引, UINT x, UINT y, UINT z);
	static void 体素采样线程1(S备用资料* s备用资料, C网格属性* 属性, vector<S体素块*> m体素块, XMFLOAT3 采样点, UINT 体素块索引, UINT x, UINT y, UINT z);
	void 创建包围框缓存();
	void 创建包围球();
};

