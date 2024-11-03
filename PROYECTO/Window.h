#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	bool getShouldClose() { return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }

	bool getreinicio() { return reinicio; };
	bool gettiro() { return tiro; }

	float getUltimoValorDado4() { return ultimoValorDado4; }
	float getUltimoValorDado8() { return ultimoValorDado8; }
	void setUltimoValorDado4(float valor) { ultimoValorDado4 = valor; }
	void setUltimoValorDado8(float valor) { ultimoValorDado8 = valor; }

	~Window();

private:
	GLFWwindow* mainWindow;
	GLint width, height;
	GLfloat traslacion;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;

	bool reinicio;
	bool tiro;

	float ultimoValorDado4;
	float ultimoValorDado8;

	void createCallbacks();
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);
};
