#include "Stencil.h"

Stencil::Stencil()
{
    tex = new Texture();
}

Stencil::~Stencil()
{
    //dtor
}
void Stencil::drawMask()
{

    glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );
    //Start using the stencil
    glEnable( GL_STENCIL_TEST );

    //Place a 1 where rendered
    glStencilFunc( GL_ALWAYS, 1, 1 );

    //Replace where rendered
    glStencilOp( GL_REPLACE, GL_REPLACE, GL_REPLACE );

		glPushMatrix();

    tex->Draw(0,0,1.75,1.75);


    glPopMatrix();
    glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
    glStencilFunc( GL_EQUAL, 1, 1 );
    glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
    glLoadIdentity();

}
void Stencil::disableBuffer()
{
    glDisable( GL_STENCIL_TEST );


}
