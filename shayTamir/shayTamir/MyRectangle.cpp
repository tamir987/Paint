#include "StdAfx.h"
#include "MyRectangle.h"

IMPLEMENT_SERIAL(MyRectangle, MyShape, 1)

MyRectangle::MyRectangle(void)
{
}


MyRectangle::~MyRectangle(void)
{
}
int MyRectangle::getId() {return 2;}
void MyRectangle::innerDraw(CDC *dc) {
	dc->Rectangle(start.x, start.y, end.x, end.y);
}
