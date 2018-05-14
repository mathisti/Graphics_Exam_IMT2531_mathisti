
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "camera.hpp"
#include "model.hpp"
#include "planeModel.hpp"

void testLight(Shader& shader) {


	// Directional light
	shader.setBool("dirSet", true);
	shader.setVec3("dirLight.direction", glm::vec3(1.0f, -1.0f, -0.3f));
	shader.setVec3("dirLight.ambient", glm::vec3(0.1f, 0.05f, 0.05f));
	shader.setVec3("dirLight.diffuse", glm::vec3(0.2f, 0.2f, 0.2f));
	shader.setVec3("dirLight.specular", glm::vec3(0.2f, 0.2f, 0.2f));
}

// Input
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// camera
Camera camera(glm::vec3(0.0f, 10.0f, 30.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

Camera planeCam;

bool flying = false;
bool resetPlane = false;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool lightToggle = false;

int main() {

	if (!glfwInit())
	{
		// Initialization failed
		return -4;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "framework", glfwGetPrimaryMonitor(), nullptr); // glfwGetPrimaryMonitor()
	if (!window)
	{
		// Window or OpenGL context creation failed
		return -3;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	// bind glfw events to custom functions
	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	glewExperimental = GL_FALSE;
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error: " << error << std::endl;
	}

	if (glewInit() != GLEW_OK) {
		return -2;
		glfwTerminate();
	}
	


	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glfwSwapInterval(1);

	Model world("assets/models/heightmap/height100.obj");
	planeModel plane_model("assets/models/model/ask21mi.obj");
	plane_model.translate(glm::vec3(0, 0, 0));
	plane_model.moveSpeed = -5.0f;
	
	Shader shader("shaders/testvertex.vert", "shaders/testfragment.frag");
	
	float lastFrame = 0;

	world.scale(500.0f);
	plane_model.scale(0.5f);
	

	float lightX = 0;
	
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// view/projection transformations		
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);

		// render
		// ------
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
	
			// Directional light, going in the direction of the cameras front
		testLight(shader);
		shader.setBool("dirSet", true);
		shader.setVec3("dirLight.direction", camera.Front);
		shader.setVec3("dirLight.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
		shader.setVec3("dirLight.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		shader.setVec3("dirLight.specular", glm::vec3(0.6f, 0.6f, 0.6f));

		std::cout << "\n" << plane_model.moveSpeed;

		// Which camera to use (follow the plane or free roam where flying is following the plane)
		if (!flying) {
			glm::mat4 view = camera.GetViewMatrix();
			shader.setMat4("projection", projection);
			shader.setMat4("view", view);
		} else {
			glm::mat4 view = camera.GetPlaneViewMatrix(plane_model.currentPosition(), plane_model.model_Front);
			shader.setMat4("projection", projection);
			shader.setMat4("view", view);
		}

		// The constant movement og the plane in the direction it's facing
		plane_model.translate(glm::vec3(plane_model.moveSpeed * deltaTime, 0, 0));

		shader.setMat4("model", world.getTransform());
		world.Draw(shader);
		shader.setMat4("model", plane_model.getTransform());
		plane_model.Draw(shader);


		// Input that does something with the plane
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			plane_model.update(throttleUPWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			plane_model.update(throttleDOWNWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			plane_model.update(throttleLEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			plane_model.update(throttleRIGHT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS)
			plane_model.moveSpeed -= 1.0f;
		if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS)
			plane_model.moveSpeed += 1.0f;
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
			plane_model.setRandomPos();
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
			plane_model.resetPos();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

}

void error_callback(int error, const char* description)
{
	std::cout << "Error " << error << ": " << description;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Input for the camera.
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		camera.ProcessKeyboard(UPWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWNWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SLASH) == GLFW_PRESS)
		flying = !flying;
}



// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset*deltaTime, yoffset*deltaTime);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}