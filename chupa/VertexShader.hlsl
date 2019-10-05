struct VertexInputType
{
	float4 position : POSITION;
    float2 pos : TEXCOORD0;
	float2 scale : TEXCOORD1; 
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
	matrix mScale =
	{
		{ input.scale.x, 0, 0, 0 },
		{ 0, input.scale.y, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	};
	matrix translate =
	{
		{ 1, 0, 0,input.pos.x},
		{ 0, 1, 0, input.pos.y},
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	};
	input.position.w = 1.0f;
	matrix world = mul(translate,mScale);
	output.position = mul(world,input.position);
	output.color = input.color;


	return output;
}