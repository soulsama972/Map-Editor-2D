
struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
    float3 viewDirection : viewDir;
};

float4 main(PixelInputType input) : SV_TARGET
{
    float3 lightDirection = float3(-1, 1, 1.0f);

    float4 diffuseColor = float4(1.0f, 1.0f,1.0f, 1.0f);

    float3 normal = float3(0 , 0, -1);

    float3 lightDir;
    float lightIntensity;
    float4 color;
    float3 reflection;
    float4 specular;
    float4 lightColor = float4(1, 1, 1, 1);

    specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

    lightDir = -lightDirection;

    lightIntensity = saturate(dot(normal, lightDir));

    if (lightIntensity > 0.0f)
    {
        color = saturate((diffuseColor * lightIntensity));
 
        reflection = normalize(2 * lightIntensity * normal - lightDir);
      		
        specular = pow(saturate(dot(reflection, input.viewDirection)),1.0f);
        lightColor = lightColor * specular;
    }
    color = color * input.color;
    // Add the specular component last to the output color.
    color = saturate(color + lightColor);

    return color;




}