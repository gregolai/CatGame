#ifndef GAME_H
#define GAME_H

#include "Include.h"

#include "Action.h"
#include "ActionList.h"
#include "Animable.h"
#include "Animation.h"
#include "AnimationData.h"
#include "AnimationFrame.h"
#include "AnimationState.h"
#include "Camera.h"
#include "Column.h"
#include "Font.h"
#include "Kitty.h"
#include "MemoryManager.h"
#include "Model.h"
#include "Mouse.h"
#include "Npc.h"
#include "Object.h"
#include "Sequence.h"
#include "StaticObject.h"
#include "Texture.h"
#include "TimedTrigger.h"
#include "Trigger.h"
#include "Waypoint.h"
#include "Window.h"
#include "World.h"
#include "WorldTime.h"

class Game
{
public:
	Game(WNDPROC wndProc);
	~Game();
	bool initialize(bool fullscreen);

	void update();
	void draw();

	void onMouseMove(int x, int y);
	void onMouseScroll(short delta);
	void onKeyDown(unsigned char key);
	void onKeyUp(unsigned char key);

	Camera* getCamera();
	Window* getWindow();
	World* getWorld();
	bool isPaused();
	void pause();
	void unpause();
	MemoryManager* getMemoryManager();
	bool isAlive();
	void kill();
private:
	bool initGL()
	{
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClearDepth(1.0f);									// Depth Buffer Setup
		glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
		glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	

		glEnable(GL_LIGHTING);
		GLfloat global_ambient[] = { 0.9f, 0.9f, 0.9f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

		glAlphaFunc(GL_GREATER,0.95f);								// Set Alpha Testing
		glEnable(GL_ALPHA_TEST);									// Enable Alpha Testing

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
		//glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
		//glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light		
		//glEnable(GL_LIGHT1);								// Enable Light One
		return true;										// Initialization Went OK
	}

	WNDPROC			mWndProc;
	bool			mAlive;
	Timer			mTimer;
	Window*			mWindow;
	POINT			mPrevMouse;
	World*			mWorld;
	MemoryManager*	mMemoryManager;
	Camera*			mCamera;
	int				mFps;
};

#endif