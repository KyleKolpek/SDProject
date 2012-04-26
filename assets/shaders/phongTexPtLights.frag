#version 120

uniform sampler2D texture;
uniform float coefficient;
uniform int lightCount;

// Could probably stand to combine these into a struct
uniform vec3 cameraSpaceLights[20];
uniform vec3 lightColors[20];

varying vec3 normal;
varying vec3 cameraSpacePos;
varying vec2 texCoord;

vec3 calcSpecular(vec3 l, vec3 n, vec3 v, vec3 cL, vec3 cS, float p)
{
    vec3 r =  reflect(l, n);
    return cL * cS * pow(max(0.0, dot(r, normalize(v))), p);
}

vec3 calcDiffuse(vec3 l, vec3 n, vec3 cL, vec3 cD)
{
    return cL * cD * max(0.0, dot(n, l));
}

void main(void)
{
	vec3 lightDirection;
	vec3 lightDistance;
	vec3 objectColor;
	vec3 ambientColor   = vec3(0.005, 0.005, 0.005);
	vec3 specularColor  = vec3(0.0, 0.0, 0.0);
	vec3 n              = normalize(normal);
	vec3 outColor       = ambientColor * objectColor;

	for(int i=0; i < lightCount; i++)
	{
		lightDistance = cameraSpacePos - cameraSpaceLights[i];
		lightDirection = normalize(lightDistance);
		objectColor = texture2D(texture, texCoord).xyz;
		outColor += (ambientColor * objectColor +
					calcDiffuse(-lightDirection, n, lightColors[i],
						objectColor) +
					calcSpecular(-lightDirection, n, -cameraSpacePos,
						lightColors[i], specularColor, 1.0)) *
					(1 / pow(length(lightDistance/8), 2));
	}

    gl_FragColor = vec4(outColor, 1.0);
}
