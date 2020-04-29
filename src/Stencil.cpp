#include "Stencil.h"

Stencil::Stencil()
{
    //ctor
}

Stencil::~Stencil()
{
    //dtor
}
void Stencil::drawMask(Entity* E, float aspectRatio)
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
	for(int ii = 0; ii < 45; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii*8) / float(360);//get the current angle
		float x = 0.1 * cosf(theta)*aspectRatio+0.01;//calculate the x component
		float y = 0.1 * sinf(theta)+0.01;//calculate the y component

		glVertex2f(x + E->xPos, y + E->yPos);//output vertex


	}
	glEnd();
    glBegin(GL_TRIANGLES);
	//for(int ii = 0; ii < 1; ii++)
	//{
		//float theta = 2.0f * 3.1415926f * float(0*360) / float(360);//get the current angle
        //std::cout << aspectRatio << std::endl;
		//float x = 0.2 * cosf(theta)*aspectRatio;//calculate the x component
		//float y = 0.2 * sinf(theta);//calculate the y component

		//glVertex2f(x + E->xPos, y + E->yPos);//output vertex
		glVertex2f(E->xPos,E->yPos+0.01);//output vertex
		glVertex2f(.3+E->xPos, .1+E->yPos);//output vertex
		glVertex2f(.3+E->xPos, -.1+E->yPos);//output vertex

	//}
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
