#pragma once
#include<windows.h>
#include"..\工具代码\d3dx12.h"
#include"..\fbx模型加载源代码\fbx模型加载-静态模型.h"
#include"..\fbx模型加载源代码\fbx模型加载-动态模型.h"
#include"..\工具代码\描述符堆管理.h"

class C物体管理
{
public:
	map<wstring, C静态物体*> 静态物体;
	map<wstring, C动态物体*> 动态物体;

	C物体管理(ComPtr<ID3D12Device> 设备, ComPtr<ID3D12GraphicsCommandList> 命令队列, C共享资源* 共享资源, C描述符堆管理* 描述符堆管理);
	~C物体管理();
	void 加入静态物体FBX(wstring 物体名称, const WCHAR* 文件路径, DXGI_FORMAT 索引格式, float 体素粒度);
	void 加入动态物体FBX(wstring 物体名称, const WCHAR* 文件路径, DXGI_FORMAT 索引格式, float 体素粒度);
	void 加入静态物体MDS(wstring 物体名称, const WCHAR* 文件路径);
	void 加入动态物体MDD(wstring 物体名称, const WCHAR* 文件路径);
	void 删除动态物体(wstring 物体名称);
	void 删除静态物体(wstring 物体名称);
	//S拾取输出 是否选中静态(C静态物体* 物体, UINT 元素);
	//S拾取输出 是否选中动态(C动态物体* 物体, UINT 元素);

private:
	ComPtr<ID3D12Device> 设备;
	ComPtr<ID3D12GraphicsCommandList> 命令队列;
	C共享资源* 共享资源 = nullptr;
	C描述符堆管理* 描述符堆管理 = nullptr;
};