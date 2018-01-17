#pragma once
#include "Command.h"
#include "MyShape.h"

class addShape :
	public Command
{
public:
	addShape(CTypedPtrArray<CObArray, MyShape*> &myShapes, MyShape *s);
	~addShape(void);
	virtual void perform(); //add shape and print the screen
	virtual void rollback(); //delete shape and print the screen
	int getMyId();

private:
	CTypedPtrArray<CObArray, MyShape*> &myShapes;
	MyShape *s;
};
