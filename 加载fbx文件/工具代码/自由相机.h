#pragma once
#include"d3dx12.h"
#include<DirectXMath.h>
#include"�������.h"

using namespace DirectX;

class C�������
{
public:
    void ���(XMMATRIX* �۲����, XMVECTOR ��ʼ�Ϸ���, XMVECTOR ��ʼǰ����, XMVECTOR ��ʼ����, float ת��������, float �ƶ��ٶ�);
    C�������(C�������* �������)
    {
        this->������� = �������;
    };
    ~C�������() {};

    XMVECTOR ǰ���� = { 0.0f, 0.0f, 1.0f, 0.0f };
    XMVECTOR �Ϸ��� = { 0.0f, 1.0f, 0.0f, 0.0f };
    XMVECTOR �ҷ��� = { 1.0f, 0.0f, 0.0f, 0.0f };
    XMVECTOR ������� = { 0.0f, 0.0f, 0.0f, 1.0f };
    C�������* �������;

private:
    XMVECTOR ����ǰ���� = { 0.0f, 0.0f, 0.0f, 0.0f };
    XMVECTOR ������ = { 0.0f, 0.0f, 0.0f, 1.0f };

    float ת�������ȴ��� = 0;
    bool ��ʼ�� = 1;
};

class C�������
{
public:
    void ���(XMMATRIX* �۲����, XMVECTOR ������, XMVECTOR ����ǰ����, XMVECTOR ��ʼ����, float ת��������, float �ƶ��ٶ�);
    C�������(C�������* �������)
    {
        this->������� = �������;
    }
    ~C�������() {};

    XMVECTOR ǰ���� = { 0.0f, 0.0f, 1.0f, 0.0f };
    XMVECTOR �Ϸ��� = { 0.0f, 1.0f, 0.0f, 0.0f };
    XMVECTOR �ҷ��� = { 1.0f, 0.0f, 0.0f, 0.0f };
    XMVECTOR ������� = { 0.0f, 0.0f, 0.0f, 1.0f };
    C�������* �������;

private:
    XMVECTOR ������ = { 0.0f, 0.0f, 0.0f, 1.0f };
    XMVECTOR ����ǰ���� = { 0.0f, 0.0f, 0.0f, 0.0f };
    XMVECTOR �����ᴢ�� = { 0.0f, 0.0f, 0.0f, 1.0f };
    XMVECTOR ������ǰ���� = { 0.0f, 0.0f, 0.0f, 0.0f };
    XMVECTOR ��λ�����ᴢ�� = { 0.0f, 0.0f, 0.0f, 0.0f };
    XMVECTOR ��ת���� = { 0.0f, 0.0f, 0.0f, 0.0f };
    XMVECTOR ����ǰ���� = { 0.0f, 0.0f, 0.0f, 0.0f };
    float ת�������ȴ��� = 0;
    float ǰ�ؽǶ�cos = 0;
    float ǰ�ؽǶ�sin = 0;
    float ��ת�������� = 0;
    bool ��ʼ�� = 1;
};

class C�����˳����
{
public:
    void ���(XMMATRIX* �۲����);
    C�����˳����(C�������* �������, float Phi, float Theta, float ��ʼ�뾶, float ת��������, float �ƶ��ٶ�, float ����������, XMVECTOR ����)
    {
        this->������� = �������;
        this->Phi = Phi;
        this->Theta = Theta;
        this->�뾶 = ��ʼ�뾶;
        this->�ƶ��ٶ� = �ƶ��ٶ�;
        this->ת�������� = ת��������;
        this->������ = ����;
        this->���������� = ����������;
    }
    ~C�����˳����() {};

    XMVECTOR ������� = { 0.0f, 0.0f, 0.0f, 1.0f };
    float Phi = 0;
    float Theta = 0;
    float �뾶 = 0;
    C�������* �������;
    float �ƶ��ٶ� = 0;
    float ת�������� = 0;
    float ���������� = 0;

private:
    XMVECTOR ������ = { 0.0f, 0.0f, 0.0f, 1.0f };
    XMVECTOR xzǰ���� = { 0.0f, 0.0f, 1.0f, 0.0f };
    XMVECTOR �Ϸ��� = { 0.0f, 1.0f, 0.0f, 0.0f };
    XMVECTOR �ҷ��� = { 0.0f, 0.0f, 1.0f, 0.0f };
    XMVECTOR �ƶ����� = { 0.0f, 0.0f, 0.0f, 0.0f };
    float ��ת�� = 0;
    float ����� = 0;
    XMMATRIX �任 = XMMatrixIdentity();
};