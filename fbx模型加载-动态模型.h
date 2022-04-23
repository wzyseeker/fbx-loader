#pragma once

#ifndef FBXSDK_SHARED
#define FBXSDK_SHARED
#endif // !FBXSDK_SHARED

#include"..\工具代码\d3dx12.h"
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

//加载fbx动态物体------------------------------------------------------------------------
class C动态物体
{
public:
	struct S动画帧
	{
		vector<XMFLOAT4X3> 骨骼变换;
		vector<XMFLOAT4X3> 物体变换;		//物体变换包含属性变换

		S动画帧() {  };
		~S动画帧()
		{
		};
	};
	struct S动画轨道
	{
		wstring 轨道名称;
		float 原始时长;
		float 当前时间;
		float 速度;
		vector<S动画帧> 帧;
		bool 是否循环;
		bool 是否结束;
		float 帧位;

		S动画轨道()
		{
			轨道名称 = L"";
			原始时长 = 0;
			当前时间 = 0;
			速度 = 1.0f;
			是否循环 = 1;
			是否结束 = 0;
			帧位 = 0;
		};
		~S动画轨道()
		{
		};
	};

	UINT 顶点数量 = 0;
	UINT 索引数量 = 0;
	ComPtr<ID3D12Device> 设备 = nullptr;
	C网格属性* 属性 = nullptr;
	UINT 顶点布局 = 0;
	wstring 物体名称键;

	ComPtr<ID3D12GraphicsCommandList> 命令队列 = 0;
	UINT 顶点单元大小 = 0;
	DXGI_FORMAT 索引格式;
	float 法向量合并最大角度 = XM_PI / 12;
	float 贴图顶点采样最大间隔 = 0.00001;   //分离同一个控制顶点记录两个贴图位置的情况

	vector<S动画轨道> 动画轨道;
	UINT 当前轨道 = 0;
	UINT 骨骼数量 = 0;

	void 绘制网格(UINT 属性);
	void 加载FBX文件(const WCHAR* 文件路径, wstring 物体名称键, DXGI_FORMAT 索引格式, float 体素粒度);

	void 导出mdd文件(wstring 文件名称);
	void 导入mdd文件(wstring 文件名称, wstring 物体名称键);

	void 设置网格优化信息(float 法向量合并最大角度, float 贴图顶点采样最大间隔);
	void 设定动画速度(UINT 轨道, float 速度倍数);
	void 设定动画轨道(UINT 轨道);
	void 设定轨道帧位置(UINT 轨道, float 百分比);
	void 设定播放模式(UINT 轨道, bool 是否循环);
	bool 检测动画结束(UINT 轨道);

	void 更新时间(float 时间变化);
	XMMATRIX* 获取当前骨骼变换();
	XMMATRIX 获取当前物体变换(UINT 属性);

	void 释放上传堆();

	C动态物体(ComPtr<ID3D12Device> 设备, ComPtr<ID3D12GraphicsCommandList> 命令队列, C描述符堆管理* 描述符堆管理, C共享资源* 共享资源);
	~C动态物体();

private:
	//fbx动画信息
	//规定索引为255时没有骨骼
	struct S顶点
	{
		XMFLOAT3 位置;
		XMFLOAT3 法向量;
		XMFLOAT2 纹理坐标;
		float 索引权重[3];
		UINT 关联骨骼索引[4];

		S顶点() 
		{ 
			ZeroMemory(this, sizeof(S顶点)); 
			索引权重[0] = 1.0f;
		};
		~S顶点() {  };
	};
	struct SSRT变换
	{
		XMFLOAT3 位置;
		XMFLOAT3 旋转;
		XMFLOAT3 缩放;

		SSRT变换()
		{
			位置 = XMFLOAT3{ 0.0f,0.0f, 0.0f };
			旋转 = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
			缩放 = XMFLOAT3{ 1.0f, 1.0f, 1.0f };
		}
		~SSRT变换() {};
	};
	struct S综合变换
	{
		SSRT变换 SRT变换;
		XMFLOAT3X3 旋转;

		S综合变换()
		{
			旋转 = XMFLOAT3X3
			{
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f
			};
		}
		~S综合变换()
		{
		}
	};
	struct S顶点索引
	{
		S顶点 顶点;
		UINT 索引;

		S顶点索引() { 索引 = 0; };
		~S顶点索引() { };
	};
	struct S物体控制顶点
	{
		wstring 物体名称;
		vector<vector<S顶点索引>> 控制顶点集;

		S物体控制顶点() 
		{
			物体名称 = L"";
		};
		~S物体控制顶点()
		{
		};
	};
	struct S优化顶点集
	{
		UINT 索引;
		S顶点 顶点;

		S优化顶点集() { 索引 = 0; };
		~S优化顶点集() { };
	};
	struct S合并索引集
	{
		UINT 主索引;
		vector<UINT> 副索引集;

		S合并索引集() { 主索引 = 0; };
		~S合并索引集() { };
	};
	struct S音轨数据
	{
		wstring 音轨名称;
		UINT 音效数量;

