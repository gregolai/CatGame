#include "Include.h"
#include "World.h"
#include "Game.h"

World::World(Game* game)
{
	mGame					= game;
	mTilesX					= 0;
	mTilesZ					= 0;
	mUnitsX					= 0;
	mUnitsZ					= 0;
	mColumns				= NULL;
	mKitty					= NULL;
	mWorldTime				= new WorldTime(this);
}

World::~World()
{
	delete mWorldTime;

	if(mColumns) {
		for(int z=0; z<mTilesZ; ++z) {
			for(int x=0; x<mTilesX; ++x) {
				delete mColumns[z][x];
			}
			delete[] mColumns[z];
		}
		delete[] mColumns;
	}
}

bool World::initialize(std::string& filename)
{

	if(!loadFromFile(filename)) {
		log_error(STR("Unable to load from world file: ") + filename);
		return false;
	}
	
	mKitty = MM.createKitty("cat.ani");

	//INIT MICE
	Math::Vector3 v;
	int i=0;
	Mouse* m;
	while(i<20) {
		v = Math::Vector3(Math::frand(0, mUnitsX), 0, Math::frand(0, mUnitsZ));
		m = MM.tryCreateMouse("mouse.ani", v);
		if(m) {
			mMice.push_back(m);
			++i;
		}
	}

	
	Sequence* seq = MM.getSequence(std::string("man_bathroom_trip.seq"));

	mWorldTime->setTime(8, 30);

	//MM.printResources();

	return true;
}

void World::update(GameTime& gameTime)
{
	mWorldTime->update(gameTime);

	mKitty->update(gameTime);

	size_t miceSz = mMice.size();
	for(size_t i=0; i<miceSz; ++i) {
		mMice[i]->update(gameTime);
	}

	for(int z=0; z<mTilesZ; ++z) {
		for(int x=0; x<mTilesX; ++x) {
			mColumns[z][x]->update(gameTime);
		}
	}

	
}

void World::draw()
{
	float t = mWorldTime->getPercentOfDay();
	float ratio = (-cos( Math::Degree(t * 360).getRadians() ) + 1.0f) * 0.5f;
	float r = 0.1f * ratio;
	float g = 0.6f * ratio;
	float b = 1.0f * ratio;
	glClearColor(r, g, b, 1.0f);

	Math::Vector3 kittyPos = mKitty->getPosition();

	glPushMatrix();



		//POSITION LIGHTING IN CENTER OF WORLD
		{
			//Math::Degree lightAngle = mWorldTime->getTotalHours() / 24.0f * 360.0f;
			//float lightRadius = 200.0f;
			//float lightX = mUnitsX*0.5f + lightRadius * cos(lightAngle.getRadians() - Math::C_HALF_PI);
			//float lightY = lightRadius * sin(lightAngle.getRadians() - Math::C_HALF_PI);
			
			GLfloat light_pos[] = { mUnitsX*0.5f, 100.0f, mUnitsZ*0.5f, 1.0f };
			GLfloat light_ambient[] = { ratio, ratio, ratio, 1.0f };
			GLfloat light_diffuse[] = { ratio, ratio, ratio, 1.0f };

			glEnable(GL_LIGHT0);
			glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
			glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		}

		glRotatef(mKitty->getHeading().getValue(), 0, 1, 0);	
		glTranslatef(-kittyPos.x, -kittyPos.y, -kittyPos.z);

		glPushMatrix();
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			for(int z=0; z<mTilesZ; ++z) {
				for(int x=0; x<mTilesX; ++x) {
					mColumns[z][x]->draw();
				}
			}

			for(size_t i=0; i<mMice.size(); ++i) {
				mMice[i]->draw();
			}

			mGame->getWindow()->drawGui3d(MM.getTexture("thoughtbubble.png"),
				Math::Vector3(5.0f, 1.0f, 5.0f), Math::Vector3(1, 1, 1), Math::Degree(0));

		glPopMatrix();

	glPopMatrix();

	mKitty->draw();			//draw kitty at current position

}

Column* World::getColumn(int x, int z)
{
	return mColumns[z][x];
}

Column* World::getColumnFromPt(Math::Vector3& pt)
{
	int x = (int)(pt.x / COLUMN_WIDTH);
	int z = (int)(pt.z / COLUMN_WIDTH);
	x = Math::clamp<int>(x, 0, mTilesX-1);
	z = Math::clamp<int>(z, 0, mTilesZ-1);
	return mColumns[z][x];
}

