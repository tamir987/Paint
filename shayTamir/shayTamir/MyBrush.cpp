#include "StdAfx.h"
#include "MyBrush.h"

IMPLEMENT_SERIAL(MyBrush, MyShape, 1)

MyBrush::MyBrush(void)
{
}

MyBrush::~MyBrush(void)
{
}
int MyBrush::getId() {return 6;}
void MyBrush::innerDraw(CDC *dc) {
	CPen mypen (PS_SOLID, size, bgColor);
	CPen *oldpen = dc->SelectObject(&mypen);
	dc->MoveTo(start);
	dc->LineTo(end);
	dc->SelectObject(oldpen);
}
