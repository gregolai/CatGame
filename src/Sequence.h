#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "Include.h"

class Sequence
{
	friend class MemoryManager;
private:
	Sequence(std::string& name);
	~Sequence();

	Sequence* loadFromFile(std::string& filename);
	void insertAction(Action*& prevAction, Action* curAction, ActionList* actList);
public:
	std::string getName();
	ActionList* getActionList(Object* obj);
private:
	std::string						mName;
	std::map<Object*, ActionList*>	mActionLists;
};

#endif