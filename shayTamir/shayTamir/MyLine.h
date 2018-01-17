#pragma once
#include "MyShape.h"
class MyLine :
	public MyShape
{
public:
	DECLARE_SERIAL(MyLine)
	MyLine(void);
	~MyLine(void);
	int getId();
	void draw(CDC *dc);
};

