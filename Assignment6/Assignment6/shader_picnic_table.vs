//#version 430 core

//layout (location = 0) in vec4 position;

//uniform mat4 model_matrix;
//uniform mat4 view_matrix;
//uniform mat4 projection_matrix;
//uniform vec3 Ambient;
//uniform vec3 MaterialColor;

//out vec4 color;

//void main(void)
//{
//	color = min(vec4(MaterialColor*Ambient, 1.0), vec4(1.0));
//	gl_Position = projection_matrix*view_matrix*model_matrix*position;
//}

#version 430 core

layout mat4 model_matrix;
layout mat4 view_matrix;
layout mat4 projection_matrix;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

uniform vec3 Ambient;
uniform vec3 LightColor;
uniform vec4 LightPosition;

out vec4 color;

void main(void) {
	vec4 eyesSpacePosition = view_matrix*model_matrix*position;
	vec3 lightDirection = LightPosition.xyz - eyesSpacePosition.xyz;
	vec3 L = normalize(lightDirection);
	vec3 eyeSpaceNormal = mat3(view_matrix*model_matrix)*normal;
	vec3 N = normalize(eyeSpaceNormal);
	vec3 diffuse = (max(dot(N, L), 0))*LightColor;
}