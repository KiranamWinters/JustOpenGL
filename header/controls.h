#ifndef CONTROLS_H
#define CONTROLS_H

#include <graphic.h>
#include <global.h>

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

#endif