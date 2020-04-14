#include "Stencil.h"

Stencil::Stencil()
{
    //ctor
}

Stencil::~Stencil()
{
    //dtor
}
void Stencil::drawMask(Entity* E)
{
glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );

    //Start using the stencil
    glEnable( GL_STENCIL_TEST );

    //Place a 1 where rendered
    glStencilFunc( GL_ALWAYS, 1, 1 );

    //Replace where rendered
    glStencilOp( GL_REPLACE, GL_REPLACE, GL_REPLACE );

		glPushMatrix();



    glBegin(GL_TRIANGLE_FAN);
	for(int ii = 0; ii < 360; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(360);//get the current angle

		float x = 0.1 * cosf(theta);//calculate the x component
		float y = 0.1 * sinf(theta);//calculate the y component

		glVertex2f(x + E->xPos, y + E->yPos);//output vertex

	}
	glEnd();

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
