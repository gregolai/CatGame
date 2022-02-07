#include "Include.h"

#ifdef _DEBUG
const std::string ACTION_DIR = "..\\..\\res\\action\\";
const std::string ANIMATION_DIR = "..\\..\\res\\animation\\";
const std::string MODEL_DIR = "..\\..\\res\\model\\";
const std::string TEXTURE_DIR = "..\\..\\res\\texture\\";
const std::string WORLD_DIR = "..\\..\\res\\world\\";
#else
const std::string ACTION_DIR		= "..\\..\\res\\action\\";
const std::string ANIMATION_DIR		= "..\\..\\res\\animation\\";
const std::string MODEL_DIR			= "..\\..\\res\\model\\";
const std::string TEXTURE_DIR		= "..\\..\\res\\texture\\";
const std::string WORLD_DIR			= "..\\..\\res\\world\\";
#endif

float MAX_RUN_SPEED				= 20.0f;
float MAX_WALK_SPEED			= 6.0f;
float MAX_CROUCH_SPEED			= 1.0f;
float MAX_STRAFE_SPEED			= 6.0f;
float MAX_FALL_SPEED			= 100.0f;
float JUMP_SPEED_MAX			= 40.0f;
float JUMP_SPEED_BASE			= 20.0f;
float JUMP_SPEED_REFILL			= 100.0f;
float ACCEL_GRAVITY				= 140.0f;
float ACCELERATION				= 30.0f;
float DRAG						= 100.0f;
float MIN_ZOOM					= -4.0f;
float MAX_ZOOM					= -10.0f;
float COLUMN_WIDTH				= 2.0f;
float MAX_STAMINA				= 100.0f;
float FATIGUE_RATE				= 1.0f;
float COLLIDE_EPSILON			= 0.001f;
float MIN_ROT_ELEV				= 10.0f;
float MAX_ROT_ELEV				= 45.0f;
float MIN_FOVY					= 55.0f;
float MAX_FOVY					= 80.0f;
float MIN_ROT_X					= MIN_ROT_ELEV;
float MAX_ROT_X					= MAX_ROT_ELEV;
float TIME_UNITS_PER_SEC		= 1.0f;
int SEC_PER_WORLDDAY			= 120;
int SEC_PER_DAY					= 60 * 60 * 24; // secs_per_min * min_per_hour * hours_per_day
float NPC_SPEED					= 1.0f;

bool getFileLines(std::string& filename, std::vector<std::string>& lines)
{
	std::vector<std::string> tempLines;
	
	std::ifstream myfile(filename.c_str());
	if(!myfile)
    {
		log_warning(STR("File unable to be opened: ") + filename);
		return false;
    }

	std::string strTemp;
	while(!myfile.eof())
    {
		std::getline(myfile,strTemp);
		tempLines.push_back(strTemp);
    }
	
	size_t sz = tempLines.size() - 1;		// -1 because the last line is always garbage
	for(size_t i=0; i<sz; ++i) {
		StringUtil::trim(tempLines[i]);
		if(tempLines[i] != "") {
			lines.push_back(tempLines[i]);
		}
	}

	return true;
}

