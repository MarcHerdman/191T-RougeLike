#include "Square.h"

Square::Square()
{
    //ctor
    //shader = new Shader();
    tex = new Texture();
}

Square::~Square()
{
    //dtor
}
void Square::DrawSquare(float x,float y,float scalex,float scaley)
{
    //glUseProgram(shader->program);
    //GLuint loc = glGetUniformLocation(shader->program,"iTime");

    //if(loc != -1) {
        //glUniform1f(loc, 1);
    //}
    tex->TextureBinder();
    glPushMatrix();
   // glBegin(GL_QUADS);
    //glTexCoord2f(1,1);
    //glVertex3f(-1, -1, 0.0);
    //glTexCoord2f(1,0);
    //glVertex3f(1, -1, 0.0);
    //glTexCoord2f(0,1);
    //glVertex3f(1, 1, 0.0);
    //glTexCoord2f(0,0);
    //glVertex3f(-1, 1, 0.0);
    //glEnd();
    tex->Draw(x,y,scalex,scaley);
    glPopMatrix();
    //glUseProgram(0);

}

void Square::Init(char *fileName)
{
    tex->CreateTexture(fileName,1,1);
    //shader->initShader("vert.vs","frag.fs",shader->program);

}