StaticObject* World::checkCollisions(Math::Vector3& pt)
{
	return getColumnFromPt(pt)->checkCollisions(pt);
}

int World::getTilesX()
{
	return mTilesX;
}

int World::getTilesZ()
{
	return mTilesZ;
}

float World::getUnitsX()
{
	return mUnitsX;
}

float World::getUnitsZ()
{
	return mUnitsZ;
}

Kitty* World::getKitty()
{
	return mKitty;
}

WorldTime* World::getWorldTime()
{
	return mWorldTime;
}

bool World::loadFromFile(std::string& filename, int tileOffX, int tileOffZ)
{
	std::vector<std::string> lines;
	if(!getFileLines(WORLD_DIR + filename, lines)) {
		log_error(STR("Error loading world from file: ") + filename);
		return false;
	}

	size_t numLines = lines.size();

	//OBJ
	std::string		objName;
	int				objTilesX;
	int				objTilesZ;
	float			objElev;
	int				objRot;
	int				objTexVar;
	Math::Vector3	objScale;
	bool			objCollides;
	float			objCollideHeight;
	//int			objId;
	std::string		objAni;

	//WAY
	int				wayId;
	int				wayTilesX;
	int				wayTilesZ;
	float			wayElev;
	Column*			wayCol;

	std::string tok;
	std::vector<std::string> words;
	for(size_t i=0; i<numLines; ++i) {
		StringUtil::trim(lines[i]);

		//get the next line
		if(lines[i] != "") {

			//get the first word of the line, which is always the keyword token
			words = StringUtil::split(lines[i], std::string(" "));
			if(words.size() > 0) {

				tok = words[0];

				if(tok == "MAPSIZE") {
					//if this is from the first file included
					if(mTilesX == 0 && mTilesZ == 0) {
						mTilesX			= atoi(words[1].c_str());
						mTilesZ			= atoi(words[2].c_str());
						mUnitsX			= mTilesX * 1.0f;
						mUnitsZ			= mTilesZ * 1.0f;
						mColumns		= new Column**[mTilesZ];
						for(int z=0; z<mTilesZ; ++z) {
							mColumns[z] = new Column*[mTilesX];
							for(int x=0; x<mTilesX; ++x) {
								mColumns[z][x] = new Column(this, x, z);
							}
						}
					}
				} 
				else if(tok == "INCLUDE") {
					int offX	= atoi(words[2].c_str());
					int offZ	= atoi(words[3].c_str());
					loadFromFile(words[1], tileOffX + offX, tileOffZ + offZ);
				}
				else if(tok == "OBJ") {
					objName				= words[1] + ".obj";
					objTilesX			= tileOffX + atoi(words[2].c_str());
					objTilesZ			= tileOffZ + atoi(words[3].c_str());
					objElev				= (float)atof(words[4].c_str());
					objRot				= atoi(words[5].c_str());
					objTexVar			= atoi(words[6].c_str());
					objScale.x			= (words[7] == "+" ? 1.0f : -1.0f);
					objScale.y			= (words[8] == "+" ? 1.0f : -1.0f);
					objScale.z			= (words[9] == "+" ? 1.0f : -1.0f);
					objCollides			= (words[10] == "1" ? true : false);
					objCollideHeight	= ( objCollides ? (float)atof(words[11].c_str()) : 0 );

					std::string testName;
					if(words.size() > 12)
						testName = words[12];

					Model* m = MM.getModel(objName.c_str());
					if(m) {
						Column* col = mColumns[objTilesZ][objTilesX];
						StaticObject* obj = MM.createStaticObject(m, objTexVar, col, objElev, Math::Degree((float)objRot), objScale, objCollideHeight, testName);
						if(obj) {
							col->insertObject(obj);
						}
					} //if m
				
				} else if(tok =="WAY") {
					wayId			= atoi(words[1].c_str());
					wayTilesX		= tileOffX + atoi(words[2].c_str());
					wayTilesZ		= tileOffZ + atoi(words[3].c_str());
					wayElev			= (float)atof(words[4].c_str());
					wayCol			= mColumns[wayTilesZ][wayTilesX];

					MM.createWaypoint(wayId, wayCol, wayElev);

				}

			} //if words > 0

		} //if lines != ""
	
	} //foreach line

	return true;
}