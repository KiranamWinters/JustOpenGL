#include <controls.h>


void moveForward(const float cam_speed, vec3 cam_front, vec3 cam_pos){
    glm_vec3_muladds(cam_front,cam_speed,cam_pos);
}

void moveBack(const float cam_speed, vec3 cam_front, vec3 cam_pos){
    vec3 temp;
    glm_vec3_scale(cam_front,cam_speed,temp);
    glm_vec3_sub(cam_pos, temp, cam_pos);
}

void moveLeft(const float cam_speed, vec3 cam_front, vec3 cam_up, vec3 cam_pos){
    vec3 temp;
    glm_vec3_crossn(cam_front,cam_up,temp);
    glm_vec3_scale(temp,cam_speed,temp);
    glm_vec3_sub(cam_pos, temp, cam_pos);
}

void moveRight(const float cam_speed, vec3 cam_front,vec3 cam_up, vec3 cam_pos){
    vec3 temp;
    glm_vec3_crossn(cam_front,cam_up,temp);
    glm_vec3_muladds(temp,cam_speed,cam_pos);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = deltaTime * 2.05f; // adjust accordingly

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        moveForward(cameraSpeed,cameraFront,cameraPos);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        moveBack(cameraSpeed,cameraFront,cameraPos);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
       // cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        moveLeft(cameraSpeed,cameraFront,cameraUp,cameraPos);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        //cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        moveRight(cameraSpeed,cameraFront,cameraUp,cameraPos);

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (firstMouseStroke)
    {
        lastX = xpos;  
        lastY = ypos;
        firstMouseStroke = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float mouseSensitivity = 0.1f;
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    vec3 direction;
    direction[X] = cos(glm_rad(yaw)) * cos(glm_rad(pitch));
    direction[Y] = sin(glm_rad(pitch));
    direction[Z] = sin(glm_rad(yaw)) * cos (glm_rad(pitch));
    glm_normalize(direction);
    glm_vec3_copy(direction,cameraFront);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
        
         
}