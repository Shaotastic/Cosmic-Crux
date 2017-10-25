#include <iostream>
#include "GameObject.h"

//GameObject::GameObject()
//{
//	location = glm::vec2(0.0f, 0.0f);
//}

//Location default is (0, 0), radius default is 0.15
GameObject::GameObject(glm::vec2 loc, float rad) :  radius(rad)
{
	move(loc.x, loc.y);
}

GameObject::~GameObject() 
{

}

//Change the object's location and the object mesh location
void GameObject::move(float x, float y)
{
	location.x += x;
	location.y += y;

	translate = glm::translate(translate, glm::vec3(x, y, 0.0f));
	transform = glm::translate(translate, glm::vec3(0.0f, 0.0f, 0.0f)) * rotate * scale;
}

//Check if two objects are intersecting, just using collisions spheres for now
bool GameObject::collide(GameObject other)
{
	glm::vec2 temp = glm::vec2(location.x - other.location.x, location.y - other.location.y);
	float mag = sqrt((temp.x * temp.x) + (temp.y * temp.y));

	if (mag < (radius + other.radius))
	{
		return true;
	}

	return false;
}

void GameObject::draw(ShaderProgram *shader, glm::mat4 cameraTransform, glm::mat4 cameraProjection)
{
	shader->sendUniformMat4("uModel", glm::value_ptr(transform), false);
	shader->sendUniformMat4("uView", glm::value_ptr(cameraTransform), false);
	shader->sendUniformMat4("uProj", glm::value_ptr(cameraProjection), false);
		  
	shader->sendUniform("uTex", 0);

	shader->sendUniform("lightPos", cameraTransform * glm::vec4(4.0f, 0.0f, 0.0f, 1.0f));
	shader->sendUniform("objectColor", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	shader->sendUniform("lightAmbient", glm::vec3(0.5f, 0.5f, 0.5f));
	shader->sendUniform("lightDiffuse", glm::vec3(5.0f, 5.0f, 5.0f));
	shader->sendUniform("lightSpecular", glm::vec3(5.0f, 5.0f, 5.0f));

	shader->sendUniform("lightSpecularExponent", 50.0f);
	shader->sendUniform("attenuationConstant", 1.0f);
	shader->sendUniform("attenuationLinear", 0.1f);
	shader->sendUniform("attenuationQuadratic", 0.1f);

	tex.bind();
	glBindVertexArray(mesh.vao);
	glDrawArrays(GL_TRIANGLES, 0, mesh.getNumVertices());
	glBindVertexArray(GL_NONE);
	tex.unbind();
}

void GameObject::loadTexture(const std::string & texFile)
{
	if (!tex.load(texFile))
	{
		system("pause");
		exit(0);
	}
}


