struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD;
	matrix WVP : world;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD;
};


PixelInputType main(VertexInputType input)
{
	PixelInputType output;
    
    // Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
	//output.position = mul(input.position, input.WVP);
	output.position = input.position;
    output.tex = input.tex;
    
	return output;
}
