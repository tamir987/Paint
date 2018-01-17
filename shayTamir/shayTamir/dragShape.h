#pragma once
#include "Command.h"
#include "MyShape.h"

class dragShape : //drag and refill
	public Command
{
public:
	dragShape(CTypedPtrArray<CObArray, MyShape*> &myShapes, MyShape *s,  MyShape *last);
	~dragShape(void);
	virtual void perform(); //add shape and print the screen
	virtual void rollback(); //delete shape and print the screen
	int getMyId();

private:
	CTypedPtrArray<CObArray, MyShape*> &myShapes;
	MyShape *s;
	MyShape *last;
};