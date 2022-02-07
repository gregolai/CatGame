#ifndef FONT_H
#define FONT_H

#include "Include.h"

class Font
{
	friend class MemoryManager;
private:
	Font(Window* window);
	~Font();
	Font* loadFromFile(const char* filename);
public:
	void print(GLint x, GLint y, const char* str, GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f);
private:
	Window*		mWindow;
	GLuint		mBase;
	Texture*	mTexture;
};

#endif