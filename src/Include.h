#ifndef INCLUDE_H
#define INCLUDE_H

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

// Windows
#include <windows.h>

// Standard C headers
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdarg>
#include <cmath>

// STL containers
#include <vector>
#include <map>
#include <string>
#include <set>
#include <list>
#include <deque>
#include <queue>
#include <bitset>

// STL algorithms & functions
#include <algorithm>
#include <functional>
#include <limits>

// C++ Stream stuff
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

//OpenGL stuff
#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library

//Common stuff
#include "console.h"
#include "log.h"
#include "png.h"
#include "stringutil.h"
#include "tga.h"
#include "timer.h"

//Math stuff
#include "Math.h"
#include "Box2.h"
#include "Box3.h"
#include "DegreeRadian.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Tween2.h"
#include "Tween3.h"

struct GameTime
{
	float deltaTime;
	float timeElapsed;
};

bool getFileLines(std::string& filename, std::vector<std::string>& lines);

//FORWARD DECLARATIONS
class Action;
class ActionList;
class Animable;
class Animation;
class AnimationData;
class AnimationFrame;
class AnimationState;
class Camera;
class Column;
class Font;
class Game;
class Kitty;
class Log;
class MemoryManager;
class Model;
class Mouse;
class Npc;
class Object;
class Sequence;
class StaticObject;
class StringUtil;
class Texture;
class TimedTrigger;
class Timer;
class TGAImg;
class Trigger;
class Waypoint;
class Window;
class World;
class WorldTime;

enum ActionType
{
	ACTION_ANI,
	ACTION_COLLIDE,
	ACTION_CONTINUE,
	ACTION_GO,
	ACTION_ROT,
	ACTION_SPEED,
	ACTION_START,
	ACTION_TO,
	ACTION_WAIT
};

enum KittyState
{
	KITTY_IDLE,
	KITTY_RUNNING,
	KITTY_WALKING,
	KITTY_CROUCHING
};

extern const std::string ACTION_DIR;
extern const std::string ANIMATION_DIR;
extern const std::string MODEL_DIR;
extern const std::string TEXTURE_DIR;
extern const std::string WORLD_DIR;

extern float MAX_RUN_SPEED;
extern float MAX_WALK_SPEED;
extern float MAX_CROUCH_SPEED;
extern float MAX_STRAFE_SPEED;
extern float MAX_FALL_SPEED;
extern float JUMP_SPEED_MAX;
extern float JUMP_SPEED_BASE;
extern float JUMP_SPEED_REFILL;
extern float ACCEL_GRAVITY;
extern float ACCELERATION;
extern float DRAG;
extern float MIN_ZOOM;
extern float MAX_ZOOM;
extern float COLUMN_WIDTH;
extern float MAX_STAMINA;
extern float FATIGUE_RATE;
extern float COLLIDE_EPSILON;
extern float MIN_ROT_ELEV;
extern float MAX_ROT_ELEV;
extern float MIN_FOVY;
extern float MAX_FOVY;
extern float MIN_ROT_X;
extern float MAX_ROT_X;
extern float TIME_UNITS_PER_SEC;
extern int SEC_PER_WORLDDAY;
extern int SEC_PER_DAY;
extern float NPC_SPEED;

extern Game* theGame;
extern bool keys[256];
extern LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	//passed in when intializing Window

#define MM				(*theGame->getMemoryManager())

#endif