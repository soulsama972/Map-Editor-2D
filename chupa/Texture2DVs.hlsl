cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : tex;
	matrix WVP : world;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : tex;
};


PixelInputType main(VertexInputType input)
{
	PixelInputType output;
    
    // Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;
	float4 pos = float4(input.WVP._11, input.WVP._12, input.WVP._13, 0);
	float4 size = float4(input.WVP._21, input.WVP._22, input.WVP._23, 0);
	output.position = input.position * (size/2) + pos;
	output.position.w = 1;

    // Calculate the position of the vertex against the world, view, and projection matrices.
	//output.position = mul(input.position,input.WVP);
		// Calculate the position of the vertex against the world, view, and projection matrices.
	//output.position = mul(input.position, input.WVP);
	//output.position = mul(output.position, viewMatrix);
	//output.position = mul(output.position, projectionMatrix);
	//output.position = mul(input.WVP, input.position);
	output.position = mul(viewMatrix, output.position);
	output.position = mul(projectionMatrix,output.position);
	
	
    output.tex = input.tex;
    
	return output;
}
