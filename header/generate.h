#ifndef GENERATE_H
#define GENERATE_H

#ifndef GRAPHIC_H
#include <graphic.h>
#endif

#define ERROR 0
#define FAILED -1
#define SUCCESS 0
#define GEN_VAO 0x01
#define GEN_VBO 0x02
#define GEN_EBO 0x03

const char* load_shader_source(char* filename);
unsigned int CreateShader(unsigned int type, const char* source);
unsigned int LinkShaders(unsigned int vShader, unsigned int fShader);
unsigned int generateTexture(const char* path, unsigned int type);
int generateBuffers(unsigned int bufferType);


#endif