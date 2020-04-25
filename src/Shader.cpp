#include "Shader.h"

Shader::Shader()
{
    //ctor
}

Shader::~Shader()
{
    //dtor
}
void Shader::loadFile(char* FileName, string& str)
{
    char tmp[1024];

    ifstream in(FileName);

    if(!in.is_open()) {

        cout<<"File cannot be open"<<endl;
        return;
    }

    while(!in.eof()){

        in.getline(tmp,1024);
        str +=tmp;
        str +='\n';
    }
    cout<< str<<endl;
}

unsigned int Shader::LoadShader(string& source, unsigned int mode)
{
    unsigned int id;
      const char*  csource;
      char error[1024];

     id = glCreateShader(mode);
      csource = source.c_str();

       glShaderSource(id,1,&csource, NULL);
       glCompileShader(id);

       glGetShaderInfoLog(id,1024,NULL, error);

       cout<<"Compile Statu \n"<< error<<endl;

      return id;
}

void Shader::initShader(char* VfileName, char* FfileName)
{
    string source;

     //loadFile(VfileName,source);
     //vs = LoadShader(source,GL_VERTEX_SHADER);

     source ="";

    loadFile(FfileName,source);
     fs = LoadShader(source,GL_FRAGMENT_SHADER);
     program =glCreateProgram();

     glAttachShader(program,vs);
     glAttachShader(program,fs);

     glLinkProgram(program);
     //glUseProgram(program);
}

void Shader::cleanUp()
{
    glDetachShader(program,vs);
  glDetachShader(program,fs);
  glDeleteShader(vs);
  glDeleteShader(fs);
  glDeleteProgram(program);
}