		S音轨数据() { 音效数量 = 0; };
		~S音轨数据() { };
	};
	struct S音效层数据
	{
		wstring 音效层名称;
		vector<S音轨数据> 音轨;

		S音效层数据() 
		{
			音效层名称 = L"";
		};
		~S音效层数据()
		{
		};
	};
	struct S动画位置数据
	{
		XMFLOAT3 位置;
		int 帧数;

		S动画位置数据() { ZeroMemory(this, sizeof(S动画位置数据)); };
		~S动画位置数据() {  };
	};
	struct S动画旋转数据
	{
		XMFLOAT3 旋转;
		int 帧数;

		S动画旋转数据() { ZeroMemory(this, sizeof(S动画旋转数据)); };
		~S动画旋转数据() {  };
	};
	struct S动画缩放数据
	{
		XMFLOAT3 缩放;
		int 帧数;

		S动画缩放数据() { ZeroMemory(this, sizeof(S动画缩放数据)); };
		~S动画缩放数据() {  };
	};
	struct S动画颜色数据
	{
		XMFLOAT3 颜色;
		int 帧数;

		S动画颜色数据() { ZeroMemory(this, sizeof(S动画颜色数据)); };
		~S动画颜色数据() {  };
	};
	struct S动画灯光属性
	{
		float 强度;
		float 外角;
		float 雾;
		int 帧数;

		S动画灯光属性() { ZeroMemory(this, sizeof(S动画灯光属性)); };
		~S动画灯光属性() {  };
	};
	struct S动画相机
	{
		XMFLOAT3 视觉区域;
		XMFLOAT3 光源中心;
		XMFLOAT3 滚动;
		int 帧数;

		S动画相机() { ZeroMemory(this, sizeof(S动画相机)); };
		~S动画相机() {  };
	};
	struct S动画物体数据
	{
		wstring 物体名称;
		vector<S动画位置数据> 位置;
		vector<S动画旋转数据> 旋转;
		vector<S动画缩放数据> 缩放;
		vector<S动画颜色数据> 颜色;
		vector<S动画灯光属性> 灯光属性;

		S动画物体数据() 
		{
			物体名称 = L"";
		};
		~S动画物体数据()
		{
		};
	};
	struct S动画层数据
	{
		wstring 动画层名称;
		vector<S动画物体数据> 物体;

		S动画层数据() 
		{
			动画层名称 = L"";
		};
		~S动画层数据() { };
	};
	struct S动画片段数据
	{
		wstring 片段名称;
		vector<S动画层数据> 动画层;
		vector<S音效层数据> 音效层;
		int 开始帧;
		int 结束帧;
		int 帧速率;

		S动画片段数据() 
		{
			片段名称 = L"";
			开始帧 = 0;
			结束帧 = 0;
			帧速率 = 0;
		};
		~S动画片段数据() { };
	};
	struct S动画数据
	{
		int 开始帧;
		int 结束帧;
		int 帧速率;
		vector<S动画片段数据> 片段;

		S动画数据()
		{
			开始帧 = 0;
			结束帧 = 0;
			帧速率 = 0;
		};
		~S动画数据() { };
	};
	struct S骨骼数据
	{
		vector<UINT> 索引组;
		vector<float> 权重组;
		wstring 骨骼名称;
		XMFLOAT3 关联模型位置;
		XMFLOAT3 关联模型旋转;
		XMFLOAT3 关联模型缩放;
		XMFLOAT3 关联骨骼位置;
		XMFLOAT3 关联骨骼旋转;
		XMFLOAT3 关联骨骼缩放;
		XMMATRIX 关联骨骼旋转矩阵;

		S骨骼数据()
		{
			骨骼名称 = L"";
			关联模型位置 = { 0.0f, 0.0f, 0.0f };
			关联模型旋转 = { 0.0f, 0.0f, 0.0f };
			关联模型缩放 = { 1.0f, 1.0f, 1.0f };
			关联骨骼位置 = { 0.0f, 0.0f, 0.0f };
			关联骨骼旋转 = { 0.0f, 0.0f, 0.0f };
			关联骨骼缩放 = { 1.0f, 1.0f, 1.0f };
		};
		~S骨骼数据() { };
	};
	struct S物体蒙皮数据
	{
		wstring 物体名称;
		vector<S骨骼数据> 骨骼;

		S物体蒙皮数据() 
		{
			物体名称 = L"";
		};
		~S物体蒙皮数据()
		{
		}
	};
	struct S蒙皮数据
	{
		vector<S物体蒙皮数据> 关联物体;

		S蒙皮数据() {  };
		~S蒙皮数据() { };
	};
	struct S帧2
	{
		SSRT变换 变换;
		XMFLOAT3X3 旋转;

		S帧2() 
		{
			旋转 = XMFLOAT3X3
			{
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f
			};
		};
		~S帧2()
		{
		}
	};
	struct S动画轨道2
	{
		vector<S帧2> 帧;

