#include "model.h"
#include "SceneWriter.h"

static glm::vec3 eyeLine;
static bool firstMouse;
static float yaw;
static float pitch;
static float lastX;
static float lastY;
static float fov;

model::model()
{
	eyeLine = glm::vec3(0.0f, 0.0f, -1.0f);
	firstMouse = true;
	yaw   = -90.0f;
	pitch = 0.0f;
	lastX = 800.0f / 2.0;
	lastY = 600.0 / 2.0;
	fov   = 45.0f;
}

void model::addMesh(mesh mesh) {
	meshes.push_back(mesh);
}

void model::addMTL(mtl mtl) {
	mtls.push_back(mtl);
}

void model::performMtlLightning(string mtlName, Shader* shader) {
	
	GLint ambientLight = glGetUniformLocation(shader->Program, "material.ambient");
	GLint diffuseLight = glGetUniformLocation(shader->Program, "material.diffuse");
	GLint specLight = glGetUniformLocation(shader->Program, "material.specular");
	GLint shininess = glGetUniformLocation(shader->Program, "material.shininess");

	GLfloat* Ka;
	GLfloat* Ks;
	GLfloat* Kd;
	GLfloat ns;
	GLfloat ka[3];
	GLfloat ks[3];
	GLfloat kd[3];

	for (int i = 0; i < mtls.size(); i++) {
		if (mtls[i].getName() == mtlName) {
			Ka = mtls[i].getKa();
			Ks = mtls[i].getKs();
			Kd = mtls[i].getKd();
			ns = mtls[i].getNs();
			ka[0] = Ka[0];
			ka[1] = Ka[1];
			ka[2] = Ka[2];
			kd[0] = Kd[0];
			kd[1] = Kd[1];
			kd[2] = Kd[2];
			ks[0] = Ks[0];
			ks[1] = Ks[1];
			ks[2] = Ks[2];
			break;
		}
	}

	glUniform3f(ambientLight, ka[0], ka[1], ka[2]);
	glUniform3f(diffuseLight, kd[0], kd[1], kd[2]);
	glUniform3f(specLight, ks[0], ks[1], ks[2]);
	glUniform1f(shininess, ns);

}

void model::draw(scene scene){ 

	GLFWwindow* window = init();

	Shader shader("../shaders/lighting.vs", "../shaders/lighting.frag");

	glEnable(GL_DEPTH_TEST);
	glm::mat4 model; //objects positions
	float lastFrame = 0.0f;
	
	glm::vec3 lightPos(scene.getPositions());

	upVector = glm::vec3(scene.getUpVector());
	whereToLook = glm::vec3(scene.getWhereToLook());
	deltaTime = 0.0f;	// time between current frame and last frame
	glm::vec3 objColors = glm::vec3(scene.getObjectColors());
	glm::vec3 lightColors = glm::vec3(scene.getColors());
	glm::vec4 proj = glm::vec4(scene.getProjection());
	glm::vec3 rotationVec = glm::vec3(scene.getRotation());
	glm::vec3 translationVec = glm::vec3(scene.getTranslation());
	glm::vec3 scaleVec = glm::vec3(scene.getScale());
	float angle = scene.getAngle();

	for (size_t i = 0; i < meshes.size(); i++) {
		meshes[i].bindMesh();
	}

	int* texture = new int[meshes.size()];
	
	for (size_t i = 0; i < meshes.size(); i++) {
		texture[i] = meshes[i].bindTexture(mtls, &shader);
	}

	while (!glfwWindowShouldClose(window)) {

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glm::mat4 projection; //opening, frame of view
		glm::mat4 view; //here is where the magic happens

		model = processInput(window, eyeLine);
		model = scale(model, scaleVec);
		model = glm::rotate(model, angle, rotationVec);
		model = glm::translate(model, translationVec);
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();

		GLint objectColorLoc = glGetUniformLocation(shader.Program, "objectColor");
		GLint lightColorLoc = glGetUniformLocation(shader.Program, "lightColor");
		GLint lightPosLoc = glGetUniformLocation(shader.Program, "lightPos");
		GLint viewPosLoc = glGetUniformLocation(shader.Program, "viewPos");
		
		glUniform3f(objectColorLoc, objColors.x, objColors.y, objColors.z);
		glUniform3f(lightColorLoc, lightColors.x, lightColors.y, lightColors.z); 
		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);

		projection = glm::perspective(proj.x, proj.y, proj.z, proj.w);
		view = glm::lookAt(whereToLook, whereToLook + eyeLine, upVector);

		GLint projLoc = glGetUniformLocation(shader.Program, "projection");
		GLint modelLoc = glGetUniformLocation(shader.Program, "model");
		GLint viewLoc = glGetUniformLocation(shader.Program, "view");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		for (size_t i = 0; i < meshes.size(); i++) {
			performMtlLightning(meshes[i].getMTLName(), &shader);
			meshes[i].draw(&shader, texture[i]);
		}

		glfwSwapBuffers(window);
	}
	
}

void model::terminate() {
	for (size_t i = 0; i < meshes.size(); i++) {
		meshes[i].terminate();
	}
}

glm::mat4 model::processInput(GLFWwindow* window, glm::vec3 eyeLine) {
	glm::mat4 model;
	SceneWriter test;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 3.5 * deltaTime;
	//camera transformations
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		whereToLook += cameraSpeed * eyeLine;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		whereToLook -= cameraSpeed * eyeLine;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		whereToLook -= glm::normalize(glm::cross(eyeLine, upVector)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		whereToLook += glm::normalize(glm::cross(eyeLine, upVector)) * cameraSpeed;

	//object transformations
	//Translate
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));

	//Rotate
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		model = glm::rotate(model, (GLfloat)glfwGetTime(), glm::vec3(0.0f, -1.0f, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		model = glm::rotate(model, (GLfloat)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		model = glm::rotate(model, (GLfloat)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));

	//Scale
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		//printf("aaaaaa");
		//glfwMakeContextCurrent(window);
		test.test();
	return model;
}

void model::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	eyeLine = glm::normalize(front);
}

void model::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}

GLFWwindow* model::init() {
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "My Title", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glewExperimental = GL_TRUE;
	glewInit();

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	
	return window;
}

model::~model()
{
}
