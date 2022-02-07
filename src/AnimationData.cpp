#include "Include.h"
#include "AnimationData.h"
#include "Game.h"

AnimationData::AnimationData()
{
}

AnimationData::~AnimationData()
{

}

AnimationData* AnimationData::loadFromFile(const char* filename)
{
	mName = std::string(filename);

	std::vector<std::string> lines;

	if(!getFileLines(ANIMATION_DIR + filename, lines)) {
		log_error(STR("Failed to load file: ") + filename);
		return NULL;
	}

	size_t						numLines = lines.size();
	std::string					tok;	
	std::vector<std::string>	words;
	AnimationState*				curState = NULL;
	std::string					stateName;

	//loop thru lines of the file, until the end of the file...
	for(size_t i=0; i<numLines; ++i) {
		StringUtil::trim(lines[i]);

		//get the next line
		if(lines[i] != "") {
			words = StringUtil::split(lines[i], std::string(" "));
			if(words.size() > 0) {

				tok = words[0];

				if(tok == "state") {
					stateName = words[1];
					AnimationState* state = new AnimationState(stateName.c_str());
					mStates[ stateName ] = state;		
					curState = state;
				} else if(tok == "obj") {
					if(curState) {
						Model* model = MM.getModel(words[1].c_str());
						if(model) {
							Texture* tex = model->getTextureVariant( atoi(words[2].c_str()) );
							if(tex) {
								curState->addFrame(model, tex);
							}
						}
					}
				}
			}
		}
	}
	return this;
}

AnimationState* AnimationData::getState(const char* stateName)
{
	std::map<std::string, AnimationState*>::iterator it = mStates.find(std::string(stateName));
	if(it != mStates.end()) {
		return (*it).second;
	}
	return NULL;
}