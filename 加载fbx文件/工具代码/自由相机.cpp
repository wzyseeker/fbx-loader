#include "自由相机.h"

void C自由相机::相机(XMMATRIX* 观察矩阵, XMVECTOR 初始上方向, XMVECTOR 初始前方向, XMVECTOR 初始坐标, float 转向灵敏度, float 移动速度)
{
    if (初始化)
    {
        前方向 = XMVector3Normalize(初始前方向);
        右方向 = XMVector3Cross(初始上方向, 前方向);
        右方向 = XMVector3Normalize(右方向);
        上方向 = XMVector3Cross(前方向, 右方向);
        上方向 = XMVector3Normalize(上方向);
        相机坐标 = 初始坐标;
        初始化 = 0;
    }

    if (转向灵敏度储存 != 转向灵敏度) 转向灵敏度 = sinf(转向灵敏度), 转向灵敏度储存 = 转向灵敏度;

    if (按键检测->键W状态)
        相机坐标 = 相机坐标 + 移动速度 * 前方向;

    if (按键检测->键S状态)
        相机坐标 = 相机坐标 - 移动速度 * 前方向;

    if (按键检测->键D状态)
        相机坐标 = 相机坐标 - 移动速度 * 右方向;

    if (按键检测->键A状态)
        相机坐标 = 相机坐标 + 移动速度 * 右方向;

    if (按键检测->键space状态)
        相机坐标 = 相机坐标 + 移动速度 * 上方向;

    if (按键检测->键shift状态)
        相机坐标 = 相机坐标 - 移动速度 * 上方向;

    if (按键检测->鼠标位移.x != 0 || 按键检测->鼠标位移.y != 0)
    {
        前方向 = 前方向 + 右方向 * 转向灵敏度 * 按键检测->鼠标位移.x / 10;
        前方向 = 前方向 + 上方向 * 转向灵敏度 * 按键检测->鼠标位移.y / 10;
    }
    if (!按键检测->鼠标边界状态) 按键检测->鼠标位移 = { 0, 0 };
    
    if (按键检测->键X状态)
        上方向 = 上方向 - 右方向 * 转向灵敏度;

    if (按键检测->键Z状态)
        上方向 = 上方向 + 右方向 * 转向灵敏度;

    前方向 = XMVector3Normalize(前方向);
    右方向 = XMVector3Cross(上方向, 前方向);
    右方向 = XMVector3Normalize(右方向);
    上方向 = XMVector3Cross(前方向, 右方向);
    上方向 = XMVector3Normalize(上方向);

    看坐标 = 相机坐标 + 前方向;

    *观察矩阵 = XMMatrixLookAtRH(相机坐标, 看坐标, 上方向);
}

