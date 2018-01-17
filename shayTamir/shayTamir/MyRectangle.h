#pragma once
#include "MyShape.h"
class MyRectangle :
	public MyShape
{
public:
	DECLARE_SERIAL(MyRectangle)
	MyRectangle(void);
	~MyRectangle(void);
	int getId();
	void innerDraw(CDC *dc);
};

