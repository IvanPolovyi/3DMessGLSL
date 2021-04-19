#pragma once

#include <iostream>
#include <vector>
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
private:
	glm::vec3 worldUp;
	glm::mat4 viewMatrix;

	GLfloat moveSpeed;
	GLfloat sensitivity;
	
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;
	
	void updateCameraVectors()
	{
		this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		this->front.y = sin(glm::radians(this->pitch));
		this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

		this->front = glm::normalize((this->front));
		this->right = glm::normalize(glm::cross(this->front, this->worldUp));
		this->up = glm::normalize(glm::cross(this->right, this->front));

	}

public:
	Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp)
	{
		this->viewMatrix = glm::mat4(1.f);
		this->moveSpeed = 1.f;
		this->sensitivity = 10.f;
		
		this->worldUp = worldUp;
		this->position = position;
		this->right = glm::vec3(0.f);
		this->up = worldUp;
		 
		this->pitch = 0.f;
		this->yaw = -90.f;
		this->roll = 0.f;
		
		this->updateCameraVectors();
	}
	~Camera(){}

	const glm::mat4 getViewMatrix()
	{
		this->updateCameraVectors();
		this->viewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);

		return this->viewMatrix;
	}
	const glm::vec3 getPosition()
	{
		return this->position;
	}
	void updateInput(const float& dt, const int direction, const double& offsetX, const double offsetY)
	{
		this->updateMouseInput(dt, offsetX, offsetY);
		//this->updateKeyboardInput(dt, direction);
	}
	void updateMouseInput(const float& dt, const double& offsetX, const double offsetY)
	{
		this->pitch += static_cast<GLfloat>(offsetY) * this->sensitivity * dt;
		this->yaw += static_cast<GLfloat>(offsetX) * this->sensitivity * dt;

		if(this->pitch >= 80.f)
			this->pitch = 80.f;
		else if(this->pitch <= -80)
			this->pitch = -80.f;
		
		if (this->yaw > 360.f || this->yaw < -360.f)
			this->yaw = 0.f;
		
		
	}
	void move(const float& dt, const int direction)
	{
		switch (direction)
		{
			case FORWARD: 
				this->position += this->front * moveSpeed * dt;
				break;
			case BACKWARD: 
				this->position -= this->front * moveSpeed * dt;
				break;
			case LEFT: 
				this->position -= this->right * moveSpeed * dt;
				break;	
			case RIGHT: 
				this->position += this->right * moveSpeed * dt;
				break;
			default: break;
		}
	}

	enum Directions { FORWARD = 0, BACKWARD = 1, LEFT = 2, RIGHT = 3 };


	
};