//重力相机
void C重力相机::相机(XMMATRIX* 观察矩阵, XMVECTOR 重力轴, XMVECTOR 开局前方向, XMVECTOR 初始坐标, float 转向灵敏度, float 移动速度)
{
    if (转向灵敏度储存 != 转向灵敏度) 转向灵敏度, 转向灵敏度储存 = 转向灵敏度;

    if (初始化)
    {
        单位重力轴储存 = XMVector3Normalize(-重力轴);
        前方向 = XMVector3Normalize(开局前方向);
        右方向 = XMVector3Cross(单位重力轴储存, 前方向);
        右方向 = XMVector3Normalize(右方向);
        上方向 = XMVector3Cross(前方向, 右方向);
        上方向 = XMVector3Normalize(上方向);
        重力轴储存 = XMVector3Normalize(重力轴);
        相机坐标 = 初始坐标;
        初始化 = 0;
    }

    if (XMVector3Dot(重力轴储存, XMVector3Normalize(重力轴)).m128_f32[0] < 0.95)
    {
        单位重力轴储存 = XMVector3Normalize(-重力轴);
        前方向 = XMVector3Normalize(前方向);
        右方向 = XMVector3Cross(单位重力轴储存, 前方向);
        右方向 = XMVector3Normalize(右方向);
        上方向 = XMVector3Cross(前方向, 右方向);
        上方向 = XMVector3Normalize(上方向);
        重力轴储存 = XMVector3Normalize(重力轴);
    }

    if (按键检测->键W状态)
    {
        重力轴前方向 = XMVector3Cross(右方向, 单位重力轴储存);
        相机坐标 = 相机坐标 + 移动速度 * 重力轴前方向;
    }

    if (按键检测->键S状态)
    {
        重力轴前方向 = XMVector3Cross(右方向, 单位重力轴储存);
        相机坐标 = 相机坐标 - 移动速度 * 重力轴前方向;
    }

    if (按键检测->键D状态)
        相机坐标 = 相机坐标 - 移动速度 * 右方向;

    if (按键检测->键A状态)
        相机坐标 = 相机坐标 + 移动速度 * 右方向;

    if (按键检测->键space状态)
        相机坐标 = 相机坐标 + 移动速度 * 单位重力轴储存;

    if (按键检测->键shift状态)
        相机坐标 = 相机坐标 - 移动速度 * 单位重力轴储存;


    if (按键检测->鼠标位移.x != 0 || 按键检测->鼠标位移.y != 0)
    {
        前重角度cos = XMVector3Dot(单位重力轴储存, 前方向).m128_f32[0];
        旋转向量 = 前方向 - 单位重力轴储存 * 前重角度cos;
        旋转向量长度 = XMVector3Length(旋转向量).m128_f32[0];
        旋转向量 = 旋转向量 + 右方向 * 转向灵敏度 * 按键检测->鼠标位移.x / 10;
        旋转向量 = 旋转向量 * 旋转向量长度 / XMVector3Length(旋转向量);
        前方向 = 旋转向量 + 单位重力轴储存 * 前重角度cos;

        保存前方向 = 前方向;
        前方向 = 前方向 + 上方向 * 转向灵敏度 * 按键检测->鼠标位移.y / 10;
        前方向 = XMVector3Normalize(前方向);
        if (fabs(XMVector3Dot(单位重力轴储存, 前方向).m128_f32[0]) > 0.95)
            前方向 = 保存前方向;
    }

    前方向 = XMVector3Normalize(前方向);
    右方向 = XMVector3Cross(单位重力轴储存, 前方向);
    右方向 = XMVector3Normalize(右方向);
    上方向 = XMVector3Cross(前方向, 右方向);
    上方向 = XMVector3Normalize(上方向);

    看坐标 = 相机坐标 + 前方向;

    *观察矩阵 = XMMatrixLookAtRH(相机坐标, 看坐标, 上方向);
}

void C第三人称相机::相机(XMMATRIX* 观察矩阵)
{
    if (按键检测->鼠标右键状态 && !按键检测->鼠标边界状态)
    {
        if (按键检测->鼠标位移.x != 0 || 按键检测->鼠标位移.y != 0)
        {
            float dx = XMConvertToRadians((float)(按键检测->鼠标位移.x) * 转向灵敏度);
            float dy = XMConvertToRadians((float)(按键检测->鼠标位移.y) * 转向灵敏度);

            Theta += dx;
            Phi += dy;

            if (Phi >= XM_PI) Phi = XM_PI - 0.01;
            if (Phi <= 0)  Phi = 0.01;
        }
    }
    
    if (按键检测->鼠标滑轮状态 != 0)
    {
        半径 -= 按键检测->鼠标滑轮状态 * 滑轮灵敏度;
        if (半径 < 1.0f) 半径 = 1.0f;
        if (半径 > 200.0f) 半径 = 200.0f;
        按键检测->鼠标滑轮状态 = 0;
    }

    float x = 半径 * sinf(Phi) * cosf(Theta);
    float z = 半径 * sinf(Phi) * sinf(Theta);
    float y = 半径 * cosf(Phi);

    上方向 = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    if (按键检测->鼠标边界状态)
    {
        右方向 = XMVector3Normalize(XMVector3Cross(上方向, XMVector3Normalize(看坐标 - 相机坐标)));
        xz前方向 = XMVector3Normalize(XMVector3Cross(右方向, 上方向));
        旋转角 = acosf(XMVector3Dot(xz前方向, XMVECTOR{ 1.0f, 0.0f, 0.0f, 0.0f }).m128_f32[0]);
        方向角 = XMVector3Dot(xz前方向, XMVECTOR{ 0.0f, 0.0f, 1.0f, 0.0f }).m128_f32[0];
        if (方向角 > 0) 旋转角 = -旋转角;
        变换 = XMMatrixRotationAxis(XMVECTOR{ 0.0f, 1.0f, 0.0f, 0.0f }, 旋转角);
        移动距离 = XMVECTOR{ -按键检测->鼠标位移.y * 移动速度, 0.0f, 按键检测->鼠标位移.x * 移动速度, 0.0f };
        移动距离 = XMVector3TransformCoord(移动距离, 变换);
        看坐标 += 移动距离;
    }

    相机坐标 = 看坐标 + XMVectorSet(x, y, z, 0.0f);

    *观察矩阵 = XMMatrixLookAtRH(相机坐标, 看坐标, 上方向);
}