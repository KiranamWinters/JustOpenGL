#include <global.h>
float fov = 45.0f;
float lastX = 400.0f;
float lastY = 400.0f;

float yaw = -90.0f;
float pitch = 0.0f;

bool firstMouseStroke = true;

vec3 cameraPos = {0.0f,0.0f,3.0f};
vec3 cameraUp = {0.0f,1.0f,0.0f};
vec3 cameraFront = {0.0,0.0,-1.0f};

float deltaTime = 0.0f;
float lastFrame = 0.0f;


//actual colour of the drawn shape
float to_red = 0;
float o_green = 0;
float o_blue = 0;

//background colour

float b_red = 0.2f;
float b_green = 0.2f;
float b_blue = 0.2f;

//window size
int Wheight =  800;
int Wwidth = 600;


//make sure to include glad.c when working with glad library
//function gets called each time the user resizes the window
//shaders are small programs exceuted by small cores which exist in graphics cards

//vertices and indices
