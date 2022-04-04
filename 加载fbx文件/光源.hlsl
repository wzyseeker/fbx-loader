//***************************************************************************************
// color.hlsl by Frank Luna (C) 2015 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************
#pragma pack_matrix(row_major)

struct DirLight
{
	float4 Diffuse;
	float4 Direction;
};

struct Material
{
	float4 Diffuse;
	float4 Emissive;
	float4 Ambient;
	float Specular;
	float Power;
	float Reflect;
	float pad;
};

cbuffer cbConstantObject : register(b0)
{
	float4x4 gViewProj;
	float4 gEyePosW;
	DirLight gDlight;
};

cbuffer cbUpdateObject : register(b1)
{
	float4x4 gWorld;
	Material gMat;
};

Texture2D gDiffuseMap : register(t0);

SamplerState gsamLinearWrap : register(s0);

struct VertexIn
{
	float3 Pos  : POSITION;
	float3 Normal : NORMAL;
    float2 Tex : TEXCOORD;
};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
	float3 PosW : POSITION;
	float3 NormalW : NORMAL;
	float2 Tex : TEXCOORD;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	
	vout.PosW = mul(float4(vin.Pos, 1.0f), gWorld).xyz;
	vout.NormalW = normalize(mul(vin.Normal, (float3x3) gWorld));
		
	vout.PosH = mul(float4(vout.PosW, 1.0f), gViewProj);
	
	vout.Tex = vin.Tex;
    
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	float3 toEyeW = normalize((float3) gEyePosW - pin.PosW);
	
	float3 normal = pin.NormalW;
	
	float3 lightVec = normalize(gDlight.Direction.xyz);
	float front = max(dot(-lightVec, normal), 0.0f);

	float3 diffuse = front * gMat.Diffuse.rgb * gDlight.Diffuse.rgb;
	
	float spec = pow(max(dot(reflect(lightVec, normal), toEyeW), 0.0f), gMat.Specular);
	
	float3 specular = gMat.Ambient.rgb + diffuse * 0.5 + (diffuse + gDiffuseMap.Sample(gsamLinearWrap, pin.Tex).rgb) * spec;
	
	return float4(specular, gMat.Diffuse.a);
}


