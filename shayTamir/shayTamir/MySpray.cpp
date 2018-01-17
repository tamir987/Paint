#include "StdAfx.h"
#include "MySpray.h"

IMPLEMENT_SERIAL(MySpray, MyShape, 1)

MySpray::MySpray(void)
{
	addPoints();
}

MySpray::~MySpray(void) {}

int MySpray::getId() {return 4;}

void MySpray::addPoints(){
	for(int i = 0; i < 30; i++)
	{
		deltaX.push_back((rand()%(30)));
		deltaY.push_back((rand()%(30)));
	}
}

void MySpray::innerDraw(CDC *dc){
	for(int i = 0; i < 30; i++)
	{
		randomPixel.SetPoint((start.x + deltaX[i]), (start.y - deltaY[i]));
		dc->SetPixel(randomPixel, bgColor);
	}
}
