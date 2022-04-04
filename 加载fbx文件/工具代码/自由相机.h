#pragma once
#include"d3dx12.h"
#include<DirectXMath.h>
#include"按键检测.h"

using namespace DirectX;

class C自由相机
{
public:
    void 相机(XMMATRIX* 观察矩阵, XMVECTOR 初始上方向, XMVECTOR 初始前方向, XMVECTOR 初始坐标, float 转向灵敏度, float 移动速度);
    C自由相机(C按键检测* 按键检测)
    {
        this->按键检测 = 按键检测;
    };
    ~C自由相机() {};

    XMVECTOR 前方向 = { 0.0f, 0.0f, 1.0f, 0.0f };
    XMVECTOR 上方向 = { 0.0f, 1.0f, 0.0f, 0.0f };
    XMVECTOR 右方向 = { 1.0f, 0.0f, 0.0f, 0.0f };
    XMVECTOR 相机坐标 = { 0.0f, 0.0f, 0.0f, 1.0f };
    C按键检测* 按键检测;

private:
    XMVECTOR 保存前方向 = { 0.0f, 0.0f, 0.0f, 0.0f };
    XMVECTOR 看坐标 = { 0.0f, 0.0f, 0.0f, 1.0f };

    float 转向灵敏度储存 = 0;
    bool 初始化 = 1;
};

class C重力相机
{
public:
    void 相机(XMMATRIX* 观察矩阵, XMVECTOR 重力轴, XMVECTOR 开局前方向, XMVECTOR 初始坐标, float 转向灵敏度, float 移动速度);
    C重力相机(C按键检测* 按键检测)
    {
        this->按键检测 = 按键检测;
    }
    ~C重力相机() {};

    XMVECTOR 前方向 = { 0.0f, 0.0f, 1.0f, 0.0f };
    XMVECTOR 上方向 = { 0.0f, 1.0f, 0.0f, 0.0f };
    XMVECTOR 右方向 = { 1.0f, 0.0f, 0.0f, 0.0f };
    XMVECTOR 相机坐标 = { 0.0f, 0.0f, 0.0f, 1.0f };
    C按键检测* 按键检测;

private:
    XMVECTOR 看坐标 = { 0.0f, 0.0f, 0.0f, 1.0f };
    XMVECTOR 保存前方向 = { 0.0f, 0.0f, 0.0f, 0.0f };
    XMVECTOR 重力轴储存 = { 0.0f, 0.0f, 0.0f, 1.0f };
    XMVECTOR 重力轴前方向 = { 0.0f, 0.0f, 0.0f, 0.0f };
    XMVECTOR 单位重力轴储存 = { 0.0f, 0.0f, 0.0f, 0.0f };
    XMVECTOR 旋转向量 = { 0.0f, 0.0f, 0.0f, 0.0f };
    XMVECTOR 重力前向量 = { 0.0f, 0.0f, 0.0f, 0.0f };
    float 转向灵敏度储存 = 0;
    float 前重角度cos = 0;
    float 前重角度sin = 0;
    float 旋转向量长度 = 0;
    bool 初始化 = 1;
};

class C第三人称相机
{
public:
    void 相机(XMMATRIX* 观察矩阵);
    C第三人称相机(C按键检测* 按键检测, float Phi, float Theta, float 初始半径, float 转向灵敏度, float 移动速度, float 滑轮灵敏度, XMVECTOR 看点)
    {
        this->按键检测 = 按键检测;
        this->Phi = Phi;
        this->Theta = Theta;
        this->半径 = 初始半径;
        this->移动速度 = 移动速度;
        this->转向灵敏度 = 转向灵敏度;
        this->看坐标 = 看点;
        this->滑轮灵敏度 = 滑轮灵敏度;
    }
    ~C第三人称相机() {};

    XMVECTOR 相机坐标 = { 0.0f, 0.0f, 0.0f, 1.0f };
    float Phi = 0;
    float Theta = 0;
    float 半径 = 0;
    C按键检测* 按键检测;
    float 移动速度 = 0;
    float 转向灵敏度 = 0;
    float 滑轮灵敏度 = 0;

private:
    XMVECTOR 看坐标 = { 0.0f, 0.0f, 0.0f, 1.0f };
    XMVECTOR xz前方向 = { 0.0f, 0.0f, 1.0f, 0.0f };
    XMVECTOR 上方向 = { 0.0f, 1.0f, 0.0f, 0.0f };
    XMVECTOR 右方向 = { 0.0f, 0.0f, 1.0f, 0.0f };
    XMVECTOR 移动距离 = { 0.0f, 0.0f, 0.0f, 0.0f };
    float 旋转角 = 0;
    float 方向角 = 0;
    XMMATRIX 变换 = XMMatrixIdentity();
};