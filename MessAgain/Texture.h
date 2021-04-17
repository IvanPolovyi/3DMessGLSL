#pragma once

#include <glm.hpp>
#include <glew.h>
#include <glfw3.h>
#include <string>
#include <iostream>
#include <SOIL2.h>

class Texture
{
private:
	GLuint id;
	int width;
	int height;
	unsigned int type;
	GLint textureUnit;

public:

	Texture(const char* fileName, GLenum type, GLint textureUnit)
	{
		this->type = type;
		this->textureUnit = textureUnit;
		
		loadFromFile(fileName);
	}
	~Texture()
	{
		glDeleteTextures(1, &this->id);
	}

	GLuint getID() const {return this->id;}
	void bind()
	{
		glActiveTexture(GL_TEXTURE0 + this->textureUnit);
		glBindTexture(this->type, this->id);
	}
	void unbind()
	{
		glActiveTexture(0);
		glBindTexture(this->type, 0);
	}
	GLint getTextureUnit() { return this->textureUnit; }

	void loadFromFile(const char* fileName)
	{
		if(this->id)
		{
			glDeleteTextures(1, &this->id);
		}
		
		unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

		glGenTextures(1, &this->id);
		glBindTexture(this->type, this->id);
		glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		if (image)
		{
			glTexImage2D(this->type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(this->type);
		}
		else
		{
			std::cout << "ERROR::TEXTURE::LOAD_FROM_FILE::TEXTURE_LOAD_FAILED_FILE: " << fileName << "\n";
		}

		glActiveTexture(0);
		glBindTexture(this->type, 0);
		SOIL_free_image_data(image);
	}
};
