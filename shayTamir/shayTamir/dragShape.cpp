#include "StdAfx.h"
#include "dragShape.h"


dragShape::dragShape(CTypedPtrArray<CObArray, MyShape*> &myShapes, MyShape *s, MyShape *last)
	: myShapes(myShapes), s(s),  last(last)
{
	//dragg = false;
}


dragShape::~dragShape(void)
{
}

int dragShape::getMyId() {return s->getId();}

void dragShape::perform()
{
	for (int i = 0; i < myShapes.GetSize(); ++i)
		if (myShapes[i] == last)
		{
			myShapes.RemoveAt(i);
			myShapes.Add(s);
			return;
		}
}

void dragShape::rollback()
{
	for (int i = 0; i < myShapes.GetSize(); ++i)
		if (myShapes[i] == s)
		{
			myShapes.RemoveAt(i);
			myShapes.Add(last);
			return;
		}
}