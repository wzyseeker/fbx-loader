#include"物体管理.h"

C物体管理::C物体管理(ComPtr<ID3D12Device> 设备, ComPtr<ID3D12GraphicsCommandList> 命令队列, C共享资源* 共享资源, C描述符堆管理* 描述符堆管理)
{
	this->设备 = 设备;
	this->命令队列 = 命令队列;
	this->共享资源 = 共享资源;
	this->描述符堆管理 = 描述符堆管理;
}

void C物体管理::加入静态物体FBX(wstring 物体名称, const WCHAR* 文件路径, DXGI_FORMAT 索引格式, float 体素粒度)
{
	静态物体.insert(pair<wstring, C静态物体*>(物体名称, 0));

	静态物体[物体名称] = new C静态物体(设备, 命令队列, 描述符堆管理, 共享资源);
	静态物体[物体名称]->加载FBX文件(文件路径, 物体名称, 索引格式, 体素粒度);
}

void C物体管理::加入动态物体FBX(wstring 物体名称, const WCHAR* 文件路径, DXGI_FORMAT 索引格式, float 体素粒度)
{
	动态物体.insert(pair<wstring, C动态物体*>(物体名称, 0));

	动态物体[物体名称] = new C动态物体(设备, 命令队列, 描述符堆管理, 共享资源);
	动态物体[物体名称]->加载FBX文件(文件路径, 物体名称, 索引格式, 体素粒度);
}

void C物体管理::加入静态物体MDS(wstring 物体名称, const WCHAR* 文件路径)
{
	静态物体.insert(pair<wstring, C静态物体*>(物体名称, 0));

	静态物体[物体名称] = new C静态物体(设备, 命令队列, 描述符堆管理, 共享资源);
	静态物体[物体名称]->导入mds文件(文件路径, 物体名称);
}

void C物体管理::加入动态物体MDD(wstring 物体名称, const WCHAR* 文件路径)
{
	动态物体.insert(pair<wstring, C动态物体*>(物体名称, 0));

	动态物体[物体名称] = new C动态物体(设备, 命令队列, 描述符堆管理, 共享资源);
	动态物体[物体名称]->导入mdd文件(文件路径, 物体名称);
}

void C物体管理::删除静态物体(wstring 物体名称)
{
	delete 静态物体[物体名称];
	静态物体.erase(物体名称);
}

void C物体管理::删除动态物体(wstring 物体名称)
{
	delete 动态物体[物体名称];
	动态物体.erase(物体名称);
}

/*
S拾取输出 C物体管理::是否选中静态(C静态物体* 物体, UINT 元素)
{
	S拾取输出 是否选中;

	命令队列->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(物体->属性->元素[元素].拾取输出.Get(),
		D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_COPY_SOURCE));

	命令队列->CopyResource(物体->属性->元素[元素].拾取输出读回.Get(), 物体->属性->元素[元素].拾取输出.Get());

	命令队列->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(物体->属性->元素[元素].拾取输出.Get(),
		D3D12_RESOURCE_STATE_COPY_SOURCE, D3D12_RESOURCE_STATE_UNORDERED_ACCESS));

	S拾取输出* map资源 = nullptr;
	物体->属性->元素[元素].拾取输出读回->Map(0, nullptr, (void**)&map资源);

	if (map资源->是否拾取 == 1)
	{
		是否选中.是否拾取 = 1;
		是否选中.距离 = map资源->距离;

		map资源->是否拾取 = 0;
		物体->属性->元素[元素].拾取输出上传->Map(0, nullptr, (void**)&map资源);

		命令队列->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(物体->属性->元素[元素].拾取输出.Get(),
			D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_COPY_DEST));

		命令队列->CopyResource(物体->属性->元素[元素].拾取输出.Get(), 物体->属性->元素[元素].拾取输出上传.Get());

		命令队列->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(物体->属性->元素[元素].拾取输出.Get(),
			D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_UNORDERED_ACCESS));
	}
	else
	{
		是否选中.是否拾取 = 0;
	}

	物体->属性->元素[元素].拾取输出->Unmap(0, nullptr);
		
	return 是否选中;
}
*/

C物体管理::~C物体管理()
{
	map<wstring, C动态物体*>::iterator it动态;

	it动态 = 动态物体.begin();
	for (int i = 0; i < 动态物体.size(); i++)
	{
		delete (*it动态).second;
		it动态++;
	}

	map<wstring, C静态物体*>::iterator it静态;

	it静态 = 静态物体.begin();
	for (int i = 0; i < 静态物体.size(); i++)
	{
		delete (*it静态).second;
		it静态++;
	}
}