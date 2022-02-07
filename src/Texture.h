#ifndef TEXTURE_H
#define TEXTURE_H

#include "Include.h"

class Texture
{
	friend class MemoryManager;
private:
	Texture();
	~Texture();
	Texture* loadFromTGA(const char* filename);
	Texture* loadFromPNG(const char* filename);
public:
	GLuint getId();
	int getWidth();
	int getHeight();
private:
	std::string		mName;
	GLuint			mId;
	int				mWidth;
	int				mHeight;
};

#endif