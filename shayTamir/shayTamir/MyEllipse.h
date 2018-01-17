#pragma once
#include "MyShape.h"
class MyEllipse :
	public MyShape
{
public:
	DECLARE_SERIAL(MyEllipse)
	MyEllipse(void);
	~MyEllipse(void);
	int getId();
	void innerDraw(CDC *dc);
};

