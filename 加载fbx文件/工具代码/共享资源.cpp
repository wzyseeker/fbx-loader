#include"������Դ.h"

C������Դ::C������Դ(ComPtr<ID3D12Device> �豸, ComPtr<ID3D12GraphicsCommandList> �������)
{
	this->�豸 = �豸;
	this->������� = �������;
}

void C������Դ::������ͼ()
{
	CreateDDSTextureFromFile12(�豸.Get(), �������.Get(), L"��ͼ\\whitetex.dds", ����ͼ, ����ͼ�ϴ�, 0, 0);
}

C������Դ::~C������Դ()
{

}