#include "Include.h"
#include "Game.h"

Game::Game(WNDPROC wndProc)
{
	mWndProc			= wndProc;
	mAlive				= true;
	mTimer				= Timer();
	mWindow				= new Window(wndProc);	
	mPrevMouse			= POINT();
	mWorld				= new World(this);
	mMemoryManager		= new MemoryManager(this);

	//Math::Degree rotElev	= Math::Degree(MIN_ROT_ELEV + (MAX_ROT_ELEV - MIN_ROT_ELEV) * 0.5f);
	float zoom				= MIN_ZOOM + (MAX_ZOOM-MIN_ZOOM)*0.5f;
	mCamera					= new Camera(Math::Degree(0), Math::Degree(25.0f), Math::Degree(0), zoom);
	mFps					= 0;
	GetCursorPos(&mPrevMouse);	
}
Game::~Game()
{
	delete mMemoryManager;

	delete mWorld;

	delete mWindow;
}
bool Game::initialize(bool fullscreen)
{
	if(!mWindow->initialize("Cat Game", 800, 600, 32, fullscreen)) {
		return false;
	}

	if(!initGL()) {
		return false;
	}

	if(!mWorld->initialize(std::string("main.catmap"))) {
		return false;
	}

	mTimer.start();
	return true;
}

void Game::update()
{
	GameTime gameTime;
	gameTime.timeElapsed = mTimer.getSeconds();
	gameTime.deltaTime = mTimer.getDeltaSeconds();

	mWorld->update(gameTime);

	//UPDATE MOUSE MOTION
	POINT mousePt;
	GetCursorPos(&mousePt);
	if(mousePt.x != mPrevMouse.x || mousePt.y != mPrevMouse.y) {
		onMouseMove(mousePt.x, mousePt.y);
	}

	if(keys[VK_F1])
	{
		std::string title			= mWindow->getTitle();
		int width					= mWindow->getWidth();
		int height					= mWindow->getHeight();
		int bits					= mWindow->getBits();
		bool fs						= mWindow->getFullscreen();

		delete mWindow;
		mWindow = new Window(mWndProc);
		mWindow->initialize(title.c_str(), width, height, bits, !fs);
	}

	if(keys['Q'])
	{
		mCamera->setRotY( mCamera->getRotY() - 2.0f );
	}

	if(keys['E'])
	{
		mCamera->setRotY( mCamera->getRotY() + 2.0f );
	}


	//float len = mWorld->getKitty()->getVelocity().getLength();
	//float calc = len * (MAX_FOVY-MIN_FOVY) / (MAX_RUN_SPEED) + MIN_FOVY;
	//mWindow->setFovy( calc );

	static float prevTime = gameTime.timeElapsed;
	static unsigned int fpsTicks = 0;
	if(prevTime + 1.0f < gameTime.timeElapsed) {
		mFps = fpsTicks;
		prevTime = gameTime.timeElapsed;
		fpsTicks = 0;
	}
	++fpsTicks;
	
	mTimer.tick();
}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glScalef(-1, 1, 1);									//mirror x-axis to make forward direction be positive-z

	mCamera->apply();									//apply camera transforms

	mWorld->draw();										//draw world


	Font* font = MM.getFont("font.png");
	if(font) {
		Math::Vector3 camPos = mCamera->getPosition();
		std::stringstream camStream;
		camStream << "Camera: (" << camPos.x << ", " << camPos.y << ", " << camPos.z << ")";
		font->print(0, mWindow->getHeight() - 20, camStream.str().c_str());
		/*
		std::stringstream rotXStream;
		rotXStream << "RotX: " << mCamera->getRotX().getValue();
		font->print(0, 180, rotXStream.str().c_str());

		std::stringstream timeStream;
		timeStream << "Elapsed Time: " << mTimer.getSeconds();
		font->print(0, 160, timeStream.str().c_str());

		std::stringstream colStream;
		colStream << "Columns: (" << mCurColumn->getTileX() << ", " << mCurColumn->getTileZ() << ")";
		font->print(0, 140, colStream.str().c_str());

		std::stringstream velStream;
		velStream << "Velocity: (" << mVelocity.x << ", " << mVelocity.y << ", " << mVelocity.z << ")";
		font->print(0, 120, velStream.str().c_str());

		std::stringstream posStream;
		posStream << "Position: (" << mPosition.x << ", " << mPosition.y << ", " << mPosition.z << ")";
		font->print(0, 100, posStream.str().c_str());

		std::stringstream headingStream;
		headingStream << "Heading: " << mRotation.getValue();
		font->print(0, 80, headingStream.str().c_str());

		std::stringstream LStream;
		LStream << "L: (" << L.x << ", " << L.z << ")";
		font->print(0, 60, LStream.str().c_str());

		std::stringstream FStream;
		FStream << "F: (" << F.x << ", " << F.z << ")";
		font->print(0, 40, FStream.str().c_str());

		std::stringstream RStream;
		RStream << "R: (" << R.x << ", " << R.z << ")";
		font->print(0, 20, RStream.str().c_str());

		std::stringstream BStream;
		BStream << "B: (" << B.x << ", " << B.z << ")";
		font->print(0, 0, BStream.str().c_str());
	
		float winWidth = (float)theGame->getWindow()->getWidth();
		font->print((int)winWidth - 150, 22, "Stamina");
		*/

		//std::stringstream strFPS;
		//strFPS << "FPS: " << mFps;
		//font->print(0, 80, strFPS.str().c_str());

		std::stringstream sVel;
		Math::Vector3 vel = mWorld->getKitty()->getVelocity();
		sVel << "cat vel: (" << vel.x << ", " << vel.y << ", " << vel.z << ")";
		font->print(0, 40, sVel.str().c_str());

		std::stringstream heading;
		heading << "Heading: " << mWorld->getKitty()->getHeading().getValue();
		font->print(0, 20, heading.str().c_str());

		//std::stringstream rotElev;
		//rotElev << "RotElev: " << mCamera->getRotElev().getValue();
		//font->print(0, 0, rotElev.str().c_str());

		WorldTime* wt = mWorld->getWorldTime();
		std::stringstream wtStr;
		wtStr << "WorldTime: " << wt->getTotalSeconds() << " ----- " << wt->getHours() << ":" << wt->getMinutes();
		font->print(0, 0, wtStr.str().c_str());
	}

	mWindow->start2d();
		int winWidth = mWindow->getWidth();
		int barWidth = (int)(150.0 * mWorld->getKitty()->getStamina() / MAX_STAMINA);
		
		glColor3f(0, 1, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_QUADS);
			glVertex2i(winWidth - 10 - barWidth, 4);
			glVertex2i(winWidth - 10 - barWidth, 20);
			glVertex2i(winWidth - 10, 20);
			glVertex2i(winWidth - 10, 4);
		glEnd();

	mWindow->end2d();

	mWindow->swapBuffers();
}

