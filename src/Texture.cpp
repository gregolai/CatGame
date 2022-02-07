#include "Include.h"
#include "Texture.h"
#include "Game.h"

Texture::Texture()
{
	mName = "";
	mId = 0;
}

Texture::~Texture()
{
	if(mId != 0) {
		glDeleteTextures(1, &mId);
	}
}

Texture* Texture::loadFromTGA(const char* filename)
{
	mName = filename;

	TGAImg tgaImage;
	if(tgaImage.Load((char*)(TEXTURE_DIR + filename).c_str()) != IMG_OK) {
		log_error(STR("File unable to be opened: ") + filename);
		return NULL;
	}

	unsigned char* data = tgaImage.GetImg();
	int channels = tgaImage.GetBPP() / 8;
	mWidth = tgaImage.GetWidth();
	mHeight = tgaImage.GetHeight();

	if(channels != 3 && channels != 4) {
		log_error(STR("File bpp not supported: ") + filename);
		return NULL;
	}

	GLenum format = (channels == 3 ? GL_RGB : GL_RGBA);

	glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId);

	if(channels == 4) {
		glTexImage2D(GL_TEXTURE_2D, 0, channels, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	} else {
		gluBuild2DMipmaps(GL_TEXTURE_2D, channels, mWidth, mHeight, format, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	return this;
}

Texture* Texture::loadFromPNG(const char* filename)
{
	mName = filename;

	unsigned char* fbuf;
	long flen;
	//buffer file
	{
		FILE* f = NULL;
		
		fopen_s(&f, (TEXTURE_DIR + filename).c_str(), "rb");
		if(!f) {
			log_error(STR("File unable to be opened: ") + filename);
			return NULL;
		}

		fseek(f, 0, SEEK_END);
		flen = ftell(f);
		fseek(f, 0, SEEK_SET);
		
		fbuf = new unsigned char[flen];
		fread(fbuf, 1, flen, f);
		fclose(f);
	}

	std::vector<unsigned char> dataVector;
	unsigned long w, h;
	if(decodePNG(dataVector, w, h, fbuf, flen) != 0) {
		log_error(STR("Failed to decode PNG file: ") + filename);
		return NULL;
	}

	mWidth = (int)w;
	mHeight = (int)h;
	
	size_t sz = dataVector.size();
	unsigned char* data = new unsigned char[sz];
	for(size_t i=0; i<sz; ++i) {
		data[i] = dataVector[i];
	}

	int channels = sz / (mWidth * mHeight);

	if(channels != 3 && channels != 4) {
		log_error(STR("File bpp not supported: ") + filename);
		return NULL;
	}

	//SWAP ROWS
	size_t rowWidth = channels * mWidth;
	unsigned char* temp = new unsigned char[rowWidth];
	size_t d;
	for(size_t i=0; i<(size_t)(sz*0.5); i+=rowWidth) {
		d = sz-i-rowWidth;
		memcpy(temp, &data[i], rowWidth);
		memcpy(&data[i], &data[d], rowWidth);
		memcpy(&data[d], temp, rowWidth);
	}
	delete[] temp;

	GLenum format = (channels == 3 ? GL_RGB : GL_RGBA);

	glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId);

	if(channels == 4) {
		glTexImage2D(GL_TEXTURE_2D, 0, channels, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	} else {
		gluBuild2DMipmaps(GL_TEXTURE_2D, channels, mWidth, mHeight, format, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	delete[] data;
	return this;
}

GLuint Texture::getId()
{
	return mId;
}

int Texture::getWidth()
{
	return mWidth;
}

int Texture::getHeight()
{
	return mHeight;
}
