#version 120

uniform sampler2D texture;

varying vec3 normal;
varying vec3 cameraSpacePos;
varying vec2 texCoord;

vec3 calcSpecular(vec3 l, vec3 n, vec3 v, vec3 cL, vec3 cS, float p)
{
    vec3 r =  2.0 * n * dot(n, l) - l;
    return cL * cS * pow(max(0.0, dot(r, normalize(v))), p);
}

vec3 calcDiffuse(vec3 l, vec3 n, vec3 cL, vec3 cD)
{
    return cL * cD * max(0.0, dot(n, l));
}

void main(void)
{
    vec3 lightDirection = normalize(vec3(-1.0, -0.5, -1.0));
    vec3 objectColor    = texture2D(texture, texCoord).xyz;
    vec3 ambientColor   = vec3(0.3, 0.3, 0.3);
    vec3 lightColor     = vec3(0.3, 0.3, 0.3);
    vec3 specularColor  = vec3(1.0, 1.0, 1.0);

    vec3 n = normalize(normal);
    gl_FragColor = vec4(
                   ambientColor * objectColor +
                   calcDiffuse(-lightDirection, n, lightColor,
                        objectColor) +
                   calcSpecular(-lightDirection, n, -cameraSpacePos,
                           lightColor, specularColor, 64.0),1.0);
}
