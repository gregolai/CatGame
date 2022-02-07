#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "Include.h"

class MemoryManager
{
public:
	MemoryManager(Game* game);
	~MemoryManager();
	Model* getModel(const char* filename);
	Texture* getTexture(const char* filename);
	AnimationData* getAnimationData(const char* filename);
	Font* getFont(const char* filename);
	Waypoint* getWaypoint(int wayId);
	Sequence* getSequence(std::string& filename);

	Object* getNamedObject(std::string& name);

	StaticObject* createStaticObject(Model* model, unsigned int textureVariant, Column* col, float elev,
		Math::Degree& rot, Math::Vector3& scale, float collideHeight, std::string& name = std::string());

	Waypoint* createWaypoint(int id, Column* col, float elev);

	Mouse* tryCreateMouse(const char* animFilename, Math::Vector3& pos);

	Kitty* createKitty(const char* animFilename);

	//FOR DEBUGGING
	void printResources();
private:
	Game*										mGame;
	Kitty*										mKitty;
	std::set<StaticObject*>						mStaticObjects;
	std::set<Mouse*>							mMice;	
	std::map<std::string, Texture*>				mTextures;
	std::map<std::string, Model*>				mModels;
	std::map<std::string, AnimationData*>		mAnimationData;
	std::map<std::string, Font*>				mFonts;
	std::map<int, Waypoint*>					mWaypoints;
	std::map<std::string, Sequence*>			mSequences;

	std::map<std::string, Object*>				mNamedObjects;
};

#endif