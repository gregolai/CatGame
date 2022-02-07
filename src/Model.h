#ifndef MODEL_H
#define MODEL_H

#include "Include.h"

class Model
{
	friend class MemoryManager;
private:
	Model();
	~Model();
	Model* loadFromOBJ(const char* filename);
	bool loadTextureFromMtl(const char* filename, std::vector<Texture*>& texRet);
public:
	Texture* getTextureVariant(unsigned int variant);
	GLuint getId();
	Math::Box3& getBoundingBox();
private:
	std::string						mName;
	GLuint							mId;
	Math::Box3						mBoundingBox;
	std::vector<Texture*>			mTextures;
};

#endif