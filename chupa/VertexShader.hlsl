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
    float3 viewDirection : viewDir;
};

PixelInputType main(VertexInputType input)
{
	PixelInputType output;
    input.position.w = 1.0f;
    output.position = mul(input.position, input.WVP);
	output.color = input.color;

    // Determine the viewing direction based on the position of the camera and the position of the vertex in the world. &&  Normalize the viewing direction vector.
    output.viewDirection = normalize(input.position.xyz);
	
	return output;
}