#include "Include.h"
#include "Sequence.h"
#include "Game.h"

Sequence::Sequence(std::string& name)
{
	mName			= name;
}

Sequence::~Sequence()
{
	std::map<Object*, ActionList*>::iterator it = mActionLists.begin();
	for( ; it != mActionLists.end(); ++it) {
		delete (*it).second;
	}
}

Sequence* Sequence::loadFromFile(std::string& filename)
{
	std::vector<std::string> lines;

	if(!getFileLines(ACTION_DIR + filename, lines)) {
		log_error(STR("Failed to load file: ") + filename);
		return false;
	}

	size_t						numLines = lines.size();
	std::string					tok;	
	std::vector<std::string>	words;
	std::vector<std::string>	tokWords;
	std::string					tokTarget;			// if tok is "herp.TO", then target would be "herp"
	std::string					tokAction;			// if tok is "herp.TO", then action would be "TO"
	
	Object*						targetObj;
	ActionList*					actList;
	Action*						prevAction = NULL;
	for(size_t i=0; i<numLines; ++i) {
		StringUtil::trim(lines[i]);

		//get the next line
		if(lines[i] != "") {
			words = StringUtil::split(lines[i], std::string(" "));
			if(words.size() > 0) {

				tok = words[0];

				if(tok[0] != '#') {
					tokWords = StringUtil::split(tok, std::string("."));

					tokTarget = tokWords[0];
					tokAction = tokWords[1];	

					targetObj = MM.getNamedObject(tokTarget);
					if(!targetObj) {
						log_error(STR("Failed to get target object name: ") + tokTarget);
					} else {

						std::map<Object*, ActionList*>::iterator it = mActionLists.find(targetObj);
						if(it == mActionLists.end()) {
							actList = new ActionList(targetObj, this);
							mActionLists[targetObj] = actList;
						} else {
							actList = mActionLists[targetObj];
						}

						if(tokAction == "ANI") {
							AnimationData* animData = MM.getAnimationData(words[1].c_str());
							AnimationState* animState = animData->getState(words[2].c_str());
							bool loop = (words.size() > 3 && words[3] == "NOLOOP" ? false : true);
							ActionANI* act = new ActionANI(targetObj, animState, loop);					
							insertAction(prevAction, act, actList);

						} else if(tokAction == "COLLIDE") {
							bool collide = (words[1] == "on" ? true : false);
							ActionCOLLIDE* act = new ActionCOLLIDE(targetObj, collide);
							insertAction(prevAction, act, actList);

						} else if(tokAction == "CONTINUE") {
							Object* otherObj = MM.getNamedObject(words[1]);
							if(otherObj) {
								ActionCONTINUE* act = new ActionCONTINUE(targetObj, otherObj);							
								insertAction(prevAction, act, actList);
							}
						} else if(tokAction == "GO") {
							int wayId = atoi(words[1].c_str());
							Waypoint* wp = MM.getWaypoint(wayId);
							if(wp) {
								ActionGO* act = new ActionGO(targetObj, wp);							
								insertAction(prevAction, act, actList);
							}
						} else if(tokAction == "ROT") {
							float rotDeg = (float)atof(words[1].c_str());					
							ActionROT* act = new ActionROT(targetObj, Math::Degree(rotDeg));
							insertAction(prevAction, act, actList);

						} else if(tokAction == "SPEED") {
							float mult = (float)atof(words[1].c_str());
							ActionSPEED* act = new ActionSPEED(targetObj, mult);
							insertAction(prevAction, act, actList);

						} else if(tokAction == "START") {
							Object* otherObj = MM.getNamedObject(words[1]);
							if(otherObj) {
								Sequence* otherSeq = MM.getSequence( words[2] );
								if(otherSeq) {
									ActionList* otherActionList = otherSeq->getActionList(otherObj);
									if(otherActionList) {
										ActionSTART* act = new ActionSTART(targetObj, otherObj, otherActionList);
										insertAction(prevAction, act, actList);
									}
								}
							}
						} else if(tokAction == "TO") {
							int wayId = atoi(words[1].c_str());
							Waypoint* wp = MM.getWaypoint(wayId);
							if(wp) {
								ActionTO* act = new ActionTO(targetObj, wp);
								insertAction(prevAction, act, actList);
							}
						} else if(tokAction == "WAIT") {
							float timeUnits;
							if(words.size() > 1) {
								timeUnits = (float)atof(words[1].c_str());
							} else {
								timeUnits = -1;
							}
							ActionWAIT* act = new ActionWAIT(targetObj, timeUnits);
							insertAction(prevAction, act, actList);
						}

					} //if targetObj

				} //if tok != "#"

			} //if word count > 0

		} //if line is not empty

	} //for each line

	
	return this;
}

void Sequence::insertAction(Action*& prevAction, Action* curAction, ActionList* actList)
{
	actList->insertAction(curAction);

	if(prevAction) {
		prevAction->setNext(curAction);							
	}
	prevAction = curAction;
}

std::string Sequence::getName()
{
	return mName;
}

ActionList* Sequence::getActionList(Object* obj)
{
	std::map<Object*, ActionList*>::iterator it = mActionLists.find(obj);
	if(it != mActionLists.end()) {
		return (*it).second;
	} else {
		return NULL;
	}
}