
struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
    float3 normal : normal;
};

float4 main(PixelInputType input) : SV_TARGET
{
    float3 lightDirection = float3(0, 0, 1);
    float4 diffuseColor = saturate(dot(lightDirection, input.normal) * input.color);


    float3 lightDir;
    float lightIntensity;
    float4 color;

    float3 reflection = reflect(lightDirection, input.normal.xyz);

    // Calculate the specular light based on the reflection and the camera position.
    //Increase the specular light by the shininess value.

    // Calculate the specular light based on the reflection and the camera position.
    float specular = dot(normalize(reflection), float3(0, 0,-1));

    // Check to make sure the specular was positive so we aren't adding black spots to the water.
    if (specular > 0.0f)
    {

            //  // Increase the specular light by the shininess value.
        specular = pow(specular, 64.0f);

        // Add the specular to the final color.
        color = saturate(specular) * input.color;

    }

    return color;




}