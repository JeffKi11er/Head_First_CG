#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
std::string loadShaderSrc(const char* filename);//load the shader source 

int main() {
	std::cout << "Hello Worlds" << std::endl;

	//glm test 
	
	//glm::vec4 vec(1.0f, 1.0f, 1.0f, 1.0f);//4d vector
	//glm::mat4 trans = glm::mat4(1.0f);//identity the matrix 
	//we can put out transformation knowledge to good use by translating a vector of (1,0,0) by (1,1,0) (note that
	//we can define it as glm::vec4 with its homogenous coordinate set to 1.0)
	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));//translation

	//we scale the container by 0.5 on each axis and then rotate the container 90 degrees around the z-axis 
	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));//rotaion
	//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));//scaling
	//vec = trans * vec;
	//std::cout << vec.x << ' ' << vec.y << ' ' << vec.z << std::endl;

	int success;
	char infoLog[512];

	glfwInit();
	//openGL Version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#endif // __APPLE__

	GLFWwindow* window = glfwCreateWindow(800, 600, "Heart First CG", NULL, NULL);//weight, height, title, monitor
	if (window == NULL) { //window not created
		std::cout << "Could not create a window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/*
		shaders
	*/
	//compile the vertex shader 
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertShaderSrc = loadShaderSrc("assets/vertex_core.glsl");
	const GLchar* vertShader = vertShaderSrc.c_str();
	glShaderSource(vertexShader, 1, &vertShader, NULL);
	glCompileShader(vertexShader);

	//catch error
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error with vertex shader comp.:"<< std::endl << infoLog << std::endl;
	}

	//compile fragment shader 
	unsigned int fragmentShader[2];
	fragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragShaderSrc = loadShaderSrc("assets/fragment_core.glsl");
	const GLchar* fragShader = fragShaderSrc.c_str();
	glShaderSource(fragmentShader[0], 1, &fragShader, NULL);
	glCompileShader(fragmentShader[0]);

	//catch error
	glGetShaderiv(fragmentShader[0], GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader[0], 512, NULL, infoLog);
		std::cout << "Error with frag shader comp.:" << std::endl << infoLog << std::endl;
	}

	fragmentShader[1] = glCreateShader(GL_FRAGMENT_SHADER);
	fragShaderSrc = loadShaderSrc("assets/fragment_core2.glsl");
	fragShader = fragShaderSrc.c_str();
	glShaderSource(fragmentShader[1], 1, &fragShader, NULL);
	glCompileShader(fragmentShader[1]);

	//catch error
	glGetShaderiv(fragmentShader[1], GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader[1], 512, NULL, infoLog);
		std::cout << "Error with frag shader comp.:" << std::endl << infoLog << std::endl;
	}

	//create linked program
	unsigned int shaderProgram[2];
	shaderProgram[0] = glCreateProgram();
	glAttachShader(shaderProgram[0], vertexShader);
	glAttachShader(shaderProgram[0], fragmentShader[0]);
	glLinkProgram(shaderProgram[0]);

	//catch errors 
	glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram[0], 512, NULL, infoLog);
		std::cout << "Linking error: " << std::endl << infoLog << std::endl;
	}
	shaderProgram[1] = glCreateProgram();
	glAttachShader(shaderProgram[1], vertexShader);
	glAttachShader(shaderProgram[1], fragmentShader[1]);
	glLinkProgram(shaderProgram[1]);

	//catch errors 
	glGetProgramiv(shaderProgram[1], GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram[1], 512, NULL, infoLog);
		std::cout << "Linking error: " << std::endl << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader[0]);
	glDeleteShader(fragmentShader[1]);

	//vertex array
	float vertices[] = {

		//triangle
		/*-0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f*/

		//rectangle											//color
		
		-0.25f, -0.5f, 0.0f,								1.0f, 1.0f, 0.5f, //top right					
		0.15f, 0.0f, 0.0f,									0.5f, 1.0f, 0.75f,//top left
		0.0f, 0.5f, 0.0f,									0.6f, 1.0f, 0.2f,//bottom left
		0.5f, -0.4f, 0.0f,									1.0f, 0.2f, 1.0f//bottom right 
	};
	unsigned int indices[] = {
		0, 1, 2,
		3, 1, 2
	};
	//VAO, VBO
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//bind VAO
	glBindVertexArray(VAO);

	//bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//set up EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//set attribute pointer

	//positions 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//index = 0, size = 3, type = GL_FLOAT
	//glFloat Nomarlize = false, strike  = (int)3*sizeof(float), last one is the advoid pointer
	glEnableVertexAttribArray(0);

	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window)) {
		//process input 
		processInput(window);

		//render
		glClearColor(0.2f, 0.3f, 0.3f, 1.1f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw shapes 
		glBindVertexArray(VAO);//which vertex array object that it looks at or vertex buffer data to
		//look at 
		//first triangle
		glUseProgram(shaderProgram[0]);//use the shader 
		//glDrawArrays(GL_TRIANGLES, 0, 3);//first is zero and count to 3 (index to draw and number of
		//vertex to draw)

		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		//second triangle 
		//glUseProgram(shaderProgram[1]);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3*sizeof(unsigned int)));

		//send the new frame to window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

std::string loadShaderSrc(const char* filename) {
	std::ifstream file; //create file object standard 
	std::stringstream buf;//this will be the buffer to read the data 
	std::string ret = "";//just be our placeholder for the return variable
	file.open(filename);

	if (file.is_open()) {
		buf << file.rdbuf();//read the buffer and essencially piping it to the string buffer 
		ret = buf.str();
	}
	else {
		std::cout << "Couldn't open " << filename << std::endl;
	}
	file.close();
	return ret;
}