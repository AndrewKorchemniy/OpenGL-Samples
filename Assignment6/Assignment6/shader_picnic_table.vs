#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

uniform vec3 Ambient;
uniform vec3 MaterialColor;
uniform vec3 LightColor;
uniform vec4 LightPosition; // in camera or eye coordinate

out vec4 fColor;
vec4 eyeSpacePosition;  // converts vertex position to the eyespace
vec3 eyeSpaceNormal;    // converts vertex normals to the eyespace

void main(void) {
	eyeSpacePosition = view_matrix*model_matrix*position;
	eyeSpaceNormal = mat3(view_matrix*model_matrix)*normal;

	vec3 N = normalize(eyeSpaceNormal); 
	vec3 L = normalize(LightPosition.xyz-eyeSpacePosition.xyz);
	vec3 diffuse = LightColor* (max(dot(L,N), 0.0));

	vec4 scatteredLight = vec4((Ambient+diffuse)*vec3(MaterialColor), 1.0);
	fColor = min(scatteredLight, vec4(1.0));

	//color = min(vec4(MaterialColor*Ambient, 1.0), vec4(1.0));
	gl_Position = projection_matrix*view_matrix*model_matrix*position;
}
