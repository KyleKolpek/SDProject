#version 120

uniform mat4 modelView;
uniform mat4 normalModelView;
uniform mat4 projection;

attribute vec3 vertexPosition;
attribute vec3 vertexNormal;

varying vec3 normal;
varying vec3 cameraSpacePos;
varying vec3 position;

void main( void )
{
    vec4 p = modelView * vec4(vertexPosition, 1.0);
    position = p * projection;
	
	cameraSpacePos = p.xyz;
	normal = normalize(normalModelView * vec4(vertexPosition, 0.0));
}
