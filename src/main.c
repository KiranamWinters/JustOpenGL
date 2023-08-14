#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <graphic.h>
#include <generate.h>
#include <controls.h>
#include <global.h>


//make sure to include glad.c when working with glad library
//function gets called each time the user resizes the window
//shaders are small programs exceuted by small cores which exist in graphics cards

//vertices and indices
float vertices[] = {      //textures
    //x      y      z     t.x   t.y
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int indices[] = {  // note that we start from 0!
    0, 1, 2,   // first triangle
    0, 2, 3   // second triangle
};

//Cube Locations
vec3 cubePos[] = {
    { 0.0f,  0.0f,  0.0f}, 
    { 2.0f,  5.0f, -15.0}, 
    {-1.5f, -2.2f, -2.5f},  
    {-3.8f, -2.0f, -12.3},  
    { 2.4f, -0.4f, -3.5f},  
    {-1.7f,  3.0f, -7.5f},  
    { 1.3f, -2.0f, -2.5f},  
    { 1.5f,  2.0f, -2.5f}, 
    { 1.5f,  0.2f, -1.5f}, 
    {-1.3f,  1.0f, -1.5f},
    { 0.5f,  3.5f, -20.0f}  
    };


int main(int argc,char** argv)
{

    //initializes all the values to a deafault value
    //to set individual int value use glfWindowHint 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //creating a window and storing it in a pointer with error handling i think.
    GLFWwindow* window = glfwCreateWindow(Wheight, Wwidth, "JustOpenGL", NULL, NULL);

    if (window == NULL)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return FAILED;
    }

    //assigning handle to the window
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    //initializing GLAD which handles pointers for OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return FAILED;
    }

    glEnable(GL_DEPTH_TEST);

    //Loading shaders from file
    const char* fragmentShaderSource = load_shader_source("shaders/Fragment.glsl");
    const char* vertexShaderSource = load_shader_source("shaders/Vertex.glsl");
    const char* lighting_vs_source = load_shader_source("shaders/Lighting_vs.glsl");
    const char* lighting_fs_source = load_shader_source("shaders/Lighting_fs.glsl");

    //Creates and compiles shader
    unsigned int vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    unsigned int lighting_vs = CreateShader(GL_VERTEX_ARRAY, lighting_vs_source);
    unsigned int lighting_fs = CreateShader(GL_FRAGMENT_SHADER, lighting_fs_source);

    //creating a shader program to link both shaders together
    unsigned int shaderProgram = LinkShaders(vertexShader, fragmentShader);
    unsigned int lightingProgram = LinkShaders(lighting_vs, lighting_fs);

    //deleting the shaders cause now they are linked and we don't need them anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    free((void*)vertexShaderSource);
    free((void*)fragmentShaderSource);

    
    //making vertex buffer | vertex attribute object | element buffer object 
    unsigned int VAO = generateBuffers(GEN_VAO);
    unsigned int VBO = generateBuffers(GEN_VBO);
    unsigned int EBO = generateBuffers(GEN_EBO);

    //copying data from vertex memory to buffer's memory
    //vertex_memory -> buffer_memory

    //OPENGL USE INSTRUCTIONS
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



    //telling opengl how to render

    //Triangle coordinate
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //Texture coordinate
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int lightVAO = generateBuffers(GEN_VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    

    unsigned int texture1 = generateTexture("assets/MyImage.JPG", GL_RGB);
    unsigned int texture2 = generateTexture("assets/awesomeface.png", GL_RGBA);

    glUseProgram(shaderProgram);
    

    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);
    glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"),1.0f,0.5f,0.31f);
    glUniform3f(glGetUniformLocation(shaderProgram, "lightColor"),1.0f,1.0f,1.0f);

    
    mat4 model;
    mat4 view;
    vec3 center;

    vec3 axis = {1.0f,0.3f,0.5f};
    vec3 pos = {0.9f, 0.0f, 0.3f};

    //Pitch = camera rotation in X-Z plane
    //Yaw = camera rotation in X-Y plane
    //Roll = camera rotation in Y-Z plane
    float yaw = -90.0f;
     glEnable(GL_DEPTH_TEST);

    //Input, Rendering and openining/closing in while loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);
        glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
        
        // RENDERING COMMANDS HERE
        //--------------------------------------------------------------------------------------

        //Color refresh/background color
        glClearColor(b_red, b_green, b_blue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Time
        float time = (float)glfwGetTime();
        float currentFrame = time;
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //Texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        //camera
        glm_vec3_add(cameraPos,cameraFront,center);
        glm_lookat(cameraPos,center,cameraUp,view);



        mat4 projection;
        glm_mat4_identity(projection);
        glm_perspective(glm_rad(fov),(float)Wheight/(float)Wwidth,0.1f,100.0f,projection);
        int projectionLocation = glGetUniformLocation(shaderProgram,"projection");
        glUniformMatrix4fv(projectionLocation,1,GL_FALSE,&projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(lightingProgram,"model"),1,GL_FALSE,&projection[0][0]);

        //Uniform Location in Shaders
        int timeLocation = glGetUniformLocation(shaderProgram, "u_time");

        //Defining Uniform Values
        glUniform1f(timeLocation, time);
        
        // glm_mat4_identity(view);
        // const float radius = 10.0f;
        // float camX = (float)(sin(glfwGetTime())*radius);
        // float camZ = (float)(cos(glfwGetTime())* radius);
        // vec3 eye = {camX,0.0,camZ};
        // vec3 center = {0.0,0.0,0.0};
        // vec3 up1 = {0.0,1.0,0.0}; vec3 axis = {1.0f,0.3f,0.5f};
        // glm_lookat(eye,center,up1,view);

        int viewLocation = glGetUniformLocation(shaderProgram,"view");
        glUniformMatrix4fv(viewLocation,1,GL_FALSE,&view[0][0]);

        glUniformMatrix4fv(glGetUniformLocation(lightingProgram,"view"),1,GL_FALSE,&view[0][0]);

        //Drawing
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glm_mat4_identity(model);
        glm_translate(model, axis);
        glm_rotate(model, time * glm_rad(time), axis);
        glDrawArrays(GL_TRIANGLES,0,36);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"model"),1,GL_FALSE,&model[0][0]);
        
        //glUseProgram(lightingProgram);
        //glm_translate(model, axis);
        //glm_rotate(model, time * glm_rad(deltaTime), pos);
        //glDrawArrays(GL_TRIANGLES,0,36);

        glUniformMatrix4fv(glGetUniformLocation(lightingProgram,"model"),1,GL_FALSE,&model[0][0]);
        for (unsigned int i = 0; i < 11; i++){

            glm_mat4_identity(model);
            glm_translate(model, cubePos[i]);
            float angle = 20.0f * i;
           
            glm_rotate(model, time * glm_rad(angle), axis);
                
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"model"),1,GL_FALSE,&model[0][0]);

            glDrawArrays(GL_TRIANGLES,0,36);
        }
        
        //-----------------------------------------------------------------------------------------

        // Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Deleting memory once it has fullfilled its purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();

    return SUCCESS;
}

//This is called whenever user is resizing the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
