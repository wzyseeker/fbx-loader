//骨骼动画的实现，适用于大多数物体
#pragma pack_matrix(row_major)

static uint MAXBONENUM = 4;

struct DIRLIGHT
{
	float4 color;
	float4 direction;
};

struct MATERAL
{
	float4 diffuse;
	float4 emissive;
	float4 ambient;
	float specular;
	float power;
	float reflect;
	float pad;
};

cbuffer Constbuffer : register(b0)
{
	DIRLIGHT dlight;
	float4x4 gViewProj;
	float4 gEyePosW;
}

cbuffer Updatebuffer : register(b1)
{
	MATERAL mat;
	float4x4 gBoneTransform[128];
}

cbuffer PerUpdatebuffer : register(b2)
{
	float4x4 gWorld;
	float4x4 gObj;
}

Texture2D gDiffuseMap : register(t0);

SamplerState gsamLinearWrap : register(s0);

struct VertexOut
{
	float4 PosH : SV_POSITION;
	float3 PosW : POSITION;
	float3 NormalW : NORMAL;
	float2 Tex : TEXCOORD0;
};

//点光源无法线贴图---------------------------------------------------------------------------------------
VertexOut VSSpot(float3 PosL : POSITION, float3 NormalL : NORMAL, float2 Tex : TEXCOORD,
				 float3 Weight : WEIGHT, uint4 BoneIndex : BONEINDEX)
{
	VertexOut VOut;
	
	VOut.Tex = Tex;
	
	float3 bPosL = float3(0.0f, 0.0f, 0.0f);
	float3 bNormalL = float3(0.0f, 0.0f, 0.0f);
	float3 oPosL = mul(float4(PosL, 1.0f), gObj).xyz;
	float3 oNormalL = mul(NormalL, (float3x3) gObj).xyz;
	float3 transform1;
	
	float bWeight[4] = { Weight.x, Weight.y, Weight.z, 0.0f };
	bWeight[3] = 1.0f - Weight.x - Weight.y - Weight.z;
	for (uint i = 0; i < MAXBONENUM; i++)
	{
		bPosL += bWeight[i] * mul(float4(oPosL, 1.0f), gBoneTransform[BoneIndex[i]]).xyz;
		bNormalL += bWeight[i] * normalize(mul(oNormalL, (float3x3) gBoneTransform[BoneIndex[i]]));
	}
	VOut.PosW = mul(float4(bPosL, 1.0f), gWorld).xyz;
	VOut.PosH = mul(mul(float4(bPosL, 1.0f), gWorld), gViewProj);
	VOut.NormalW = normalize(mul(bNormalL, (float3x3) gWorld));
	
	return VOut;
}

float4 PSSpot(VertexOut PIn) : SV_Target
{
	float3 ToEyeW = normalize(gEyePosW.xyz - PIn.PosW);
	float Lenght = length(gEyePosW.xyz - PIn.PosW);
	
	float3 lightVec = -ToEyeW;
	float front = max(dot(-lightVec, PIn.NormalW), 0.0f);

	float3 diffuse = front * dlight.color.rgb * mat.diffuse.rgb;
	
	float spec = pow(max(dot(reflect(lightVec, PIn.NormalW), ToEyeW), 0.0f), mat.power);
	
	float3 specular = dlight.color.rgb * spec * mat.specular / sqrt(Lenght);
	
	float4 texColor = gDiffuseMap.Sample(gsamLinearWrap, PIn.Tex);
	
	return float4(texColor.rgb * 0.5 + diffuse + specular, mat.diffuse.a);
}