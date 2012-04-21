#version 120

uniform mat4 modelView;
uniform mat4 normalModelView;
uniform mat4 projection;

attribute vec3 vertexPosition;
attribute vec3 vertexNormal;
attribute vec2 vertexTexCoord;

varying vec3 normal;
varying vec3 cameraSpacePos;
varying vec2 texCoord;

void main(void)
{
	vec4 p = modelView * vec4(vertexPosition, 1.0);
	gl_Position = projection * p;

	cameraSpacePos = p.xyz;
	normal = normalize(normalModelView * vec4(vertexNormal, 0.0)).xyz;

	texCoord = vertexTexCoord;
}
