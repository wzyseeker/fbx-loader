#pragma once
#include<windows.h>

const UINT FVF位置 = 0x00000001;
const UINT FVF法向量 = 0x00000002;
const UINT FVF纹理坐标 = 0x00000004;
const UINT FVF切向量 = 0x0000008;
const UINT FVF关联骨骼 = 0x00000010;
const UINT FVF权重 = 0x00000011;
const UINT FVF数量 = 6;
const UINT FVF描述数量 = 3;
const UINT d骨骼动画描述 = 0x00000001 | 0x00000002 | 0x00000004 | 0x0000008 | 0x00000010 | 0x00000011;
const UINT d骨骼动画描述无切线 = 0x00000001 | 0x00000002 | 0x00000004 | 0x00000010 | 0x00000011;
const UINT d静态物体描述 = 0x00000001 | 0x00000002 | 0x00000004;
const UINT d最大骨骼索引数量 = 4;
const UINT d最大骨骼数量 = 64;