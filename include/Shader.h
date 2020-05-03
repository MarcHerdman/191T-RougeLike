#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#define GL_GLEXT_PROTOTYPES

#include <stdlib.h>
#include <GL/glew.h>

#include <iostream>
#include <math.h>

#include <fstream>

using namespace std;


class Shader
{
    public:
        Shader();
        virtual ~Shader();

        void loadFile(char *,string&);
        unsigned vs, fs, program;
        unsigned int LoadShader(string&, unsigned int);
        void initShader(char *, char *,unsigned&);
        void cleanUp();

    protected:

    private:
};

#endif // SHADER_H
