#include "Include.h"
#include "MemoryManager.h"
#include "Game.h"

MemoryManager::MemoryManager(Game* game)
{
	mGame = game;
	mKitty = NULL;
}
MemoryManager::~MemoryManager()
{
	if(mKitty) {
		delete mKitty;
		mKitty = NULL;
	}

	std::set<StaticObject*>::iterator staticObjIt = mStaticObjects.begin();
	for( ; staticObjIt != mStaticObjects.end(); ++staticObjIt) {
		delete (*staticObjIt);
	}

	std::set<Mouse*>::iterator mouseIt = mMice.begin();
	for( ; mouseIt != mMice.end(); ++mouseIt) {
		delete (*mouseIt);
	}

	std::map<std::string, Texture*>::iterator texIt = mTextures.begin();
	for( ; texIt != mTextures.end(); ++texIt) {
		delete (*texIt).second;
	}

	std::map<std::string, Model*>::iterator modelIt = mModels.begin();
	for( ; modelIt != mModels.end(); ++modelIt) {
		delete (*modelIt).second;
	}

	std::map<std::string, AnimationData*>::iterator animIt = mAnimationData.begin();
	for( ; animIt != mAnimationData.end(); ++animIt) {
		delete (*animIt).second;
	}

	std::map<std::string, Font*>::iterator fontIt = mFonts.begin();
	for( ; fontIt != mFonts.end(); ++fontIt) {
		delete (*fontIt).second;
	}

	std::map<int, Waypoint*>::iterator wayIt = mWaypoints.begin();
	for( ; wayIt != mWaypoints.end(); ++wayIt) {
		delete (*wayIt).second;
	}

	std::map<std::string, Sequence*>::iterator seqIt = mSequences.begin();
	for( ; seqIt != mSequences.end(); ++seqIt) {
		delete (*seqIt).second;
	}
}

Model* MemoryManager::getModel(const char* filename)
{
	std::map<std::string, Model*>::iterator it = mModels.find(std::string(filename));
	if(it != mModels.end()) {
		return (*it).second;
	} else {
		Model* m = new Model();			
		if(!m->loadFromOBJ(filename)) {
			log_error(STR("Failed to get model: ") + filename);
			delete m;
			return NULL;
		}
		mModels[std::string(filename)] = m;
		return m;
	}
}

Texture* MemoryManager::getTexture(const char* filename)
{
	std::map<std::string, Texture*>::iterator it = mTextures.find(std::string(filename));
	if(it != mTextures.end()) {
		return (*it).second;
	} else {

		Texture* t = new Texture();

		std::vector<std::string> C = StringUtil::split(std::string(filename), std::string("."));
		std::string ext = C[C.size()-1];
		
		StringUtil::toLowerCase(ext);

		if(ext == "tga") {
			if(!t->loadFromTGA(filename)) {
				log_error(STR("Failed to load TGA texture: ") + filename);
				delete t;
				return NULL;
			}
		} else if(ext == "png") {
			if(!t->loadFromPNG(filename)) {
				log_error(STR("Failed to load PNG texture: ") + filename);
				delete t;
				return NULL;
			}
		} else {
			log_error(STR("Extension \"") + ext + STR("\" not supported."));
			delete t;
			return NULL;
		}

		mTextures[std::string(filename)] = t;
		return t;
	}
}

AnimationData* MemoryManager::getAnimationData(const char* filename)
{
	std::map<std::string, AnimationData*>::iterator it = mAnimationData.find(std::string(filename));
	if(it != mAnimationData.end()) {
		return (*it).second;
	} else {
		AnimationData* a = new AnimationData();
		if(!a->loadFromFile(filename)) {
			log_error(STR("Failed to get animation data: ") + filename);
			delete a;
			return NULL;
		}
		mAnimationData[std::string(filename)] = a;
		return a;
	}
}

Font* MemoryManager::getFont(const char* filename)
{
	std::map<std::string, Font*>::iterator it = mFonts.find(std::string(filename));
	if(it != mFonts.end()) {
		return (*it).second;
	} else {
		Font* f = new Font(mGame->getWindow());
		if(!f->loadFromFile(filename)) {
			log_error(STR("Failed to get font: ") + filename);
			delete f;
			return NULL;
		}

		mFonts[std::string(filename)] = f;
		return f;
	}
}

Waypoint* MemoryManager::getWaypoint(int wayId)
{
	std::map<int, Waypoint*>::iterator it = mWaypoints.find(wayId);
	if(it != mWaypoints.end()) {
		return (*it).second;
	} else {
		return NULL;
	}
}

