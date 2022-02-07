#include "Include.h"
#include "Font.h"
#include "Game.h"

Font::Font(Window* window)
{
	mWindow		= window;
	mBase		= 0;
	mTexture	= NULL;
}
Font::~Font()
{
	if(mBase != 0)
		glDeleteLists(mBase, 256);
}

Font* Font::loadFromFile(const char* filename)
{
	Texture* tex = MM.getTexture(filename);
	if(!tex) {
		log_error(STR("Failed to get font texture: ") + filename);
		return NULL;
	}
	mTexture = tex;

	mBase = glGenLists(128);

	glBindTexture(GL_TEXTURE_2D, tex->getId());

	int i=0;
	float dx = 16.0/256;
	float dy = 16.0/128;
	float cx, cy;
	for(int y=0; y<8; ++y) {
		cy = dy * y;
		for(int x=0; x<16; ++x) {
			cx = dx * x;
			glNewList(mBase + i,GL_COMPILE);				// Start Building A List
				glBegin(GL_QUADS);							// Use A Quad For Each Character
					glTexCoord2f(cx,1-cy-dy);			// Texture Coord (Bottom Left)
					glVertex2i(0,0);						// Vertex Coord (Bottom Left)
					glTexCoord2f(cx+dx,1-cy-dy);	// Texture Coord (Bottom Right)
					glVertex2i(16,0);						// Vertex Coord (Bottom Right)
					glTexCoord2f(cx+dx,1-cy);			// Texture Coord (Top Right)
					glVertex2i(16,16);						// Vertex Coord (Top Right)
					glTexCoord2f(cx,1-cy);					// Texture Coord (Top Left)
					glVertex2i(0,16);						// Vertex Coord (Top Left)
				glEnd();									// Done Building Our Quad (Character)
				glTranslated(16,0,0);						// Move To The Right Of The Character
			glEndList();									// Done Building The Display List
			
			++i;
		}
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	return this;
}

void Font::print(GLint x, GLint y, const char* str, GLfloat r, GLfloat g, GLfloat b)
{
	glColor3f(r, g, b);
	glBindTexture(GL_TEXTURE_2D, mTexture->getId());			// Select Our Font Texture

	mWindow->start2d();
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glTranslated(x,y,0);								// Position The Text (0,0 - Bottom Left)
	glListBase(mBase-32);									// Choose The Font Set (0 or 1)
	glCallLists(strlen(str), GL_UNSIGNED_BYTE, str);		// Write The Text To The Screen
	
	mWindow->end2d();

	glBindTexture(GL_TEXTURE_2D, 0);
}