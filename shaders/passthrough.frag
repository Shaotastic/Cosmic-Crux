#version 420

out vec4 outColor;
in vec3 normals;

void main()
{
	outColor = vec4(normals, 1.0f);
}