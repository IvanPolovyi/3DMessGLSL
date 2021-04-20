#include "Game.h"

void Game::initWindow()
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	this->window = glfwCreateWindow(WIDTH, HEIGHT, title, NULL, NULL);

	if(this->window == nullptr)
	{
		std::cout << "ERROR::GAME::INIT_WINDOW::WINDOW_IS_NULL" << "\n";
		glfwTerminate();
	}
	
	glfwGetFramebufferSize(this->window, &framebufferWidth, &framebufferHeight);
	glViewport(0, 0, framebufferWidth, framebufferHeight);
	glfwMakeContextCurrent(this->window);
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // puts cursor inside window

}

Game::Game(char* title) : camera(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f))
{
	this->window = nullptr;
	this->title = title;
	
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);
	this->cameraFront = glm::vec3(0.f, 0.f, -1.f);
	this->cameraPosition = glm::vec3(0.f, 0.f, 1.f);

	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 1000.f;
	this->ProjectionMatrix = glm::mat4(1.f);

	
	this->initGLFW();
	this->initWindow();
	this->iniGLEW();
	this->initMatrices();
	this->initShaders();
	this->initTextures();
	this->initMaterials();
	this->initMeshes();
	this->initModels();
	this->initLights();

	this->initUniforms();
}
Game::~Game()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();
	
	for (int i = 0; i < this->shaders.size(); ++i)
		delete this->shaders[i];
	for (int i = 0; i < this->textures.size(); ++i)
		delete this->textures[i];
	for (int i = 0; i < this->materials.size(); ++i)
		delete this->materials[i];
	for (int i = 0; i < this->meshes.size(); ++i)
		delete this->meshes[i];
	for (int i = 0; i < this->lights.size(); ++i)
		delete this->lights[i];
}

void Game::setWindowShouldClose()
{
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

int Game::getWindowShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Game::initGLFW()
{
	if(glfwInit() == GLFW_FALSE)
	{
		std::cout << "ERROR::GAME::INIT_GLFW::INIT_FAILED" << "\n";
		glfwTerminate();
	}
}
void Game::iniGLEW()
{
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR::GAME::INIT_GLEW::GLEW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
}

void Game::initOpenGLOptions()
{
    // OPENGL OPTIONS
    glEnable(GL_DEPTH_TEST); // allows us to use z coordinate, zoom away, etc

    glEnable(GL_CULL_FACE); // able to remove unecessary content
    glCullFace(GL_BACK); // remove back of triangle or whatever
    glFrontFace(GL_CCW); // front face is vertices that are going counter clockwise

    glEnable(GL_BLEND); // allow blending of colors
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // ??????? 
	glDepthFunc(GL_LEQUAL);
    glPolygonMode(GL_FRONT, GL_FILL);

    // Input
}
void Game::initMatrices()
{
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);
	this->cameraFront = glm::vec3(0.f, 0.f, -1.f);
	this->cameraPosition = glm::vec3(0.f, 0.f, 1.f);


	this->viewMatrix = glm::mat4(1.f);
	this->viewMatrix = glm::lookAt(this->cameraPosition, this->cameraPosition + this->cameraFront, this->worldUp);

	ProjectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->framebufferWidth) / this->framebufferHeight, this->nearPlane, this->farPlane);


}
void Game::initShaders()
{

	this->shaders.push_back(new Shader((char*)"vertex_core.glsl", (char*)"fragment_core.glsl"));

}
void Game::initTextures()
{
	this->textures.push_back(new Texture ("images/pusheen.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("images/pusheen_specular.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture ("images/container.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture ("images/container_specular.png", GL_TEXTURE_2D));
	
}

void Game::initMaterials()
{
	this->materials.push_back (new Material(
			glm::vec3(0.1f), 
			glm::vec3(1.f), 
			glm::vec3(1.f), 
			0, 
			1));
}

void Game::initMeshes()
{
	Pyramid tempQuad;
	tempQuad = Pyramid();

	this->meshes.push_back(new Mesh(&tempQuad));
}

void Game::initLights()
{
	this->lights.push_back(new glm::vec3(2.f, 2.f, 2.f));

}

void Game::initModels()
{
	this->models.push_back(new Model(glm::vec3(0.f), this->materials[MAT_1], this->textures[TEX_CONTAINER], this->textures[TEX_CONTAINER_SPECULAR], this->meshes));
}

void Game::initUniforms()
{
	
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(viewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");


	
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
	
}

void Game::updateUniforms()
{
	this->viewMatrix = this->camera.getViewMatrix();
	 
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->viewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "cameraPos");
}

void Game::update()
{
	this->updateDt();
	this->updateInput();

}
void Game::render()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	this->updateUniforms();

	//this->materials[MAT_1]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);
	//
	//this->shaders[SHADER_CORE_PROGRAM]->use();
	//
	//this->textures[TEX_CONTAINER]->bind(0);
	//this->textures[TEX_CONTAINER_SPECULAR]->bind(1);

	//this->meshes[MESH_QUAD]->render(this->shaders[SHADER_CORE_PROGRAM]);


	this->models[0]->render(this->shaders[SHADER_CORE_PROGRAM]);
	
	//end draw
	glfwSwapBuffers(window);
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);

}
void Game::updateKeyboardInput()
{
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		setWindowShouldClose();
	}
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		this->camera.move(this->dt, Camera::FORWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->camera.move(this->dt, Camera::BACKWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->camera.move(this->dt, Camera::LEFT);
	}
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->camera.move(this->dt, Camera::RIGHT);
	}
	
}

void Game::updateMouseInput()
{
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

	if (this->firstMouse)
	{
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
	}

	this->mouseOffsetX = this->mouseX - this->lastMouseX;
	this->mouseOffsetY = this->lastMouseY - this->mouseY; // y is inverted

	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;
}
void Game::updateInput()
{
	glfwPollEvents();
	this->updateKeyboardInput();
	this->updateMouseInput();
	this->camera.updateInput(dt, -1, this->mouseOffsetX, this->mouseOffsetY);
}

void Game::updateDt()
{
	this->curTime = static_cast<float>(glfwGetTime());
	this->dt = this->curTime - this->lastTime;
	this->lastTime = curTime;
}



