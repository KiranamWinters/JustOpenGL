#include <generate.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int generateBuffers(unsigned int bufferType){

    if (bufferType == GEN_VAO){
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        return VAO;
    }
    if (bufferType == GEN_VBO){
        unsigned int VBO;
        glGenBuffers(1,&VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        return VBO;
    }
    if (bufferType == GEN_EBO){
        unsigned int EBO;
        glGenBuffers(1,&EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        return EBO;
    }
    return FAILED;
}

const char* load_shader_source(char* filename)
{
    FILE* file = fopen(filename, "r");             // open 
    fseek(file, 0L, SEEK_END);                     // find the end
    size_t size = ftell(file);                     // get the size in bytes
    char* shaderSource = calloc(1, size + 1);      // allocate enough bytes
    rewind(file);                                  // go back to file beginning
    fread(shaderSource, size, sizeof(char), file); 

    printf("Size of %s: %.3f MB\n", filename, (float)size/1024);   // read each char into 

    fclose(file);                                  // close the 
    return shaderSource;
}

//function which will return either -1 if err occurs and 0 if successfull
unsigned int CreateShader(unsigned int type, const char* source) {

    unsigned int Shader = glCreateShader(type);
    glShaderSource(Shader, 1, &source, NULL);
    glCompileShader(Shader);

    //error handling
    int success;
    char infoLog[512];
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(Shader, 512, NULL, infoLog);
        if (type == GL_VERTEX_SHADER)
            printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", infoLog);
        else if (type == GL_FRAGMENT_SHADER)
            printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s,", infoLog);
        return ERROR;
    }
    return Shader;
}

unsigned int LinkShaders(unsigned int vShader, unsigned int fShader) {
    //creating a shader program to link both shaders together
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);
    glLinkProgram(shaderProgram);

    //error handling for linking shaders
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", infoLog);
        return ERROR;
    }

    return shaderProgram;
}

unsigned int generateTexture(const char* path , unsigned int type) {

    unsigned int texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = (unsigned char*)stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("Failed to load texture");
        return ERROR;
    }
    stbi_image_free(data);
    return texture;
}



