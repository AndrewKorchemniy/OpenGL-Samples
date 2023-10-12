#version 430 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

uniform mat4 trans_matrix;
uniform mat4 scale_matrix;

out vec4 color;

void main(){
     gl_Position = trans_matrix * scale_matrix * vPosition;
     color = vColor;
}