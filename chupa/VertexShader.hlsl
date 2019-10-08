
struct VertexInputType
{
	float4 position : POSITION;
	float4 color : COLOR;
    matrix WVP : world;
    float3 normal : normal;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
    float3 normal : normal;
};

PixelInputType main(VertexInputType input)
{
	PixelInputType output;
    input.position.w = 1.0f;
    output.position = mul(input.position, input.WVP);
	output.color = input.color;

    output.normal = mul(input.normal, (float3x3)input.WVP);
	


    // Normalize the normal vector.
    output.normal = normalize(output.normal);

	

	return output;
}