void Game::onMouseMove(int x, int y)
{
	Kitty* cat = mWorld->getKitty();
	float ySensitivity = 0.2f;
	float xSensitivity = 0.5f;

	float deltaMouseX = (float)(350-x);
	if(deltaMouseX != 0) {		
		float delta = deltaMouseX * xSensitivity;
		cat->setHeading(cat->getHeading() + delta);
		SetCursorPos(350, 350);
	}

	float deltaMouseY = (float)(y-350);
	if(deltaMouseY != 0) {
		float delta = deltaMouseY * ySensitivity;
		//Math::Degree vr = mCamera->getRotElev() + delta;
		//Math::Degree cr = mCamera->getRotX() + delta;
		//mCamera->setRotElev( vr );
		//mCamera->setRotX( cr );
		SetCursorPos(350, 350);
	}
}

void Game::onMouseScroll(short delta)
{
	float zoomDelta = (delta > 0 ? 1.5f : -1.5f);
	float curZoom = mCamera->getZoom();
	mCamera->setZoom( Math::clamp<float>(curZoom + zoomDelta, MIN_ZOOM, MAX_ZOOM) );
}

//OCCURS ONLY ONCE EVERY TIME THE KEY IS PRESSED
void Game::onKeyDown(unsigned char key)
{
	keys[key] = true;

	if(key == 'P') {
		if(mTimer.isPaused()) {
			mTimer.unpause();
		} else {
			mTimer.pause();
		}
	}

	if(key == 'R') {
		mCamera->setRotY(Math::Degree(0));
	}

	if(key == VK_ESCAPE) {
		mAlive = false;
	}
}

void Game::onKeyUp(unsigned char key)
{
	keys[key] = false;
}

Camera* Game::getCamera()
{
	return mCamera;
}

Window* Game::getWindow()
{
	return mWindow;
}

World* Game::getWorld()
{
	return mWorld;
}

bool Game::isPaused()
{
	return mTimer.isPaused();
}

void Game::pause()
{
	mTimer.pause();
}

void Game::unpause()
{
	mTimer.unpause();
}

MemoryManager* Game::getMemoryManager()
{
	return mMemoryManager;
}

bool Game::isAlive()
{
	return mAlive;
}

void Game::kill()
{
	mAlive = false;
}