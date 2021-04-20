#pragma once

#include "libs.h"

enum ShaderEnum
{
	SHADER_CORE_PROGRAM = 0
};
enum TextureEnum
{
	TEX_PUSHEEN,
	TEX_PUSHEEN_SPECULAR,
	TEX_CONTAINER,
	TEX_CONTAINER_SPECULAR
};
enum MaterialEnum
{
	MAT_1 = 0
};
enum MeshEnum
{
	MESH_QUAD = 0
};

class Game
{
private:
	GLFWwindow* window;
	char* title;
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	int framebufferWidth = WIDTH;
	int framebufferHeight = HEIGHT;

	float dt;
	float curTime;
	float lastTime;

	//mouse
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;
	
	//Matrices
	glm::mat4 viewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::vec3 worldUp;

	glm::vec3 cameraPosition;
	glm::vec3 cameraFront;
	float fov;
	float nearPlane;
	float farPlane;

	Camera camera;
	
	//Shaders
	std::vector<Shader*> shaders;
	
	//Textures
	std::vector<Texture*> textures;

	//Meshes
	std::vector<Mesh*> meshes;

	//Materials
	std::vector<Material*> materials;

	//lights
	std::vector<glm::vec3*> lights;

	std::vector<Model*> models;
	
	void initGLFW();
	void initWindow();
	void iniGLEW();
	void initOpenGLOptions();
	void initMatrices();

	void initShaders();
	void initTextures();
	void initMaterials();
	void initMeshes();
	void initLights();
	void initModels();
	
	void initUniforms();

	void updateUniforms();
public:
	Game(char* title);
	virtual ~Game();
	void setWindowShouldClose();
	int getWindowShouldClose();
	void update();
	void render();
	void updateKeyboardInput();
	void updateMouseInput();
	void updateInput();
	void updateDt();
};