Sequence* MemoryManager::getSequence(std::string& filename)
{
	std::map<std::string, Sequence*>::iterator it = mSequences.find(filename);
	if(it != mSequences.end()) {
		return (*it).second;
	} else {
		Sequence* seq = new Sequence(filename);
		if(!seq->loadFromFile(filename)) {
			delete seq;
			log_error(STR("Unable to load sequence file: ") + filename);
			return NULL;
		}

		mSequences[filename] = seq;

		return seq;
	}
}

Object* MemoryManager::getNamedObject(std::string& name)
{
	std::map<std::string, Object*>::iterator it = mNamedObjects.find(name);
	if(it != mNamedObjects.end()) {
		return (*it).second;
	} else {
		return NULL;
	}
}

StaticObject* MemoryManager::createStaticObject(Model* model, unsigned int textureVariant, Column* col, float elev,
	Math::Degree& rot, Math::Vector3& scale, float collideHeight, std::string& name)
{
	Texture* texture = model->getTextureVariant(textureVariant);
	if(!texture) {
		log_error("Unable to create object with this model/texture variant.");
		return NULL;
	}
	StaticObject* obj = new StaticObject(mGame->getWorld(), model, texture, col, elev, rot, scale, collideHeight);
	if(!obj->initialize()) {
		log_error("Failed to initialize object.");
		delete obj;
		return NULL;
	}
	mStaticObjects.insert(obj);

	if(name != "") {
		if(mNamedObjects.find(std::string(name)) == mNamedObjects.end()) {
			mNamedObjects[std::string(name)] = obj;
		} else {
			log_warning(STR("Named object with duplicate name detected: ") + name);
		}
	}

	return obj;
}

Waypoint* MemoryManager::createWaypoint(int id, Column* col, float elev)
{
	if(mWaypoints.find(id) != mWaypoints.end()) {
		log_error("Duplicate waypoint data id detected. Unable to create waypoint.");
		return NULL;
	}

	Waypoint* wp = new Waypoint(mGame->getWorld(), id, col, elev);
	
	mWaypoints[id] = wp;

	return wp;
}

Mouse* MemoryManager::tryCreateMouse(const char* animFilename, Math::Vector3& pos)
{
	Math::Vector3 groundPoint(pos.x, 0, pos.z);
	World* world = mGame->getWorld();
	Column* column = world->getColumnFromPt(groundPoint);
	if(!column) {
		return NULL;
	}

	StaticObject* obj = column->checkCollisions(groundPoint);
	if(obj) {
		return NULL;
	}

	AnimationData* animData = getAnimationData(animFilename);

	Mouse* mouse = new Mouse(world, animData, groundPoint);
	if(!mouse->initialize()) {
		log_error("Failed to initialize mouse.");
		delete mouse;
		return NULL;
	}

	mMice.insert(mouse);
	return mouse;
}

/*
StaticObject* createObject(AnimationData* anim)
{
	StaticObject* obj = new Object(anim);
	if(!obj->initialize()) {
		log_error("Failed to initialize object.");
		delete obj;
		return NULL;
	}
	mStaticObjects.insert(obj);
	return obj;
}
*/

Kitty* MemoryManager::createKitty(const char* animFilename)
{
	AnimationData* animData = getAnimationData(animFilename);
	if(!animData) {
		log_error(STR("Unabled to get animation: ") + animFilename);
		return NULL;
	}

	Kitty* k = new Kitty(mGame->getWorld(), animData);
	if(!k->initialize()) {
		log_error("Failed to initialize kitty.");
		delete k;
		return NULL;
	}

	mKitty = k;
	return k;
}

void MemoryManager::printResources()
{
	std::stringstream out;
	/*
	std::set<StaticObject*>::iterator objIt = mStaticObjects.begin();
	for( ; objIt != mStaticObjects.end(); ++objIt) {
		out		<< "Object: " << std::endl
				<< "  Model - " << (*objIt)->mModel->name << std::endl
				<< "  Texture - " << (*objIt)->mTexture->name << std::endl;
	}
	*/
	std::map<std::string, Texture*>::iterator texIt = mTextures.begin();
	for( ; texIt != mTextures.end(); ++texIt) {
		out		<< "Texture: " << (*texIt).first << std::endl;
	}

	std::map<std::string, Model*>::iterator mdlIt = mModels.begin();
	for( ; mdlIt != mModels.end(); ++mdlIt) {
		out		<< "Model: " << (*mdlIt).first << std::endl;
	}

	std::map<std::string, AnimationData*>::iterator animIt = mAnimationData.begin();
	for( ; animIt != mAnimationData.end(); ++animIt) {
		out		<< "Anim: " << (*animIt).first << std::endl;
	}

	log_debug( out.str() );
}