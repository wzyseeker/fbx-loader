#include"共享资源.h"

C共享资源::C共享资源(ComPtr<ID3D12Device> 设备, ComPtr<ID3D12GraphicsCommandList> 命令队列)
{
	this->设备 = 设备;
	this->命令队列 = 命令队列;
}

void C共享资源::加载贴图()
{
	CreateDDSTextureFromFile12(设备.Get(), 命令队列.Get(), L"贴图\\whitetex.dds", 白贴图, 白贴图上传, 0, 0);
}

C共享资源::~C共享资源()
{

}