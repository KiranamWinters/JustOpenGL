#ifndef GLOBAL_H
#define GLOBAL_H

#include <graphic.h>

extern float fov;
extern bool firstMouseStroke;

extern float yaw;
extern float pitch;
extern float roll;

extern float lastX;
extern float lastY;

extern vec3 cameraFront;
extern vec3 cameraPos;
extern vec3 cameraUp;

extern float deltaTime;
extern float lastFrame;

//actual colour of the drawn shape
extern float o_red;
extern float o_green;
extern float o_blue;

//background colour

extern float b_red;
extern float b_green;
extern float b_blue;

//window size
extern int Wheight;
extern int Wwidth;


//make sure to include glad.c when working with glad library
//function gets called each time the user resizes the window
//shaders are small programs exceuted by small cores which exist in graphics cards

//vertices and indices
extern float vertices[];
extern unsigned int indices[];

//Cube Locations
extern vec3 cubePos[];

#define X 0
#define Y 1
#define Z 2
#define W 3


#endif