
struct VertexInputType
{
	float4 position : POSITION;
	float4 color : COLOR;
    matrix WVP : world;
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
    output.position = mul(input.position, input.WVP);
	output.color = input.color;


	return output;
}