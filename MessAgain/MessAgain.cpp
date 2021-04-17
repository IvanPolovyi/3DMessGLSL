#include "Game.h"


void updateInput(GLFWwindow* window, Mesh &mesh)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(-0.01f, 0.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.01f, 0.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.f, 0.01f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.f, -0.01f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.f, 0.f, 0.01f));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.f, 0.f, -0.01f));
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		mesh.rotate(glm::vec3(0.f, 0.5f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		mesh.rotate(glm::vec3(0.f, -0.5f, 0.f));
	}

}

GLFWwindow* createWindow(const char* title, const int width, const int height, int &fbWidth, int &fbHeight, const int glMajorVersion, const int glMinorVersion)
{

}

int main()
{
	glfwInit();

	const int glMajorVersion = 4;
	const int glMinorVersion = 5;

	Game game();
	
	
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) 
	{
		std::cout << "ERROR::MAIN.CPP::GLEW_INIT_FAILED" << "\n";
		glfwTerminate();
	}

	//OpenGL Options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	Quad tempQuad = Quad();
	Mesh mesh(&tempQuad);
	

	//Texture0
	Texture texture0("images/cat.png", GL_TEXTURE_2D, 0);
	Texture texture1("images/fish.png", GL_TEXTURE_2D,1);


	//Shaders

	Shader core_program((char*) "vertex_core.glsl", (char*) "fragment_core.glsl");

	
	//Material

	Material material0(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), texture0.getTextureUnit(), texture1.getTextureUnit());

	//GLuint core_program;
	//if (loadShaders(core_program) == false) 
	//{
	//	glfwTerminate();
	//}


	// camera thing

	glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f);
	glm::vec3 camFront = glm::vec3(0.f, 0.f, -1.f);
	glm::vec3 camPosition = glm::vec3(0.f, 0.f, 1.f);


	glm::mat4 ViewMatrix(1.f);
	ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp);

	float fov = 90.f;
	float nearPlane = 0.1f;
	float farPlane = 1000.f;
	glm::mat4 ProjectionMatrix(1.f);

	ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWidth) / framebufferHeight, nearPlane, farPlane);

	//lights
	
	glm::vec3 lightPos0(0.f, 0.f, 1.f);

	//uniformss
	//glUseProgram(core_program);

	core_program.setMat4fv(ViewMatrix, "ViewMatrix");
	core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	core_program.setVec3f(lightPos0, "lightPos0");
	core_program.setVec3f(camPosition, "cameraPos");


	while (glfwWindowShouldClose(window) == false)
	{
		
		glfwPollEvents();

		//update
		updateInput(window, mesh);
		//draw

		//clear
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);



		//update uniforms
		core_program.set1i(texture0.getTextureUnit(), "texture0");
		core_program.set1i(texture1.getTextureUnit(), "texture1");

		material0.sendToShader(core_program);
		


		//Use program
		core_program.use();

		//texture

		texture0.bind();
		texture1.bind();
		
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture0);
		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, texture1);

		//bind vertex array


		//draw
		//glDrawElements(GL_TRIANGLES, nrOfIndeces, GL_UNSIGNED_INT, 0);
		mesh.render(&core_program);

		//end draw
		glfwSwapBuffers(window);
		glFlush();

		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