		S动画轨道2() 
		{
		};
		~S动画轨道2()
		{
		}
	};
	struct S变换节点
	{
		S变换节点* 子节点;
		S变换节点* 父节点;
		UINT 子节点数量;
		wstring 节点名称;
		SSRT变换 变换;
		XMFLOAT3 原始位置;
		XMFLOAT3 原始旋转;
		vector<S动画轨道2> 动画轨道;
		XMMATRIX 世界矩阵;
		XMFLOAT3 初始骨骼位置;
		XMFLOAT3X3 初始骨骼旋转;

		S变换节点()
		{
			子节点 = 0;
			父节点 = 0;
			子节点数量 = 0;
			节点名称 = L"";
			世界矩阵 = XMMatrixIdentity();
			原始位置 = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
			原始旋转 = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
			初始骨骼位置 = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
			初始骨骼旋转 = XMFLOAT3X3
			{
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f,
			};
		};
		~S变换节点()
		{
			if (子节点) delete[] 子节点;
		};
	};
	struct S备用资料
	{
		vector<S顶点> 顶点集;
		vector<UINT> 索引;
		vector<USHORT> s索引;
		vector<wstring> 路径集;

		S备用资料() {};
		~S备用资料() 
		{
		};
	};
	struct S造型
	{
		map<wstring, XMMATRIX> 绑定造型;
		map<wstring, XMMATRIX> 角色造型;
	};

	UINT m顶点计数 = 0;
	UINT m索引计数 = 0;
	vector<S物体控制顶点> m物体控制顶点集;
	vector<S合并索引集> m合并索引集;
	S备用资料* s备用资料 = nullptr;
	S顶点* 顶点集 = nullptr;
	vector<S优化顶点集> m优化顶点集;
	ComPtr<ID3D12Resource> 顶点 = nullptr;
	ComPtr<ID3D12Resource> 索引 = nullptr;
	ComPtr<ID3D12Resource> 顶点上传 = nullptr;
	ComPtr<ID3D12Resource> 索引上传 = nullptr;

	D3D12_VERTEX_BUFFER_VIEW vbv;
	D3D12_INDEX_BUFFER_VIEW ibv;
	C描述符堆管理* 描述符堆管理 = nullptr;

	S动画数据* m动画数据 = nullptr;
	S蒙皮数据* m蒙皮数据 = nullptr;
	vector<wstring> m骨骼名称;
	vector<S综合变换> m骨骼变换;
	S变换节点* m根节点 = nullptr;
	S造型* 造型 = nullptr;

	XMMATRIX s物体变换;
	XMMATRIX* s骨骼变换 = nullptr;

	C共享资源* 共享资源 = nullptr;

	//加载物体信息
	void 加载节点(FbxNode* p节点);
	void 加载网格(FbxNode* p网格节点);
	void 加载骨骼蒙皮信息(FbxNode* p网格节点);
	void 加载材质(FbxNode* p网格节点, C网格属性::S属性* 属性);
	void 加载材质属性(FbxSurfaceMaterial* p表面材质, C网格属性::S属性* 属性);
	void 加载纹理(FbxSurfaceMaterial* p表面材质, C网格属性::S属性* 属性);

	void 生成纹理描述符();

	//优化顶点临时信息
	void 添加顶点(UINT 顶点集索引, S顶点* 顶点, UINT 索引);
	void 释放链表(S顶点索引* p链表头);
	void 优化顶点();
	void 合并顶点(UINT 控制顶点集, UINT 控制顶点索引, float 最小cos角度, float 最大uv间隔);
	void 释放合并顶点索引集();
	void 释放合并信息();

	void 加载动画(FbxScene* p场景);
	void 加载音效层(FbxAudioLayer* p音效层, UINT 音效层索引, UINT 片段索引);
	void 加载动画层(FbxAnimLayer* p动画层, FbxNode* p节点, UINT 片段索引, UINT 动画层索引);
	void 加载动画通道(FbxAnimLayer* p动画层, FbxNode* p节点, UINT 片段索引, UINT 动画层索引, UINT 模型索引);
	void 加载动画片段(FbxAnimStack* p动画片段, FbxNode* p节点, UINT 片段索引);
	void 加载曲线序列(FbxAnimCurve* p曲线, FbxProperty* p属性);
	void 加载骨骼数据(FbxNode* p骨骼节点);
	void 加载造型(FbxScene* p场景);

	int 插入标志转索引(int 标志);
	int 恒定标志转索引(int 标志);
	int 切线模式标志转索引(int 标志);
	int 切线权重标志转索引(int 标志);
	int 切线速度标志转索引(int 标志);

	void 合并物体动画信息();
	void 加载层次(FbxScene* p场景);
	void 加载层次(FbxNode* p节点, S变换节点& 节点);
	void 加载骨骼位置信息();
	void 加载骨骼位置信息(S变换节点* 节点, XMMATRIX 世界矩阵);
	void 合并骨骼树(S变换节点* 变换节点);
	void 搜索骨骼树(wstring 骨骼名称, S变换节点*& 目标节点);
	void 搜索骨骼树(S变换节点* 变换节点, wstring 骨骼名称, S变换节点*& 目标节点);
	void 设定轨道数(S变换节点* 变换节点, UINT 轨道数量);
	void 设定帧数(S变换节点* 变换节点, UINT 动画轨道, UINT 帧数);
};