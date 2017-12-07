#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <stb\stb_image.h>
#include <assimp\camera.h>

#include <iostream>

#include "shader.h"
#include "camera.h"
#include "Model.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 768;

Camera camera(glm::vec3(0.0f, 3.0f, 10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
#pragma region init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Scene", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create glfw window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize glad" << std::endl;
		system("pause");
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
#pragma endregion

	Shader shaderProgram("vertex_shader.glsl", "fragment_shader.glsl");

	Model modelHouse("models/house/house.obj");
	Model modelBike("models/bike/bike.obj");
	Model modelBasketballStands("models/basketballStands/basketballStands.obj");
	Model modelLamp("models/lamp/lamp.obj");
	
	glm::vec3 lightPos(1.2f, 1.0f, 1.0f);


	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.use();

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		shaderProgram.setUniform("projection", projection);
		shaderProgram.setUniform("view", view);

		// render the loaded model
		glm::mat4 model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
		//shaderProgram.setUniform("model", model);

		shaderProgram.setUniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shaderProgram.setUniform("viewPos", camera.Position);

		shaderProgram.setUniform("pLight.position", glm::vec3(-2.5f, 2.5f, -2.5f));
		shaderProgram.setUniform("pLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		shaderProgram.setUniform("pLight.diffuse", glm::vec3(1.0f,1.0f, 1.0f));
		shaderProgram.setUniform("pLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shaderProgram.setUniform("pLight.constant", 1.0f);
		shaderProgram.setUniform("pLight.linear", 0.09f);
		shaderProgram.setUniform("pLight.quadratic", 0.032f);

		shaderProgram.setUniform("isSpecular", false);
		glm::mat4 modelTemp = model;
		shaderProgram.setUniform("model", modelTemp);
		modelHouse.draw(shaderProgram);

		modelTemp = glm::translate(model, glm::vec3(-12.0f, 0.0f, 7.0f));
		shaderProgram.setUniform("model", modelTemp);
		modelBasketballStands.draw(shaderProgram);

		modelTemp = glm::translate(model, glm::vec3(-5.0f, 0.0f, 14.0f));
		shaderProgram.setUniform("model", modelTemp);
		modelLamp.draw(shaderProgram);

		shaderProgram.setUniform("isSpecular", true);
		modelTemp = glm::translate(model, glm::vec3(3.0f, 0.0f, -1.0f));
		shaderProgram.setUniform("model", modelTemp);
		modelBike.draw(shaderProgram);
		/*	glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);*/

		/*model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));

		lightShaderProgram.use();
		lightShaderProgram.setUniform("projection", projection);
		lightShaderProgram.setUniform("view", view);
		lightShaderProgram.setUniform("model", model);
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);*/

		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	/*glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &lightVAO);*/
	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; 

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}