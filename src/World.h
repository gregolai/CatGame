#ifndef WORLD_H
#define WORLD_H

#include "Include.h"

class World
{
public:
	World(Game* game);
	~World();
	bool initialize(std::string& filename);
	void update(GameTime& gameTime);
	void draw();

	Column* getColumn(int x, int z);
	Column* getColumnFromPt(Math::Vector3& pt);

	StaticObject* checkCollisions(Math::Vector3& pt);

	int getTilesX();
	int getTilesZ();
	float getUnitsX();
	float getUnitsZ();
	Kitty* getKitty();
	WorldTime* getWorldTime();
private:
	bool loadFromFile(std::string& filename, int tileOffX = 0, int tileOffZ = 0);
	
	Game*					mGame;
	int						mTilesX;
	int						mTilesZ;
	float					mUnitsX;
	float					mUnitsZ;
	Column***				mColumns;
	Kitty*					mKitty;
	std::vector<Mouse*>		mMice;
	WorldTime*				mWorldTime;
};

#endif