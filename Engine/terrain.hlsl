////////////////////////////////////////////////////////////////////////////////
// Filename: terrain.ps
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////
Texture2D shaderTexture[7];
SamplerState SampleType;

cbuffer LightBuffer
{
	float4 ambientColor;
	float4 diffuseColor;
    float3 lightDirection;
	float padding;
};


//////////////
// TYPEDEFS //
//////////////
struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
    float2 tex2 : TEXCOORD1;
	float4 worldPosition : TEXCOORD2;
};


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 TerrainPixelShader(PixelInputType input) : SV_TARGET
{
	float4 textureColor;
	float3 lightDir;
	float lightIntensity;
	float4 color;

	float slope;
	float blendAmount;

	float4 dirt01;
	float4 grass;
	float4 fire;
	float4 rock;
	float4 beach;
	float4 water;
	float4 alpha;

	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	dirt01 = shaderTexture[0].Sample(SampleType, input.tex);
	grass = shaderTexture[1].Sample(SampleType, input.tex);
	fire = shaderTexture[2].Sample(SampleType, input.tex);
	rock = shaderTexture[3].Sample(SampleType, input.tex);
	beach = shaderTexture[4].Sample(SampleType, input.tex);
	water = shaderTexture[5].Sample(SampleType, input.tex);
	alpha = shaderTexture[6].Sample(SampleType, input.tex2);
	
	
	textureColor = lerp(dirt01, grass, input.worldPosition.y / (255.0 / 25.0));
    textureColor = lerp(textureColor, rock, input.normal.y);
    textureColor = lerp(beach, textureColor, alpha);
	

	// Set the default output color to the ambient light value for all pixels.
    color = ambientColor;

	// Invert the light direction for calculations.
    lightDir = -lightDirection;

    // Calculate the amount of light on this pixel.
    lightIntensity = saturate(dot(input.normal, lightDir));

	if(lightIntensity > 0.0f)
    {
        // Determine the final diffuse color based on the diffuse color and the amount of light intensity.
        color += (diffuseColor * lightIntensity);
    }

    // Saturate the final light color.
    color = saturate(color);

	// Multiply the texture pixel and the final light color to get the result.
    color = color * textureColor;

    return color;
}