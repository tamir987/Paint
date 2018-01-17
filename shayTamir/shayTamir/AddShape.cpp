#include "StdAfx.h"
#include "addShape.h"


addShape::addShape(CTypedPtrArray<CObArray, MyShape*> &myShapes, MyShape *s)
	: myShapes(myShapes), s(s)
{
}


addShape::~addShape(void)
{
}

int addShape::getMyId() {return s->getId();}

void addShape::perform()
{
	myShapes.Add(s);
}

void addShape::rollback()
{
	for (int i = 0; i < myShapes.GetSize(); ++i)
		if (myShapes[i] == s)
		{
			myShapes.RemoveAt(i);
			return;
		}
}