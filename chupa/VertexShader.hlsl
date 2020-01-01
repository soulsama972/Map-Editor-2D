cbuffer CAMERAPROJ
{
	matrix proj;
	float3 cameraPos;
};

struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : tex;
	float3 pos : POS;
	float3 size : SIZE;

};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : tex;
};


PixelInputType main(VertexInputType input)
{
	PixelInputType output;
	input.position.w = 1.0f;
	output.position = input.position * float4(input.size, 1) + float4(input.pos, 0);
	output.position = mul(proj, output.position);

	output.tex = input.tex;
    
	return output;
}
