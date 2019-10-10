
struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
    float3 viewDirection : viewDir;
};

float4 main(PixelInputType input) : SV_TARGET
{
    float3 lightDirection = float3(-1, 1, 1);

    float4 diffuseColor = float4(0.9f, 0.9f, 0.9f, 1.0f);

    float3 normal = float3(0, 0, -1);

    float3 lightDir;
    float lightIntensity;
    float4 color;
    float3 reflection;
    float4 specular;
    float4 lightColor = float4(1, 1, 1, 1);
    // Initialize the specular color.
    specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

    // Invert the light direction for calculations.
    lightDir = -lightDirection;

    // Calculate the amount of light on this pixel.
    lightIntensity = saturate(dot(normal, lightDir));

    if (lightIntensity > 0.0f)
    {
    // Determine the final diffuse color based on the diffuse color and the amount of light intensity.
		//and Saturate the ambient and diffuse color.
        color = saturate((diffuseColor * lightIntensity));
 
    // Calculate the reflection vector based on the light intensity, normal vector, and light direction.
        reflection = normalize(2 * lightIntensity * normal - lightDir);
      		
    // Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
        specular = pow(saturate(dot(reflection, input.viewDirection)),2.0f);
        lightColor = lightColor * specular;
    }
	// Multiply the texture pixel and the input color to get the textured result.
    color = color * input.color;
    // Add the specular component last to the output color.
    color = saturate(color + lightColor);

    return color;




}