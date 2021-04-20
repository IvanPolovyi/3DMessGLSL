#pragma once

#include "Mesh.h"

class Model
{
private:
	Material* material;
	Texture* overrideTextureDiffuse;
	Texture* overrideTextureSpecular;

	std::vector<Mesh*> meshes;
	glm::vec3 position;
public:
	Model(glm::vec3 position, Material* material, Texture* overrideTexDif, Texture* overrideTexSpec, std::vector<Mesh*> meshes)
	{
		this->position = position;
		this->material = material;
		this->overrideTextureDiffuse = overrideTexDif;
		this->overrideTextureSpecular = overrideTexSpec;

		for (auto*i : meshes)
		{
			this->meshes.push_back(new Mesh(*i));
		}
	}
	~Model()
	{
		for (auto*& i : this->meshes)
		{
			delete i;
		}
	};
	void update()
	{
		
	}
	void render(Shader* shader)
	{

		this->material->sendToShader(*shader);

		shader->use();

		this->overrideTextureDiffuse->bind(0);
		this->overrideTextureSpecular->bind(1);

		for(auto&i:this->meshes)
		{
			i->render(shader);
		}
		
		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};