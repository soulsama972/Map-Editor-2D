cbuffer  CAMERAPROJ
{
	matrix proj;
	float3 cameraPos;
};


struct VertexInputType
{
	float4 position : POSITION;
	float3 pos : POS;
	float3 size : SIZE;
	float4 color : COLOR;

};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};


PixelInputType main(VertexInputType input) 
{
	PixelInputType output;

	input.position.w = 1.0f;
	input.pos.x -= cameraPos.x;
	input.pos.y += cameraPos.y;
	input.pos.z -= cameraPos.z;
	output.position = input.position * float4(input.size, 1) + float4(input.pos, 0);


	output.position = mul(proj, output.position);

	output.color = input.color;

	return output;
}