//cbuffer matrixType
//{
//	matrix proj;
//	matrix view;
//	matrix q;
//};

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
	output.position = mul(mul(translate, mScale),input.position);
	//output.position = mul(view, output.position);
	//output.position = mul(proj, output.position);
	output.color = input.color;


	return output;
}